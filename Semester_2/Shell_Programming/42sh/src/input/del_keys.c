/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** getline utils
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <termios.h>
#include <string.h>
#include <sys/ioctl.h>
#include "my.h"
#include "input.h"
#include "arguments.h"

static int get_terminal_width(void)
{
    struct winsize ws;

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == 0 && ws.ws_col > 0)
        return ws.ws_col;
    return 80;
}

static void clear_input(int size, args_t *args)
{
    int term_width = get_terminal_width();
    int total = args->size_of_cwd + size;
    int rows = (total > 0) ? (total - 1) / term_width : 0;

    for (int i = 0; i < rows; ++i)
        write(STDOUT_FILENO, "\033[A", 3);
    write(STDOUT_FILENO, "\r", 1);
    for (int i = 0; i <= rows; ++i) {
        write(STDOUT_FILENO, "\033[2K", 4);
        if (i < rows)
            write(STDOUT_FILENO, "\033[B", 3);
    }
    for (int i = 0; i < rows; ++i)
        write(STDOUT_FILENO, "\033[A", 3);
    write(STDOUT_FILENO, "\r", 1);
}

static void place_cursor(int *where, args_t *args, int size)
{
    int term_width = get_terminal_width();
    int end_row = (args->size_of_cwd + size) / term_width;
    int target_abs = args->size_of_cwd + *where;
    int target_row = target_abs / term_width;
    int target_col = target_abs % term_width;

    for (int i = 0; i < (end_row - target_row); ++i)
        write(STDOUT_FILENO, "\033[A", 3);
    write(STDOUT_FILENO, "\r", 1);
    for (int i = 0; i < target_col; ++i)
        write(STDOUT_FILENO, "\033[C", 3);
}

void suppr(int *size, int *where, args_t *args)
{
    if (*size == 0 || *where == *size)
        return;
    clear_input(*size, args);
    memmove(&(args->buffer)[*where],
        &(args->buffer)[*where + 1], strlen(args->buffer) - *where);
    (args->buffer)[(*size == 0) ? 0 : *size - 1] = '\0';
    *size -= (*size == 0) ? 0 : 1;
    write_console_message();
    write(STDOUT_FILENO, args->buffer, *size);
    place_cursor(where, args, *size);
}

void backspace(int *size, int *where, args_t *args)
{
    if (*where == 0 || *size == 0)
        return;
    clear_input(*size, args);
    memmove(&(args->buffer)[*where - 1],
        &(args->buffer)[*where], strlen(args->buffer) - *where);
    (args->buffer)[(*size == 0) ? 0 : *size - 1] = '\0';
    *size -= (*size == 0) ? 0 : 1;
    *where -= (*where == 0) ? 0 : 1;
    write_console_message();
    write(STDOUT_FILENO, args->buffer, *size);
    place_cursor(where, args, *size);
}
