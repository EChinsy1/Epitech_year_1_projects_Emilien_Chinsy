/*
** EPITECH PROJECT, 2025
** a
** File description:
** a
*/

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void *my_calloc(size_t length, size_t size)
{
    void *buffer = malloc(length * size);
    size_t i;

    if (buffer) {
        for (i = 0; i < (length * size); i++){
            ((char *)buffer)[i] = 0;
        }
    };
    return buffer;
}
