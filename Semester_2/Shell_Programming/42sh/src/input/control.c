/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Arrows
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my.h"
#include "input.h"

void ctrl_a(int *size, int *where, args_t *args)
{
    *where = 0;
}

void ctrl_e(int *size, int *where, args_t *args)
{
    *where = *size;
}

void alt_f(int *size, int *where, args_t *args)
{
    if (*where == *size)
        return;
    *where += 1;
    while (*where < *size && args->buffer[*where] != ' ')
        *where += 1;
}

void alt_b(int *size, int *where, args_t *args)
{
    if (*where == 0)
        return;
    *where -= 1;
    while (*where > 0 && args->buffer[*where] != ' ')
        *where -= 1;
}
