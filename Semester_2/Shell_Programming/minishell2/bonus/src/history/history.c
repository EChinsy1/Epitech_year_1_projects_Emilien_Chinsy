/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** history
*/

#include <string.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include "my.h"
#include "arguments.h"
#include "macros.h"

char *find_in_history(args_t *args, char *value)
{
    int i = 0;
    char *result = NULL;

    if (!args || !value)
        return (NULL);
    while (args->history[i]) {
        if (strncmp(args->history[i], &result[1], strlen(&result[1])) == 0)
            return (args->history[i]);
        ++i;
    }
    return (NULL);
}

int add_to_history(args_t *args, char *command)
{
    int i = 0;

    if (!args)
        return (-1);
    while (args->history[i])
        ++i;
    if (command[strlen(command) - 1] == '\n')
        command[strlen(command) - 1] = '\0';
    args->history[i] = strdup(command);
    return (0);
}
