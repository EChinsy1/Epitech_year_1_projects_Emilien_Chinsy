/*
** EPITECH PROJECT, 2025
** length_height.c
** File description:
** emacs
*/

#include "lib/my/my.h"
#include "stumper.h"
#include <stdio.h>

static void show_3_4_5(char *buff)
{
    show_rush(3, length(buff), height(buff));
    my_putstr(" || ");
    show_rush(4, length(buff), height(buff));
    my_putstr(" || ");
    show_rush(5, length(buff), height(buff));
    my_putchar('\n');
}

static int check_for_square_1(char *buff)
{
    int i = 0;
    int max = ((height(buff) * 2) - 2);

    while (buff[i] != '\0') {
        if ((i == 0 || i == max) && buff[i] != 'o') {
            return 0;
        }
        if ((i != 0 && i != max) && buff[i] != '|' && buff[i] != '\n') {
            return 0;
        }
        i++;
    }
    show_rush(1, length(buff), height(buff));
    my_putchar('\n');
    return 0;
}

static int check_for_square_2(char *buff)
{
    int i = 0;

    while (buff[i] != '\0') {
        if (buff[i] != '*' && buff[i] != '\n'){
            return 0;
        }
        i++;
    }
    show_rush(2, length(buff), height(buff));
    my_putchar('\n');
    return 0;
}

static int check_for_square_3(char *buff)
{
    int i = 0;

    while (buff[i] != '\0') {
        if (buff[i] != 'B' && buff[i] != '\n'){
            return 0;
        }
        i++;
    }
    show_3_4_5(buff);
    return 0;
}

int check_for_1_length(char *buff)
{
    check_for_square_2(buff);
    check_for_square_3(buff);
    check_for_square_1(buff);
    return 0;
}
