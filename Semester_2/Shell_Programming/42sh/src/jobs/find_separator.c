/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** detect separators
*/

#include <string.h>
#include <stdio.h>
#include "tree.h"

static size_t get_sep(char *pos)
{
    size_t index = 0;

    while (SEPARATORS[index] != NULL){
        if (strncmp(pos, SEPARATORS[index],
                strlen(SEPARATORS[index])) == 0)
            return index;
        index++;
    }
    return EXECUTE;
}

static size_t is_sep(char *c)
{
    size_t index = 0;

    while (SEPARATORS[index] != NULL){
        if (strncmp(c, SEPARATORS[index],
                strlen(SEPARATORS[index])) == 0)
            return strlen(SEPARATORS[index]);
        index++;
    }
    return 0;
}

size_t find_separator(char *command, size_t index)
{
    int sep_index = -1;
    size_t command_index = 0;

    while (is_sep(command + command_index)){
        command_index++;
    }
    while (command[command_index] != 0){
        sep_index += is_sep(command + command_index);
        if (sep_index == index){
            return get_sep(command + command_index);
        }
        command_index++;
    }
    return EXECUTE;
}
