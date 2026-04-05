/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** get_directory_to_exec
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "arguments.h"
#include "my.h"

char *create_path(char *path, char *arg)
{
    char *directory_exec = NULL;

    if (path[my_strlen(path) - 1] != '/') {
        directory_exec = my_calloc(sizeof(char),
            (my_strlen(path) * my_strlen(arg) + 3));
    } else {
        directory_exec = my_calloc(sizeof(char),
            (my_strlen(path) * my_strlen(arg) + 1));
    }
    my_strcat(directory_exec, path);
    if (directory_exec[my_strlen(path) - 1] != '/')
        my_strcat(directory_exec, "/");
    my_strcat(directory_exec, arg);
    return (directory_exec);
}

char *malloc_same_path(args_t *args)
{
    char *directory_exec = my_calloc(sizeof(char),
        my_strlen(args->word_array[0]) + 1);

    my_strcat(directory_exec, args->word_array[0]);
    if (access(directory_exec, F_OK) == 0)
        return (directory_exec);
    free(directory_exec);
    return (NULL);
}

char *free_and_return(char *directory_exec, char **word_array)
{
    free_word_array(word_array);
    return (directory_exec);
}

static int has_slash(char *str)
{
    int i = 0;

    while (str[i] != '\0') {
        if (str[i] == '/')
            return (1);
        ++i;
    }
    return (0);
}

static char *is_not_in_path(args_t *args)
{
    if (args->word_array[0][0] == '/' || args->word_array[0][0] == '.') {
        if (access(args->word_array[0], F_OK) == 0) {
            return (malloc_same_path(args));
        }
        return (NULL);
    }
    if (((access(args->word_array[0], F_OK) == 0
                && has_slash(args->word_array[0]) == 1))) {
        return (malloc_same_path(args));
    }
    return (NULL);
}

char *get_directory_exec(args_t *args)
{
    char *directory_exec = NULL;
    int i = 0;
    char **paths = NULL;
    char *not_in_path = is_not_in_path(args);

    if (not_in_path != NULL)
        return (not_in_path);
    while (args->env[i] != NULL && my_strncmp("PATH=", args->env[i], 5) != 0)
        ++i;
    if (args->env[i] == NULL || my_strlen(args->env[i]) <= 5)
        return (NULL);
    paths = my_str_to_word_array(&(args->env[i])[5], ":");
    i = 0;
    for (; paths[i]; ++i) {
        directory_exec = create_path(paths[i], args->word_array[0]);
        if (access(directory_exec, F_OK) == 0)
            return (free_and_return(directory_exec, paths));
        free(directory_exec);
    }
    return (free_and_return(NULL, paths));
}
