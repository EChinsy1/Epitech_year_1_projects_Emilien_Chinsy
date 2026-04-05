/*
** EPITECH PROJECT, 2026
** bs_minishell
** File description:
** my_str_to_wordarr
*/

#include <unistd.h>
#include <stdlib.h>
#include "my_string.h"

int my_lenwordarr(char **wordarr)
{
    int nb = 0;

    if (wordarr == NULL)
        return -1;
    for (int i = 0; wordarr[i] != NULL; i++){
        nb++;
    }
    return nb;
}

void free_wordarr(char **wordarr)
{
    if (wordarr == NULL)
        return;
    for (int i = 0; wordarr[i] != NULL; i++)
        free(wordarr[i]);
    free(wordarr);
}

static void free_incomplete_wordarr(char **wordarr, int nb)
{
    for (int i = 0; i < nb; i++)
        free(wordarr[i]);
    free(wordarr);
}

static int get_nb_word(char *str, char deli)
{
    int nb = 0;
    int i = 0;

    if (!str)
        return 0;
    while (str[i] == deli || str[i] == '\t')
        i++;
    for (; str[i] != '\0'; i++){
        if ((str[i] == deli) && str[i + 1] != '\0')
            nb++;
        while (str[i] == deli || str[i] == '\t')
            i++;
    }
    nb++;
    return nb;
}

static char *fill(char *str, char deli, int *n_str)
{
    int len = my_strlen(str);
    char *str_d = my_calloc(len + 1, sizeof(char));

    if (str_d == NULL)
        return NULL;
    for (int i = 0; str[i] != '\0' && str[i] != deli; i++){
        str_d[i] = str[i];
        *n_str = *n_str + 1;
    }
    *n_str = *n_str + 1;
    str_d[len] = '\0';
    return str_d;
}

char **my_str_to_wordarr(char *str, char deli)
{
    int nb_word = get_nb_word(str, deli);
    char **wordarr = malloc(sizeof(char *) * (nb_word + 1));
    int n_str = 0;

    if (wordarr == NULL || !str)
        return NULL;
    for (int i = 0; i < nb_word; i++){
        while (str[n_str] == deli || str[n_str] == '\t')
            n_str++;
        wordarr[i] = fill(&str[n_str], deli, &n_str);
        if (wordarr[i] == NULL){
            free_incomplete_wordarr(wordarr, i);
            return NULL;
        }
    }
    wordarr[nb_word] = NULL;
    return wordarr;
}
