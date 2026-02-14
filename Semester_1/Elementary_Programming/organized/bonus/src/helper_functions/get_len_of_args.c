/*
** EPITECH PROJECT, 2025
** get len of args
** File description:
** a function to get the length of a char **
*/

#include <stdio.h>
#include "my.h"

int get_len_of_args(char **args)
{
    int i = 0;

    while (args[i] != NULL) {
        ++i;
    }
    return (i);
}
