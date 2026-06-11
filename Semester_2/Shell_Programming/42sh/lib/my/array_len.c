/*
** EPITECH PROJECT, 2026
** lib
** File description:
** array_len
*/

#include <stdlib.h>

int array_len(char **array)
{
    size_t i = 0;

    for (; array[i] != NULL; i++);
    return i;
}
