/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Where instruction for the scripting part
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "scripting.h"
#include "my.h"

static int count_array(char **array)
{
    int size = 0;

    for (; array[size]; ++size);
    return size;
}

static int error_handling(char **array)
{
    dprintf(2, "where: too few arguments.\n");
    my_array_free(1, array);
    return -1;
}

static void create_exec(char *arg, char **fp_array)
{
    char *string = NULL;

    for (int i = 0; fp_array[i]; ++i) {
        string = calloc(sizeof(char), strlen(
                fp_array[i]) + strlen(arg) + strlen(" 2> /tmp/prout") + 5);
        if (!string)
            return;
        strcat(string, "ls ");
        strcat(string, fp_array[i]);
        strcat(string, "/");
        strcat(string, arg);
        strcat(string, " 2> /tmp/prout");
        system(string);
        free(string);
    }
}

int where_builtin(args_t *args, char **command_array)
{
    int idx = 0;
    int count = 0;
    char **fp_array = NULL;

    if (!command_array)
        return -1;
    count = count_array(command_array);
    if (count < 2)
        return error_handling(command_array);
    for (; args->env[idx]; ++idx)
        if (strncmp(args->env[idx], "PATH=", 5) == 0)
            break;
    fp_array = my_str_to_word_array(args->env[idx] + 5, ":\n", args);
    if (!fp_array)
        return -1;
    for (int i = 0; i < count; ++i)
        create_exec(command_array[i], fp_array);
    my_array_free(1, fp_array);
    return 1;
}

int where(char *buffer, args_t *args, FILE *file)
{
    int idx = 0;
    int count = 0;
    char **array = my_str_to_word_array(buffer, " ", args);
    char **fp_array = NULL;

    if (!array)
        return -1;
    count = count_array(array);
    if (count < 2)
        return error_handling(array);
    for (; args->env[idx]; ++idx)
        if (strncmp(args->env[idx], "PATH=", 5) == 0)
            break;
    fp_array = my_str_to_word_array(args->env[idx] + 5, ":\n", args);
    if (!fp_array)
        return -1;
    for (int i = 0; i < count; ++i)
        create_exec(array[i], fp_array);
    my_array_free(2, array, fp_array);
    return 1;
}
