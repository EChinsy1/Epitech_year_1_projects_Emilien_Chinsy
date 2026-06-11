/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** if only we could fly
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "arguments.h"
#include "scripting.h"
#include "my.h"

int foreach(char *buffer, args_t *args, FILE *file)
{
    char **foreach_values = calloc(sizeof(char *), 2);
    char *read = buffer;
    int size = 1;
    size_t getline_size = 0;

    foreach_values[0] = strdup(read);
    while (strncmp(read, "endif", 5) != 0) {
        foreach_values = realloc(foreach_values, sizeof(char *) * (size + 2));
        if (getline(&read, &getline_size, file) < 0)
            return (84);
        read = remove_backslash_r(read);
        foreach_values[size] = strdup(read);
        foreach_values[size + 1] = NULL;
        ++size;
    }
    exec_foreach(foreach_values, args, file);
    return (1);
}
