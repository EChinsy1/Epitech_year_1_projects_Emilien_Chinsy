/*
** EPITECH PROJECT, 2026
** bs_minishell
** File description:
** my_strdup
*/

#include <unistd.h>
#include <stdlib.h>
#include "my_string.h"

char *my_strndup(char *str, int n)
{
    int len = 0;
    char *str_d = NULL;

    if (!str)
        return NULL;
    len = my_strlen(str);
    str_d = my_calloc(len + 1, sizeof(char));
    if (str_d == NULL)
        return NULL;
    for (int i = 0; str[i] != '\0' && i < n; i++)
        str_d[i] = str[i];
    str_d[len] = '\0';
    return str_d;
}
