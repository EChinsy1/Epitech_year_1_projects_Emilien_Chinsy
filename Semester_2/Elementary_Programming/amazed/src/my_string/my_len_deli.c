/*
** EPITECH PROJECT, 2026
** minishell
** File description:
** my_len_deli
*/

#include <unistd.h>
#include "macros.h"

int len_deli(char *str, char deli)
{
    int nb = 0;

    if (str == NULL)
        return NOPE;
    for (int i = 0; str[i] != '\0'; i++){
        if (str[i] == deli)
            return nb;
        nb++;
    }
    return NOPE;
}
