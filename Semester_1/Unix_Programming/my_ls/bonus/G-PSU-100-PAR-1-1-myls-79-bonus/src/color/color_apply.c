/*
** EPITECH PROJECT, 2025
** color_apply
** File description:
** functions to print with colors
*/

#include "my.h"

void print_dir(char *name)
{
    my_printf("\x1b[01;34m%s\x1b[0m", name);
}

void print_fifo(char *name)
{
    my_printf("\x1b[33;40m%s\x1b[m", name);
}

void print_device(char *name)
{
    my_printf("\x1b[1;33;40m%s\x1b[m", name);
}

void print_link(char *name)
{
    my_printf("\x1b[01;36m%s\x1b[0m", name);
}

void print_exec(char *name)
{
    my_printf("\x1b[01;32m%s\x1b[0m", name);
}
