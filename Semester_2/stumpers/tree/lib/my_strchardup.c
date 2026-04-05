/*
** EPITECH PROJECT, 2026
** my_strdup.c
** File description:
** dup str
*/
#include "lib.h"
#include <stdlib.h>

char *my_strchardup(char *src, int n)
{
    char *final = malloc(sizeof(char) * (2));

    final[0] = src[n];
    final[1] = 0;
    return (final);
}
