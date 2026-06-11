/*
** EPITECH PROJECT, 2025
** remove_extra
** File description:
** removes the quotes in the strings.
*/

#include <stdio.h>
#include "my.h"

static char **remove_single(char **word_array, char to_remove, int i, int *pos)
{
    int newpos = *pos;

    for (; word_array[i][newpos] != '\0'; ++newpos)
        word_array[i][newpos] = word_array[i][newpos + 1];
    *pos += 1;
    newpos = *pos;
    while (word_array[i][newpos] != '\0' && word_array[i][newpos] != to_remove)
        ++newpos;
    if (word_array[i][newpos] == '\0') {
        dprintf(2, "Unmatched, '%c'\n", to_remove);
        return (NULL);
    } else {
        *pos = newpos;
        while (word_array[i][newpos] != '\0') {
            word_array[i][newpos] = word_array[i][newpos + 1];
            ++newpos;
        }
    }
    return (word_array);
}

char **in_between(char **word_array, int i, int *pos)
{
    if (word_array && word_array[i][*pos] == '"') {
        word_array = remove_single(word_array, '"', i, pos);
    } else if (word_array && word_array[i][*pos] == '\'') {
        word_array = remove_single(word_array, '\'', i, pos);
    } else {
        *pos += 1;
    }
    return (word_array);
}

char **remove_extra(char **word_array)
{
    int pos = 0;

    for (int i = 0; word_array && word_array[i]; ++i) {
        pos = 0;
        while (word_array && word_array[i][pos] != '\0') {
            in_between(word_array, i, &pos);
        }
    }
    return (word_array);
}
