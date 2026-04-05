/*
** EPITECH PROJECT, 2026
** minishell
** File description:
** my_strcat
*/

#include <stdlib.h>
#include "my_string.h"

char *my_strcat(char *src, char *add)
{
    int len_add = 0;
    int len_src = 0;
    char *new = NULL;

    if (!src || !add)
        return NULL;
    len_add = my_strlen(add);
    len_src = my_strlen(src);
    new = malloc(sizeof(char) * (len_add + len_src + 1));
    if (!new)
        return NULL;
    for (int i = 0; src[i] != '\0'; i++)
        new[i] = src[i];
    for (int i = 0; i < len_add; i++)
        new[len_src + i] = add[i];
    new[len_src + len_add] = '\0';
    return new;
}

char *my_strncat(char *src, char *add, int nb)
{
    int len_src = 0;
    int len_add = 0;
    char *new = NULL;

    if (!src || !add)
        return NULL;
    len_add = my_strlen(add);
    len_src = my_strlen(src);
    new = malloc(sizeof(char) * (len_add + len_src + 1));
    for (int i = 0; src[i] != '\0'; i++)
        new[i] = src[i];
    for (int i = 0; i < nb; i++)
        new[len_src + i] = add[i];
    new[len_src + len_add] = '\0';
    return new;
}
