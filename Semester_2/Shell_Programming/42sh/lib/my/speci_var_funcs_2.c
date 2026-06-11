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

char *arg_list(args_t *args, char *value)
{
    int total = 0;
    char *result = NULL;

    if (args->argc <= 2)
        return my_strdup("");
    for (int i = 2; i < args->argc; i++)
        total += my_strlen(args->argv[i]) + 1;
    result = my_calloc(sizeof(char), total);
    for (int i = 2; i < args->argc; i++) {
        my_strcat(result, args->argv[i]);
        if (i < args->argc - 1)
            my_strcat(result, " ");
    }
    return result;
}

char *bg_pid(args_t *args, char *value)
{
    if (args->last_pid == 0)
        return my_strdup("");
    return my_strdup(my_itoa(args->last_pid));
}
