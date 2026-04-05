#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>

char *getstring(void)
{
    char *value = NULL;
    char input;

    input = getch();
    while (input != '\n') {
        if (input)
            strcat(value, &input);
        input = getch();
    }
    return (value);
}

int main(void)
{
    char *input = NULL;

    initscr();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    input = getstring();
    printf("input = %s\n", input);
    endwin();
}
