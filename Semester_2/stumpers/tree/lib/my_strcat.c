/*
** EPITECH PROJECT, 2026
** my_strcat
** File description:
** my_strcat
*/

#include "lib.h"
#include <stdio.h>

char *my_strcat(char *src, char *dest)
{
    int len_src = my_strlen(src);
    int len_dest = my_strlen(dest);
    int i = 0;

    for (; i < len_src; ++i)
        dest[len_dest + i] = src[i];
    dest[len_dest + i] = '\0';
    return (dest);
}
