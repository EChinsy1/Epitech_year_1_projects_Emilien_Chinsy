/*
** EPITECH PROJECT, 2026
** bs_minishell
** File description:
** my_putwordarr
*/

#include <unistd.h>
#include "prints.h"

void put_wordarr(char **wordarr)
{
    if (wordarr == NULL)
        return;
    for (int i = 0; wordarr[i] != NULL; i++){
        my_putstr(wordarr[i]);
        my_putchar('\n');
    }
}
