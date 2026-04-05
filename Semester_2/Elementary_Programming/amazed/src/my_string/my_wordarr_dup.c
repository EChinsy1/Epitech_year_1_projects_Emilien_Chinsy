/*
** EPITECH PROJECT, 2026
** minishell
** File description:
** my_wordarr_dup
*/

#include <stdlib.h>
#include "my_string.h"

char **my_wordarr_dup(char **wordarr)
{
    int len = my_lenwordarr(wordarr);
    char **dup = my_calloc(len + 1, sizeof(char *));

    if (wordarr == NULL)
        return NULL;
    for (int i = 0; wordarr[i] != NULL; i++)
        dup[i] = my_strdup(wordarr[i]);
    dup[len] = NULL;
    return dup;
}
