/*
** EPITECH PROJECT, 2025
** rush-1-2
** File description:
** Assignement 2 for the first rush,
** We have to display a rectangle,
** the number of lines and columns depends on two values
*/

#include <unistd.h>

static void display_line_top(int cur_col, int end_col, int end_line)
{
    if ((cur_col == 0) && (end_line != 0) && (end_col != 0)){
        my_putchar(47);
    } else if ((cur_col == end_col) && (end_line != 0) && (end_col != 0)){
        my_putchar(92);
    } else {
        my_putchar(42);
    }
}

static void display_line_bottom(int cur_col, int end_col, int end_line)
{
    if ((cur_col == 0) && (end_line != 0) && (end_col != 0)){
        my_putchar(92);
    } else if ((cur_col == end_col) && (end_line != 0) && (end_col != 0)){
        my_putchar(47);
    } else {
        my_putchar(42);
    }
}

static void display_center(int cur_col, int end_col)
{
    if ((cur_col == 0) || (cur_col == end_col)){
        my_putchar(42);
    } else {
        my_putchar(' ');
    }
}

void displayer_2(int cur_line, int end_line, int cur_col, int end_col)
{
    if (cur_line == 0){
        display_line_top(cur_col, end_col, end_line);
    } else if (cur_line == end_line){
        display_line_bottom(cur_col, end_col, end_line);
    } else {
        display_center(cur_col, end_col);
    }
}

void rush(int x, int y)
{
    if ((x <= 0) || (y <= 0)){
        write(2, "Invalid size\n", 14);
    }
    for (int i = 0; i < y; i++){
        for (int j = 0; j < x; j++){
            displayer_2(i, y - 1, j, x - 1);
        }
        my_putchar('\n');
    }
}
