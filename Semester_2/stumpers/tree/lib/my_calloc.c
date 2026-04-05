/*
** EPITECH PROJECT, 2026
** fake_calloc
** File description:
** fake_calloc
*/

#include <stdlib.h>

char *my_fake_calloc(int size, int size_2)
{
    char *value = malloc(size * size_2);

    for (int i = 0; i < size_2; ++i) {
        value[i] = '\0';
    }
    return (value);
}

char **my_big_calloc(int size, int size_2)
{
    char **value = malloc(size * size_2);

    for (int i = 0; i < size_2; ++i) {
        value[i] = NULL;
    }
    return (value);
}
