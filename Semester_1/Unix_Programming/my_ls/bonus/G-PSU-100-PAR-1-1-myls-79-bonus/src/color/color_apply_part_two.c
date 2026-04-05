/*
** EPITECH PROJECT, 2025
** color_apply
** File description:
** functions to print with colors
*/

#include "my.h"

void print_sticky_and_ow(char *name)
{
    my_printf("\x1b[30;42m%s\x1b[0m", name);
}

void print_not_sticky_and_ow(char *name)
{
    my_printf("\x1b[34;42m%s\x1b[m", name);
}

void print_sticky_and_not_ow(char *name)
{
    my_printf("\x1b[37;44m%s\x1b[m", name);
}

void print_sock(char *name)
{
    my_printf("\x1b[35m%s\x1b[0m", name);
}
