/*
** EPITECH PROJECT, 2025
** my_strncat
** File description:
** third task of the seventh day
** I have to write a function to concatenate n characters
** of one string into another
*/

#include "my.h"

char *my_strncat(char *dest, char const *src, int nb)
{
    int len = my_strlen(src);
    int len2 = my_strlen(dest);
    int i = 0;

    while ((i < len) && (i < nb)){
        dest[len2 + i] = src[i];
        i++;
    }
    return (dest);
}
