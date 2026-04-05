/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** unsetenv
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "my.h"
#include "arguments.h"

static char **remove_value(args_t *args, char *argument)
{
    int where = find_value_in_char_star_star(args->env, argument);
    char **new_env = NULL;
    int size = get_size_of_char_star_star(args->env);
    int j = 0;

    if (where == -1)
        return (args->env);
    new_env = my_calloc(sizeof(char *), size);
    for (int i = 0; i < size; ++i) {
        if (i != where) {
            new_env[j] = my_strdup(args->env[i]);
            ++j;
        }
    }
    free_word_array(args->env);
    new_env[size - 1] = NULL;
    return (new_env);
}

int unsetenv_func(args_t *args, char **command_array)
{
    size_t size = 100;
    int where = 0;
    int i = 1;

    if (command_array[1] == NULL) {
        my_putstr(2,
            "unsetenv: Too few arguments.\n");
        free_word_array(command_array);
        return (1);
    }
    if (!args->env) {
        free_word_array(command_array);
        return (-1);
    }
    while (command_array[i] != NULL) {
        args->env = remove_value(args, command_array[i]);
        ++i;
    }
    free_word_array(command_array);
    return (0);
}
