/*
** EPITECH PROJECT, 2025
** stumper
** File description:
** emacs
*/
#include <unistd.h>
#include "lib/my/my.h"
#include "stumper.h"

void show_rush(int rush_number, int length, int height)
{
    my_putchar('[');
    my_putstr("rush1-");
    my_put_nbr(rush_number);
    my_putchar(']');
    my_putchar(' ');
    my_put_nbr(length);
    my_putchar(' ');
    my_put_nbr(height);
}
