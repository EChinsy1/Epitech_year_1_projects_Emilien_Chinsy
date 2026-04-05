/*
** EPITECH PROJECT, 2026
** my_top
** File description:
** file initializing and closing ncurses window
*/

#include <ncurses.h>

void init_screen(int delay)
{
    initscr();
    noecho();
    keypad(stdscr, TRUE);
    halfdelay(delay);
    curs_set(0);
}

void terminate_screen(void)
{
    endwin();
}
