/*
** EPITECH PROJECT, 2026
** get_array.c
** File description:
** get array for stumper 2
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my.h"
#include "struct.h"

static int nb_line(char *str)
{
    int size = 0;

    for (int i = 0; str[i] != '\0'; i++){
        if (str[i] == '\n')
            size += 1;
    }
    return (size);
}

static void next_line(char *str, int *i)
{
    for (; str[(*i)] != '\0' && str[(*i)] != '\n'; (*i) += 1);
}

char **get_array(char *str, char **map)
{
    int idx = 0;
    int size = nb_line(str) + 1;

    map = calloc(sizeof(char *), size + 2);
    if (map == NULL)
        return (map);
    map[idx] = strtok(&str[0], "\n");
    for (int i = 0; str[i + 1] != '\0'; i++){
        idx += 1;
        map[idx] = strtok(NULL, "\n");
    }
    map[size] = NULL;
    return (map);
}
