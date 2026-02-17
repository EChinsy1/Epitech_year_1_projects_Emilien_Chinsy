/*
** EPITECH PROJECT, 2025
** rush-1-3
** File description:
** Assignement 3, rush1, displays rectangle depending on 2 arguments
*/

#include <unistd.h>

void display_line_top_bot(int cur_col, int end_col, int end_line, int cur_line)
{
    if ((end_line == 0) || (end_col == 0)) {
        my_putchar(66);
        return;
    }
    if ((cur_line == end_line) && ((cur_col == 0) || (cur_col == end_col))) {
        my_putchar(67);
    } else if ((cur_line == 0) && ((cur_col == 0) || (cur_col == end_col))) {
        my_putchar(65);
    } else {
        my_putchar(66);
    }
}

static void display_center(int cur_col, int end_col)
{
    if ((cur_col == 0) || (cur_col == end_col)){
        my_putchar(66);
    } else {
        my_putchar(' ');
    }
}

void displayer_2(int cur_line, int end_line, int cur_col, int end_col)
{
    if (cur_line == 0){
        display_line_top_bot(cur_col, end_col, end_line, cur_line);
    } else if (cur_line == end_line){
        display_line_top_bot(cur_col, end_col, end_line, cur_line);
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
