/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** minishell2
*/

#include <errno.h>
#include <signal.h>
#include <stdbool.h>
#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include "macros.h"
#include "my.h"
#include "builtins.h"
#include "arguments.h"
#include "tree.h"
#include "redirections.h"

int infixe_redirections(tree_t *tree)
{
    int i = 0;
    int redirect_success = 0;
    int other_success = 0;

    if (tree == NULL)
        return (0);
    other_success += infixe_redirections(tree->left_node);
    while (redirection_array[i].name != NULL) {
        if (my_strncmp(redirection_array[i].name,
                tree->symbol, strlen(redirection_array[i].name)) == 0) {
            redirect_success = redirection_array[i].func(tree->value[1],
                tree->symbol);
        }
        ++i;
        if (redirect_success == 1)
            return (1);
    }
    other_success += infixe_redirections(tree->right_node);
    return (other_success);
}

static int extra_error_message(int return_value,
    tree_t *tree, char *directory_exec, args_t **args)
{
    struct stat sb;

    my_putstr(2, tree->value[0]);
    my_putstr(2, ": ");
    my_putstr(2, strerror(errno));
    if (return_value == -1 && access(directory_exec, X_OK) == 0
        && (stat(directory_exec, &sb) != -1
            && (sb.st_mode & S_IFMT) != S_IFDIR))
        my_putstr(2, ". Binary file not executable");
    my_putstr(2, ".\n");
    return (0);
}

static void free_the_tree(args_t **args)
{
    int j = 0;

    for (; (*args)->trees[j] == NULL; ++j)
        j = j;
    for (; (*args)->trees[j]; ++j)
        infixe_free((*args)->trees[j]);
}

static int validate_execution(args_t **args,
    char *directory_exec, tree_t *tree)
{
    int return_value = 0;
    int j = 0;

    if (directory_exec != NULL) {
        if (infixe_redirections(tree) == 0) {
            return_value = execve(directory_exec, tree->value,
                (*args)->env);
            extra_error_message(return_value, tree, directory_exec, args);
            _exit(1);
        } else
            _exit(1);
    } else {
        my_putstr(2, tree->value[0]);
        my_putstr(2, ": Command not found.\n");
        free_the_tree(args);
        free((*args)->trees);
        free_not_end(*args);
        _exit(1);
    }
}

static int exec_normal(tree_t **trees, tree_t *tree, args_t *args,
    int should_execute)
{
    int i = 0;
    char *directory_exec = NULL;

    while (builtinfuncs[i].name != NULL && my_strcmp(builtinfuncs[i].name,
            tree->value[0]) != 0)
        ++i;
    if (i < 5 && my_strcmp(builtinfuncs[i].name, tree->value[0]) == 0) {
        if (i != 3 && should_execute != 0)
            args->last_command_return = builtinfuncs[i].
                func(args, tree->value);
        free_the_tree(&args);
        free(trees);
        free_not_end(args);
        return (0);
    }
    directory_exec = get_directory_exec(args, tree->value);
    validate_execution(&args, directory_exec, tree);
    if (directory_exec)
        free(directory_exec);
    return (args->last_command_return);
}

static int exec_builtin(tree_t *tree, args_t **args, int j, int count)
{
    int i = 0;
    char *directory_exec = NULL;

    if (my_strcmp(tree->value[0], "exit") == 0)
        return (3);
    if (j != count - 1)
        return (0);
    while (builtinfuncs[i].name != NULL) {
        if (my_strcmp(builtinfuncs[i].name,
                tree->value[0]) == 0) {
            (*args)->last_command_return = builtinfuncs[i].
                func(*args, tree->value);
            return (0);
        }
        ++i;
    }
    return (-1);
}

static void wait_all_pids(int count, args_t **args, tree_t *tree)
{
    int status[count];

    for (int i = 0; i < count; ++i) {
        wait(&status[i]);
    }
    for (int i = 0; i < count; ++i) {
        if (WIFEXITED(status[i]) && WEXITSTATUS(status[i]) != 0)
            (*args)->last_command_return = WEXITSTATUS(status[i]);
        if (status[i] == BROKEN_PIPE) {
            (*args)->last_command_return =
                broken_pipe_handling(count, status[i], tree, args);
        }
        display_signal(args, tree, status[i], tree->value[0]);
        tree = tree->left_node;
    }
}

tree_t *get_right_tree(int count, int j, tree_t *temp_tree)
{
    for (int i = 0; i < (count - j - 1); ++i)
        temp_tree = temp_tree->left_node;
    if (j != 0)
        temp_tree = temp_tree->right_node;
    return (temp_tree);
}

static int find_command(tree_t **trees, tree_t *tree, args_t *args, int count)
{
    int pfildes[count - 1][2];
    tree_t *temp_tree = tree;
    int should_exit = 0;
    pid_t pid;

    for (int i = 0; i < (count - 1); ++i)
        pipe(pfildes[i]);
    for (int j = 0; j < count; ++j) {
        temp_tree = get_right_tree(count, j, temp_tree);
        pid = fork();
        if (pid == -1)
            my_putstr(2, "fork error\n");
        if (pid == 0 && (activate_correct_pipes(j, count, pfildes) == 0))
            _exit(exec_normal(trees, temp_tree, args, j != count - 1));
        should_exit += exec_builtin(temp_tree, &args, j, count);
        temp_tree = tree;
    }
    pipe_closer(count - 1, pfildes);
    wait_all_pids(count, &args, tree);
    return (should_exit);
}

int execute_each_function_tree(tree_t **trees, args_t *args)
{
    int return_value = 0;
    int store_return_value = args->last_command_return;

    if (trees == NULL)
        return (1);
    for (int i = 0; trees[i] != NULL; ++i) {
        if (trees[i]->value)
            return_value += find_command(trees, trees[i],
                args, count_commands(trees[i]));
        infixe_free(trees[i]);
        trees[i] = NULL;
    }
    free(trees);
    trees = NULL;
    args->trees = NULL;
    if (return_value > 0) {
        args->last_command_return = store_return_value;
        exit_func(args, NULL);
    }
    return (return_value);
}
