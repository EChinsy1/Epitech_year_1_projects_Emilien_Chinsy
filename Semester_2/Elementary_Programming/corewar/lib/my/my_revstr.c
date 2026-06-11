/*
** EPITECH PROJECT, 2025
** my_revstr
** File description:
** we have to write to write a copy of the revstr function
** from the c standard library
*/

#include "my.h"

static int my_swap_str(char *stra, char *strb)
{
    char temp;

    temp = *stra;
    *stra = *strb;
    *strb = temp;
    return (0);
}

char *my_revstr(char *str)
{
    int i = 0;
    int j = 0;
    char c = 0;

    if (!str)
        return (NULL);
    j = my_strlen(str) - 1;
    while (i < j) {
        c = str[i];
        str[i] = str[j];
        str[j] = c;
        i++;
        j--;
    }
    return (str);
}
