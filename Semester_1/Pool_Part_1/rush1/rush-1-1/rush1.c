/*
** EPITECH PROJECT, 2025
** rush-1-1
** File description:
** Assignement 1, rush1, displays rectangle depending on 2 arguments
*/

#include <unistd.h>

void displayer_1(int cur_line, int end_line, int cur_col, int end_col)
{
    if (cur_line == 0 || cur_line == end_line) {
        if (cur_col == 0 || cur_col == end_col) {
            my_putchar('o');
        } else {
            my_putchar('-');
        }
    } else if (cur_col == 0 || cur_col == end_col) {
        my_putchar('|');
    } else {
        my_putchar(' ');
    }
}

void rush(int x, int y)
{
    if ((x <= 0) || (y <= 0)){
        write(2, "Invalid size\n", 14);
    }
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            displayer_1(i, y - 1, j, x - 1);
        }
        my_putchar('\n');
    }
}
