/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** file containing the minishell function
*/


#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include "jobs.h"
#include "my.h"
#include "arguments.h"
#include "input.h"
#include "macros.h"

void free_not_end(args_t *args)
{
    free(args->buffer);
    free(args->old_dir);
    free(args->home_dir);
    free_list(args->history);
    free_word_array(args->env);
    free_word_array(args->local);
}

static void create_args2(args_t *args, char **new_env)
{
    args->history = init_history();
    args->local = NULL;
    args->trees = NULL;
    args->jobs = NULL;
    args->last_command_return = 0;
    args->old_dir = my_strdup("none");
    args->nb_alias = 0;
    args->alias = NULL;
    args->last_pid = 0;
}

args_t create_args(int argc, char **argv, char **env)
{
    args_t args;

    args.buffer = NULL;
    args.argc = argc;
    args.argv = argv;
    args.env = my_calloc(sizeof(char *), get_size_of_char_star_star(env) + 2);
    args.hist_index = 0;
    args.home_dir = NULL;
    for (int i = 0; i < get_size_of_char_star_star(env); ++i) {
        args.env[i] = my_strdup(env[i]);
        if (my_strncmp(env[i], "HOME=", 5) == 0)
            args.home_dir = my_strdup(&(env[i][5]));
    }
    if (args.home_dir == NULL)
        args.home_dir = my_strdup("none");
    create_args2(&args, args.env);
    return (args);
}

void write_console_message(void)
{
    size_t size = 0;
    char *vrai_buffer = getcwd(NULL, size);

    my_putstr(1, "\x1b[1;36m");
    my_putstr(1, vrai_buffer);
    my_putstr(1, "\x1b[m");
    my_putstr(1, BLUE(" >> "));
    free(vrai_buffer);
}

void exexcution(args_t *args)
{
    args->trees = parse_trees(args->buffer, args);
    if (args->trees == NULL)
        return;
    if (args->trees[0]->value[0] != NULL)
        execute_each_function_tree(args->trees, args);
}

static int minishell_loop(args_t *args)
{
    size_t s = 0;
    ssize_t getlinereturn = 0;

    while (args->last_command_return != EPITECH_FAILURE) {
        write_console_message();
        getlinereturn = my_getline(&(args->buffer), args);
        if (getlinereturn < 0 || getlinereturn == ERROR)
            break;
        if (check_exclamation_mark(&(args->buffer), args->history, &s) == ERROR)
            continue;
        if (history(args->buffer, args->history) == ERROR)
            continue;
        if (check_alias(&(args->buffer), args->alias, &s) == ERROR)
            continue;
        exexcution(args);
        update_jobs(&args->jobs);
    }
    return args->last_command_return;
}

int minishell(int argc, char **argv, char **env)
{
    args_t args = create_args(argc, argv, env);
    int ret = 0;

    ret = minishell_loop(&args);
    free_not_end(&args);
    return ret;
}

static int minishell2(int argc, char **argv, char **env)
{
    char *buffer = NULL;
    args_t arg = create_args(argc, argv, env);
    size_t size = 0;
    ssize_t getlinereturn = 0;

    while (arg.last_command_return != EPITECH_FAILURE) {
        write_console_message();
        getlinereturn = getline(&(arg.buffer), &size, stdin);
        if (getlinereturn < 0)
            exit_func(&arg, NULL);
        history(arg.buffer, arg.history);
        if (getlinereturn != 1)
            arg.trees = parse_trees(arg.buffer, &arg);
        if (arg.trees != NULL && arg.trees[0] && arg.trees[0]->value[0] != NULL)
            execute_each_function_tree(arg.trees, &arg);
    }
    free_not_end(&arg);
    return (arg.last_command_return);
}
