/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** minishell1
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
#include <sys/wait.h>
#include "my.h"
#include "builtins.h"
#include "arguments.h"

static void display_signal(args_t **args, int status, char *name)
{
    int signal = 0;

    if (WIFEXITED(status) == 1)
        return;
    (*args)->last_command_return = status;
    if (WIFSIGNALED(status) == 1) {
        signal = WTERMSIG(status);
        my_putstr(2, strsignal(signal));
        if (WCOREDUMP(status))
            my_putstr(2, " (core dumped)");
    }
    if (WIFSTOPPED(status) == 1) {
        signal = WSTOPSIG(status);
        my_putstr(2, strsignal(signal));
    }
    write(1, "\n", 1);
}

static void execute(args_t **args, char **command_array, char *directory_exec)
{
    execve(directory_exec, command_array, (*args)->env);
    my_putstr(2, command_array[0]);
    my_putstr(2, ": ");
    my_putstr(2, strerror(errno));
    my_putstr(2, ".\n");
    _exit(1);
}

static void fork_command(args_t **args, char **command_array,
    char *directory_exec)
{
    pid_t pid = fork();
    int status = 0;

    if (pid == -1)
        exit(EXIT_FAILURE);
    if (pid == 0) {
        if (directory_exec != NULL) {
            execute(args, command_array, directory_exec);
        } else {
            my_putstr(2, command_array[0]);
            my_putstr(2, ": Command not found.\n");
            free_word_array(command_array);
            free_not_end(*args);
            _exit(1);
        }
    }
    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
        (*args)->last_command_return = WEXITSTATUS(status);
    display_signal(args, status, command_array[0]);
}

static int create_child(args_t *args, char **command_array)
{
    char *directory_exec = NULL;

    directory_exec = get_directory_exec(args, command_array);
    fork_command(&args, command_array, directory_exec);
    if (directory_exec) {
        free(directory_exec);
    }
    return (args->last_command_return);
}

static int exec_builtin(args_t *args, char **command_array)
{
    int i = 0;
    int return_value = 0;

    while (builtinfuncs[i].name != NULL) {
        if (my_strcmp(builtinfuncs[i].name,
                command_array[0]) == 0) {
            args->last_command_return = builtinfuncs[i].
                func(args, command_array);
            return (args->last_command_return);
        }
        ++i;
    }
    return_value = create_child(args, command_array);
    free_word_array(command_array);
    return (return_value);
}

int execute_each_function(args_t *args)
{
    int return_value = 0;

    if (args->command_args == NULL)
        return (1);
    for (int i = 0; args->command_args[i] != NULL; ++i) {
        return_value = exec_builtin(args, args->command_args[i]);
    }
    free(args->command_args);
    return (return_value);
}
