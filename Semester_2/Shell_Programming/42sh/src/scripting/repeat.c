/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** repeat
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "arguments.h"
#include "scripting.h"
#include "my.h"

static int is_num(char c)
{
    if (c >= '0' && c <= '9')
        return (1);
    return (0);
}

static char *reform_command(char *buffer)
{
    int command_start = 0;

    while (is_num(buffer[command_start]) == 0)
        ++command_start;
    ++command_start;
    while (buffer[command_start] == ' ' || buffer[command_start] == '\t')
        ++command_start;
    return (&buffer[command_start]);
}

int repeat(char *buffer, args_t *args, FILE *file)
{
    char **word_array = my_str_to_word_array(buffer, " ", args);
    char *buf = NULL;
    int num_of_repetitions = 0;

    if (word_array == NULL || buffer == NULL || word_array[1] == NULL)
        return (1);
    num_of_repetitions = strtol(word_array[1], &buf, 10);
    if (buf[0] != '\0') {
        free_word_array(word_array);
        dprintf(2, "repeat: Badly formed number.\n");
        args->last_command_return = 1;
        return (1);
    }
    buf = reform_command(buffer);
    for (int i = 0; i < num_of_repetitions; ++i) {
        buf = strdup(buf);
        exec(buf, args);
    }
    free_word_array(word_array);
    return (1);
}
