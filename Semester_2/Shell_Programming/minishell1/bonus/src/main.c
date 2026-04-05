/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** minishell1
*/

#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include "my.h"
#include "arguments.h"


void free_not_end(args_t *args)
{
    free(args->buffer);
    free(args->old_dir);
    free(args->home_dir);
    free_word_array(args->env);
}

static args_t create_args(char **env)
{
    args_t args;
    char **new_env = NULL;
    int size = get_size_of_char_star_star(env);

    args.buffer = NULL;
    args.command_args = NULL;
    new_env = my_calloc(sizeof(char *), size + 2);
    args.home_dir = NULL;
    for (int i = 0; i < size; ++i) {
        new_env[i] = my_strdup(env[i]);
        if (my_strncmp(env[i], "HOME=", 5) == 0)
            args.home_dir = my_strdup(&(env[i][5]));
    }
    if (args.home_dir == NULL)
        args.home_dir = my_strdup("none");
    args.env = new_env;
    args.last_command_return = 0;
    args.old_dir = my_strdup("none");
    return (args);
}

static void write_console_message(void)
{
    size_t size = 0;
    char *buffer = NULL;
    char *vrai_buffer = getcwd(buffer, size);

    my_putstr(1, "\x1b[1;36m");
    my_putstr(1, vrai_buffer);
    my_putstr(1, "\x1b[m");
    my_putstr(1, "\x1b[1;34m");
    my_putstr(1, " >> ");
    my_putstr(1, "\x1b[m");
    free(buffer);
    free(vrai_buffer);
}

int minishell(char **env)
{
    char *buffer = NULL;
    args_t args = create_args(env);
    size_t size = 0;
    ssize_t getline_return = 0;

    while (args.last_command_return != 84) {
        write_console_message();
        getline_return = getline(&(args.buffer), &size, stdin);
        if (getline_return < 0) {
            free_not_end(&args);
            return (args.last_command_return);
        }
        if (getline_return != 1)
            args.command_args = parse_stuff(args.buffer, " \t;");
        if (getline_return != 1 && args.command_args[0] != NULL)
            execute_each_function(&args);
    }
    free_not_end(&args);
    return (args.last_command_return);
}

static void new_sigterm(int pid)
{
    write(1, "\n", 1);
    write_console_message();
}

int main(int argc, char **argv, char **env)
{
    int final_return = 0;

    signal(SIGINT, &new_sigterm);
    final_return = minishell(env);
    return (final_return);
}
