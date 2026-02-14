/*
** EPITECH PROJECT, 2025
** my_strcpy
** File description:
** we have to write a copy of the my_strcpy function
** from the c standard library
*/

#include "my.h"

char *my_strcpy(char *dst, char const *src)
{
    int i = 0;

    while (src[i] != '\0'){
        dst[i] = src[i];
        ++i;
    }
    while (dst[i] != '\0'){
        dst[i] = '\0';
        ++i;
    }
    return dst;
}
