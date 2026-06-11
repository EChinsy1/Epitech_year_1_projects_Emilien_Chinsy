/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** functions to handle special variables
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "my.h"
#include "arguments.h"

static int array_len(char **array)
{
    size_t len = 0;

    if (!array)
        return -1;
    while (array[len] != NULL)
        len++;
    return len;
}

char *last_return(args_t *args, char *value)
{
    return my_strdup(my_itoa(args->last_command_return));
}

char *arg_nb(args_t *args, char *value)
{
    char *endptr = NULL;
    int index = strtol(value + 1, &endptr, 10);

    if (*endptr != 0)
        return NULL;
    if (index >= args->argc || index < 1)
        return NULL;
    return my_strdup(args->argv[index]);
}

char *cmd_name(args_t *args, char *value)
{
    return my_strdup(args->argv[0]);
}

char *amt_of_arg(args_t *args, char *value)
{
    return my_strdup(my_itoa(array_len(args->argv + 1)));
}

char *shell_pid(args_t *args, char *value)
{
    return my_strdup(my_itoa(getpid()));
}
