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
#include "jobs.h"

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
        } else {
            free_tree_not_end(args);
            free(directory_exec);
            _exit(1);
        }
    } else {
        my_putstr(2, tree->value[0]);
        my_putstr(2, ": Command not found.\n");
        free_tree_not_end(args);
        _exit(1);
    }
}

static int get_i(tree_t *tree)
{
    int i = 0;

    while (builtinfuncs[i].name != NULL && my_strcmp(builtinfuncs[i].name,
            tree->value[0]) != 0)
        ++i;
    return i;
}

static int exec_normal(tree_t **trees, tree_t *tree, args_t *args,
    int should_execute)
{
    int i = get_i(tree);
    char *directory_exec = NULL;

    if (i < BUILTINS) {
        if (i != EXIT && should_execute != 0)
            args->last_command_return = builtinfuncs[i].
                func(args, tree->value);
        free_the_tree(&args);
        free(trees);
        free_not_end(args);
        clear_jobs(args->jobs);
        return (0);
    }
    directory_exec = get_directory_exec(args, tree->value);
    validate_execution(&args, directory_exec, tree);
    if (directory_exec)
        free(directory_exec);
    clear_jobs(args->jobs);
    return (args->last_command_return);
}

static int return_dup_n_close(int fd_0, int fd_1)
{
    dup2(fd_0, 0);
    dup2(fd_1, 1);
    close(fd_0);
    close(fd_1);
    return (0);
}

static int exec_builtin(tree_t *tree, args_t **args, int j, int count)
{
    int i = 0;
    char *directory_exec = NULL;
    int fd_0 = dup(0);
    int fd_1 = dup(1);

    if (my_strcmp(tree->value[0], "exit") == 0)
        return (3);
    if (j != count - 1)
        return (0);
    while (builtinfuncs[i].name != NULL) {
        if (my_strcmp(builtinfuncs[i].name,
                tree->value[0]) == 0 &&
            infixe_redirections(tree) == 0) {
            (*args)->last_command_return = builtinfuncs[i].
                func(*args, tree->value);
            return (return_dup_n_close(fd_0, fd_1));
        }
        ++i;
    }
    return (-1);
}

static void wait_all_pids(int count, args_t **args, tree_t *tree, pid_t pid)
{
    int status[count];

    if (find_separator((*args)->buffer, tree->index) == BACKGROUND){
        add_job(pid, tree->index, (*args)->buffer, &(*args)->jobs);
        (*args)->last_pid = pid;
        printf("[%lu] %u\n", get_infos_from_pid(pid, (*args)->jobs)->id, pid);
        return;
    }
    for (size_t i = 0; i < count; ++i)
        waitpid(-1, &status[i], WUNTRACED);
    for (int i = 0; i < count; ++i) {
        if (WIFEXITED(status[i]) && WEXITSTATUS(status[i]) != 0)
            (*args)->last_command_return = WEXITSTATUS(status[i]);
        if (status[i] == BROKEN_PIPE) {
            (*args)->last_command_return =
                broken_pipe_handling(count, status[i], tree, args);
        }
        display_signal(args, tree, status[i], pid);
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
    pid_t pid = 0;

    for (int i = 0; i < (count - 1); ++i)
        pipe(pfildes[i]);
    for (int j = 0; j < count; ++j) {
        temp_tree = get_right_tree(count, j, tree);
        pid = fork();
        setpgid(pid, getpgrp());
        if (pid == -1)
            my_putstr(2, "fork error\n");
        if (pid == 0 && (activate_correct_pipes(j, count, pfildes) == 0))
            _exit(exec_normal(trees, temp_tree, args, j != count - 1));
        should_exit = exec_builtin(temp_tree, &args, j, count);
    }
    pipe_closer(count - 1, pfildes);
    wait_all_pids(count, &args, tree, pid);
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
