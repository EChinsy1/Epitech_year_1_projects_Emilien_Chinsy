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
#include <sys/stat.h>
#include "my.h"
#include "builtins.h"
#include "arguments.h"

static void display_signal(args_t **args, int status, char *name)
{
    int signal = 0;

    if (WIFEXITED(status) || !WIFSIGNALED(status))
        return;
    (*args)->last_command_return = status;
    signal = WTERMSIG(status);
    if (signal == SIGINT)
        return;
    if (signal == SIGFPE) {
        my_putstr(2, "Floating exception");
    } else
        my_putstr(2, strsignal(signal));
    if (WCOREDUMP(status))
        my_putstr(2, " (core dumped)");
    if (WIFSTOPPED(status) == 1) {
        signal = WSTOPSIG(status);
        my_putstr(2, strsignal(signal));
    }
    write(2, "\n", 1);
}

static int execute(args_t **args, char *directory_exec)
{
    struct stat sb;
    int return_value = execve(directory_exec, (*args)->word_array,
        (*args)->env);

    my_putstr(2, (*args)->word_array[0]);
    my_putstr(2, ": ");
    my_putstr(2, strerror(errno));
    if (return_value == -1 && access(directory_exec, X_OK) == 0
        && (stat(directory_exec, &sb) != -1
            && (sb.st_mode & S_IFMT) != S_IFDIR))
        my_putstr(2, ". Binary file not executable");
    my_putstr(2, ".\n");
    exit(1);
}

static void fork_command(args_t **args, char *directory_exec)
{
    pid_t pid = fork();
    int status = 0;

    if (pid == -1)
        exit(EXIT_FAILURE);
    if (pid == 0) {
        if (directory_exec != NULL) {
            execute(args, directory_exec);
        } else {
            my_putstr(2, (*args)->word_array[0]);
            my_putstr(2, ": Command not found.\n");
            free_word_array((*args)->word_array);
            free_not_end(*args);
            _exit(1);
        }
    }
    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
        (*args)->last_command_return = WEXITSTATUS(status);
    display_signal(args, status, (*args)->word_array[0]);
}

static int create_child(args_t *args)
{
    char *directory_exec = NULL;

    directory_exec = get_directory_exec(args);
    fork_command(&args, directory_exec);
    if (directory_exec) {
        free(directory_exec);
    }
    free_word_array(args->word_array);
    return (args->last_command_return);
}

int exec_builtin(args_t *args)
{
    int i = 0;

    if (args->word_array == NULL)
        return (1);
    while (builtinfuncs[i].name != NULL) {
        if (my_strcmp(builtinfuncs[i].name,
                args->word_array[0]) == 0) {
            args->last_command_return = builtinfuncs[i].func(args);
            return (args->last_command_return);
        }
        ++i;
    }
    return (create_child(args));
}
