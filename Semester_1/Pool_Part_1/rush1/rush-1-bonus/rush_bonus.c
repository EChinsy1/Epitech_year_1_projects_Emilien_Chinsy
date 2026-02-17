/*
** EPITECH PROJECT, 2025
** rush-1-bonus
** File description:
** this is the bonus exercise for the first rush.
** We have to make a function that lets you make any type of rectangle
** the function requires a character array of size 6 to be called
** the first character is the top left character
** the second is the top right character
** the third is the bottom left character
** the fourth is the bottom right character
** the fifth is the character that will be the center of the top and bot lines
** the last one is the one for the sides.
*/

#include <unistd.h>

void my_putchar(char c)
{
    write(1, &c, 1);
}

static void top_line(int cur_col, int end_col, int end_line, char *all_chars)
{
    if ((cur_col == 0) && (end_line != 0) && (end_col != 0)){
        my_putchar(all_chars[0]);
    } else if ((cur_col == end_col) && (end_line != 0) && (end_col != 0)){
        my_putchar(all_chars[1]);
    } else {
        my_putchar(all_chars[4]);
    }
}

static void bottom_line(int cur_col, int end_col, int end_line, char *all_chars)
{
    if ((cur_col == 0) && (end_line != 0) && (end_col != 0)){
        my_putchar(all_chars[2]);
    } else if ((cur_col == end_col) && (end_line != 0) && (end_col != 0)){
        my_putchar(all_chars[3]);
    } else {
        my_putchar(all_chars[4]);
    }
}

static void display_center(int cur_col, int end_col, char *all_chars)
{
    if ((cur_col == 0) || (cur_col == end_col)){
        my_putchar(all_chars[5]);
    } else {
        my_putchar(' ');
    }
}

static int char_valid_checker(char *cha)
{
    int i;

    while (cha[i] != '\0'){
        i++;
    }
    if (i == 6){
        return (1);
    } else {
        write(2, "you need 6 chars", 16);
        my_putchar('\n');
        return (0);
    }
}

void displayer_2(int cur_line, int end_line, int end_col, char *cha)
{
    for (int j = 0; j < end_col + 1; j++){
        if (cur_line == 0){
            top_line(j, end_col, end_line, cha);
        }
        if (cur_line == end_line){
            bottom_line(j, end_col, end_line, cha);
        }
        if ((cur_line != end_line) && (cur_line != 0)){
            display_center(j, end_col, cha);
        }
    }
    my_putchar('\n');
}

void rush_generic(int x, int y, char *all_chars)
{
    if (char_valid_checker(all_chars) == 0){
        return;
    }
    if ((x <= 0) || (y <= 0)){
        write(2, "Invalid size\n", 14);
    }
    for (int i = 0; i < y; i++){
        displayer_2(i, y - 1, x - 1, all_chars);
    }
}

void rush(int x, int y, char *all_chars)
{
    rush_generic(x, y, all_chars);
}

int main(void)
{
    char c[] = "/\\\\/**";

    rush(5, 5, c);
    return (0);
}
