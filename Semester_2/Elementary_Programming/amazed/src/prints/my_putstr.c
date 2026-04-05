/*
** EPITECH PROJECT, 2026
** bs_minishell
** File description:
** my_putstr
*/

#include <unistd.h>
#include "my_string.h"

void my_putchar(char c)
{
    write(1, &c, 1);
}

void my_putstr(char *str)
{
    if (!str)
        return;
    write(1, str, my_strlen(str));
}
