/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Arrows
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "macros.h"
#include "my.h"
#include "input.h"

static void remove_bs_n(char *str)
{
    int len = strlen(str);

    if (len > 0 && str[len - 1] == '\n')
        str[len - 1] = '\0';
}

static void clear(args_t *args)
{
    write(STDIN_FILENO, "\r", 1);
    for (size_t i = 0; i < (strlen(args->buffer) + args->size_of_cwd); ++i)
        write(STDIN_FILENO, " ", 1);
    write(STDIN_FILENO, "\r", 1);
    write_console_message();
}

void up_arrow(int *size, int *where, args_t *args)
{
    if (args->tmp_t == NULL && args->tmp != NULL && args->tmp->tail != NULL)
        args->tmp_t = args->tmp->tail;
    else if (args->tmp_t != NULL && args->tmp_t->prev != NULL)
        args->tmp_t = args->tmp_t->prev;
    else
        return;
    clear(args);
    if (args->buffer) {
        free(args->buffer);
        args->buffer = NULL;
    }
    args->buffer = strdup(args->tmp_t->command);
    *size = strlen(args->buffer);
    *where = strlen(args->buffer);
    remove_bs_n(args->buffer);
    my_putstr(1, args->buffer);
}

void down_arrow(int *size, int *where, args_t *args)
{
    if (args->tmp_t == NULL)
        return;
    if (args->tmp_t->next != NULL) {
        args->tmp_t = args->tmp_t->next;
        clear(args);
        if (args->buffer) {
            free(args->buffer);
            args->buffer = NULL;
        }
        args->buffer = strdup(args->tmp_t->command);
        *size = strlen(args->buffer);
        *where = strlen(args->buffer);
        remove_bs_n(args->buffer);
        my_putstr(1, args->buffer);
    }
}

void left_arrow(int *size, int *where, UNUSED args_t *args)
{
    if (*where < *size) {
        *where += 1;
        CURSORFORWARD;
    }
}

void right_arrow(UNUSED int *size, int *where, UNUSED args_t *args)
{
    if (*where != 0) {
        *where -= 1;
        CURSORBACKWARD;
    }
}

void tab(int *size, int *where, args_t *args)
{
    autocomplete(args->buffer, &args, where, size);
}
