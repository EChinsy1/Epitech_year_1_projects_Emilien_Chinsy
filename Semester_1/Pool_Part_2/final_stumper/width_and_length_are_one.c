/*
** EPITECH PROJECT, 2025
** stumper
** File description:
** emacs
*/

#include <unistd.h>
#include "lib/my/my.h"
#include "stumper.h"

static void rush_3_4_5_with_pipes(void)
{
    show_rush(3, 1, 1);
    my_putstr(" || ");
    show_rush(4, 1, 1);
    my_putstr(" || ");
    show_rush(5, 1, 1);
    my_putchar('\n');
}

int result_if_length_and_height_are_one(char *buff)
{
    if (buff[0] == 'o'){
        show_rush(1, 1, 1);
        my_putchar('\n');
        return (0);
    }
    if (buff[0] == '*'){
        show_rush(2, 1, 1);
        my_putchar('\n');
        return (0);
    }
    if (buff[0] == 'B'){
        rush_3_4_5_with_pipes();
        return (0);
    } else {
        my_putstr("none\n");
        return (0);
    }
}
