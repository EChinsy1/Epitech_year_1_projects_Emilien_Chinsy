/*
** EPITECH PROJECT, 2026
** minishell
** File description:
** my_my_calloc
*/

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void *my_calloc(int length, int size)
{
    void *buffer = malloc(length * size);

    if (buffer == NULL)
        return NULL;
    for (int i = 0; i < (length * size); i++)
        ((char *)buffer)[i] = 0;
    return buffer;
}
