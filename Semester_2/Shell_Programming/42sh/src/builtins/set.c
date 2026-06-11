/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** cd
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "my.h"
#include "arguments.h"

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

static char *create_local_variable(char *value)
{
    char *final_local = NULL;
    int len_variable = my_strlen(value);
    int find_equal = -1;

    for (int i = 0; value[i] && find_equal == -1; ++i)
        if (value[i] == '=')
            find_equal = i;
    if (find_equal == -1) {
        return (strdup(value));
    } else {
        final_local = calloc(sizeof(char), (strlen(value) + 2));
        strncat(final_local, value, find_equal);
        strcat(final_local, "\t");
        strncat(final_local, &value[find_equal + 1], len_variable - find_equal);
        return (final_local);
    }
}

static char **add_to_local(args_t *args, char *value)
{
    int size = get_size_of_char_star_star(args->local);

    if (size == -1)
        size = 0;
    args->local = realloc(args->local, (size + 2) * sizeof(char *));
    args->local[size] = create_local_variable(value);
    args->local[size + 1] = NULL;
    return (args->local);
}

char **modify_local(args_t *args, char *value)
{
    int where = -1;
    char *value_name = NULL;
    int find_equal = -1;

    for (int i = 0; value[i] && find_equal == -1; ++i)
        if (value[i] == '=')
            find_equal = i;
    if (find_equal != -1) {
        value_name = calloc(find_equal + 1, sizeof(char));
        strncat(value_name, value, find_equal);
        where = find_value_in_char_star_star(args->local, value_name);
        free(value_name);
        if (where == -1)
            return (add_to_local(args, value));
        free(args->local[where]);
        args->local[where] = create_local_variable(value);
    }
    return (args->local);
}

static void print_local(args_t *args)
{
    for (int i = 0; args->local && args->local[i]; ++i) {
        printf("%s\n", args->local[i]);
    }
}

int set_func(args_t *args, char **command_array)
{
    size_t size = 100;
    int where = 0;
    int errors = 0;

    if (!command_array)
        return (1);
    if (command_array[1] == NULL)
        print_local(args);
    for (int i = 1; command_array[i]; ++i)
        args->local = modify_local(args, command_array[i]);
    return (0);
}
