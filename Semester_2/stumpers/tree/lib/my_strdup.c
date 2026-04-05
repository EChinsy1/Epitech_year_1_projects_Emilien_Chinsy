/*
** EPITECH PROJECT, 2026
** my_strdup.c
** File description:
** dup str
*/

#include <stdlib.h>
#include "../include/lib.h"

char *my_strdup(char *src)
{
    int len = my_strlen(src);
    char *final = malloc(sizeof(char) * (len + 1));
    int i = 0;

    for (i = 0; src[i]; i++)
        final[i] = src[i];
    final[i] = 0;
    return (final);
}
