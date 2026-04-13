/*
** EPITECH PROJECT, 2025
** my_strdup
** File description:
** first task of the eigth day,
** I have to write a function that allocates memory
** and copies the string given as argument in it
*/

#include <stdlib.h>
#include "my.h"

char *my_strcpy(char *dst, char const *src)
{
    int i = 0;

    while (src[i] != '\0'){
        dst[i] = src[i];
        i++;
    }
    while (dst[i] != '\0'){
        dst[i] = '\0';
        i++;
    }
    return dst;
}

char *my_strdup(char const *src)
{
    char *new_str = my_calloc(sizeof(char), my_strlen(src) + 1);

    my_strcpy(new_str, src);
    return (new_str);
}
