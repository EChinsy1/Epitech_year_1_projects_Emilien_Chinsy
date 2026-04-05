/*
** EPITECH PROJECT, 2026
** print_map.c
** File description:
** print map for duo stumper 2
*/

#include <stdio.h>
#include <stdlib.h>

void print_map(char **map)
{
    for (int i = 0; map[i] != NULL; i++)
        printf("%s\n", map[i]);
}
