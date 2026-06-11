/*
** EPITECH PROJECT, 2025
** my_strcat
** File description:
** j'ai oublié
*/

#include "my.h"

char *my_strcat(char *dest, char const *src)
{
    int len = my_strlen(src);
    int len2 = my_strlen(dest);
    int i = 0;

    while (i < len){
        dest[len2 + i] = src[i];
        i++;
    }
    dest[len2 + i] = '\0';
    return (dest);
}
