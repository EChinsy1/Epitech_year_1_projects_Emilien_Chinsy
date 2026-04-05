/*
** EPITECH PROJECT, 2026
** cesar
** File description:
** decrypt
*/

#include <stdio.h>
#include <string.h>
#include "macro.h"

char change_char_pos(char *new_string, int i, int n)
{
    if ((new_string[i] >= 'A' && new_string[i] <= 'Z' - n)
        || (new_string[i] >= 'a' && new_string[i] <= 'z' - n))
        return (new_string[i] + n);
    if ((new_string[i] >= 'A' && new_string[i] <= 'Z')
        || (new_string[i] >= 'a' && new_string[i] <= 'z'))
        return (new_string[i] - ALPH_SIZE + n);
    return (new_string[i]);
}

char change_char_neg(char *new_string, int i, int n)
{
    if ((new_string[i] >= 'A' + n && new_string[i] <= 'Z')
        || (new_string[i] >= 'a' + n && new_string[i] <= 'z'))
        return (new_string[i] - n);
    if ((new_string[i] >= 'A' && new_string[i] <= 'Z')
        || (new_string[i] >= 'a' && new_string[i] <= 'z'))
        return (new_string[i] + ALPH_SIZE - n);
    return (new_string[i]);
}

char *decrypt(char *string, int n)
{
    char *new_string = NULL;

    if (string == NULL)
        return (NULL);
    new_string = strdup(string);
    if (new_string == NULL)
        return (NULL);
    for (size_t i = 0; new_string[i] != STRING_DELIM; ++i) {
        if (n >= 0)
            new_string[i] = change_char_pos(new_string, i, n);
        else
            new_string[i] = change_char_neg(new_string, i, n * -1);
    }
    return (new_string);
}
