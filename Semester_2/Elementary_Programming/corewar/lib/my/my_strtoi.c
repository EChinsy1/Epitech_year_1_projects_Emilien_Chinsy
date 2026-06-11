/*
** EPITECH PROJECT, 2026
** Helper
** File description:
** My strtoi recreation
*/

#include "my.h"

static char *fill_str(char const *str, char **endptr, int i)
{
    int j = 0;
    int len_str = 0;

    for (len_str = i; str[len_str]; ++len_str);
    *endptr = my_calloc(sizeof(char), len_str + 1);
    for (; str[i]; ++i) {
        (*endptr)[j] = str[i];
        ++j;
    }
    (*endptr)[j] = '\0';
    return (*endptr);
}

int my_strtoi(char const *str, char **endptr)
{
    int len_str = 0;
    int nb = 0;

    for (int i = 0; str[i]; ++i) {
        if ((nb * 10 + 8) > 2147483647) {
            nb = 0;
            break;
        }
        if (str[i] <= 57 && str[i] >= 48)
            nb = nb * 10 + (str[i] - 48);
        else {
            *endptr = fill_str(str, endptr, i);
            break;
        }
    }
    return nb;
}
