/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Aurélien, bonne chance.
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

static char my_getch(void)
{
    char c = 0;
    struct termios term;
    struct termios oterm;

    tcgetattr(0, &oterm);
    memcpy(&term, &oterm, sizeof(term));
    term.c_lflag &= ~(ICANON | ECHO);
    term.c_cc[VMIN] = 1;
    term.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &term);
    read(STDIN_FILENO, &c, 1);
    tcsetattr(0, TCSANOW, &oterm);
    return c;
}

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

static int handle_arrows(char c, int *size, int *where, args_t *args)
{
    if (c == 0x1B) {
        read(STDIN_FILENO, &c, 1);
        if (c == '[') {
            read(STDIN_FILENO, &c, 1);
            parse_arrows(c, size, where, args);
        }
        parse_alt(c, size, where, args);
        return (1);
    }
    if (c == '\t') {
        tab(size, where, args);
        return 1;
    }
    if (c <= 31) {
        parse_ctrl(c, size, where, args);
        return (1);
    }
    return (0);
}

static void add_char(int *size, char c, int *where, args_t *args)
{
    char *buffer = calloc(sizeof(char), strlen(args->buffer) + 2);

    strcat(buffer, args->buffer);
    if (buffer == NULL || *size >= 8191)
        return;
    if (*where != *size) {
        memmove(buffer + *where + 1,
            buffer + *where, strlen(buffer) - *where + 1);
        (buffer)[*where] = c;
    } else
        (buffer)[*where] = c;
    *size += 1;
    *where += 1;
    clear_input(*size - 1, args);
    write_console_message();
    write(STDOUT_FILENO, buffer, *size);
    free(args->buffer);
    args->buffer = buffer;
    place_cursor(where, args, *size);
}

static int get_size_of_cwd(void)
{
    int size_of_cwd = 0;
    char *temp = getcwd(NULL, size_of_cwd);

    if (temp) {
        size_of_cwd = strlen(temp) + 4;
        free(temp);
    }
    return (size_of_cwd);
}

int read_char(char **buffer, int *size, int *where, args_t *args)
{
    char c = 0;

    c = my_getch();
    if (c == 127) {
        backspace(size, where, args);
        return (1);
    }
    if (c == '~') {
        suppr(size, where, args);
        return (1);
    }
    if (c == '\n')
        return (0);
    if (handle_arrows(c, size, where, args) == 1) {
        place_cursor(where, args, *size);
        return (1);
    }
    add_char(size, c, where, args);
    return (1);
}

int my_getline(char **buffer, args_t *args)
{
    int size = 0;
    int where = 0;
    size_t sizee = 0;
    struct termios test;

    args->size_of_cwd = get_size_of_cwd();
    args->tmp = args->history;
    args->tmp_t = NULL;
    if (tcgetattr(STDIN_FILENO, &test) == 0) {
        if (*buffer != NULL)
            free(*buffer);
        *buffer = calloc(sizeof(char), 8192);
        if (!buffer)
            return -1;
        while (read_char(buffer, &size, &where, args) != 0);
        args->size_of_cwd = 0;
        printf("\n");
        return (0);
    } else
        return (getline(buffer, &sizee, stdin));
}
