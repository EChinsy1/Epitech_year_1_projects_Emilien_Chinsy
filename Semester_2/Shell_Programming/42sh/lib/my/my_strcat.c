/*
** EPITECH PROJECT, 2025
** my_strcat
** File description:
** second task of the seventh day
** I have to write a function to concatenate two strings
*/

#include "my.h"

char *my_strcat(char *dest, char const *src)
{
    int len = my_strlen(src);
    int len2 = my_strlen(dest);
    int i = 0;

    if (dest == NULL || src == NULL) {
        return (NULL);
    }
    while (i < len) {
        dest[len2 + i] = src[i];
        i++;
    }
    dest[len + len2] = '\0';
    return (dest);
}
