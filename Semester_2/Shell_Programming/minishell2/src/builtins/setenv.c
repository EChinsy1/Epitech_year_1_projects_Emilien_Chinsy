/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** cd
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "my.h"
#include "arguments.h"

int get_size_of_char_star_star(char **tab)
{
    int i = 0;

    if (!tab)
        return (-1);
    while (tab[i] != NULL)
        ++i;
    return (i);
}

int find_value_in_char_star_star(char **haystack, char *needle)
{
    int i = 0;

    if (needle == NULL || haystack == NULL)
        return (-1);
    while (haystack[i] != NULL) {
        if (my_strncmp(haystack[i], needle, my_strlen(needle)) == 0)
            return (i);
        ++i;
    }
    return (-1);
}

static char *create_env_variable(char *new_variable, char *new_value)
{
    char *final_env = NULL;
    int len_variable = my_strlen(new_variable);

    if (new_value == NULL) {
        final_env = my_calloc(sizeof(char), len_variable + 2);
        my_strcat(final_env, new_variable);
        final_env[len_variable] = '=';
        final_env[len_variable + 1] = '\0';
        return (final_env);
    } else {
        final_env =
            my_calloc(sizeof(char), (len_variable + my_strlen(new_value) + 2));
        my_strcat(final_env, new_variable);
        my_strcat(final_env, "=");
        my_strcat(final_env, new_value);
        return (final_env);
    }
}

static char **add_to_env(args_t *args, char *new_variable, char *new_value)
{
    char **new_env = NULL;
    int size = get_size_of_char_star_star(args->env);

    new_env = my_calloc(sizeof(char *), size + 2);
    for (int i = 0; i < size; ++i) {
        new_env[i] = my_strdup(args->env[i]);
    }
    free_word_array(args->env);
    new_env[size] = create_env_variable(new_variable, new_value);
    new_env[size + 1] = NULL;
    return (new_env);
}

char **modify_env(args_t *args, char *new_variable, char *new_value)
{
    int where = find_value_in_char_star_star(args->env, new_variable);

    if (where == -1)
        return (add_to_env(args, new_variable, new_value));
    free(args->env[where]);
    args->env[where] = create_env_variable(new_variable, new_value);
    return (args->env);
}

int error_handling(args_t *args, char **command_array)
{
    if (command_array[1] == NULL) {
        print_env(args, command_array);
        return (-269);
    }
    if (!args->env) {
        return (-1);
    }
    if (my_str_isprintable(command_array[1]) != 1) {
        my_putstr(2,
            "setenv: Variable name must contain alphanumeric characters.\n");
        return (1);
    }
    return (0);
}

int setenv_func(args_t *args, char **command_array)
{
    size_t size = 100;
    int where = 0;
    int errors = error_handling(args, command_array);

    if (errors != 0)
        return (errors);
    if (errors == -269)
        return (0);
    if (command_array[2] != NULL && command_array[3] != NULL) {
        my_putstr(2, "setenv: Too many arguments\n");
        return (1);
    }
    args->env = modify_env(args, command_array[1], command_array[2]);
    return (0);
}
