/*
** EPITECH PROJECT, 2025
** add char
** File description:
** a function to add a char to a string
*/

#include "../../includes/my.h"

void add_char(char *str, char to_add)
{
    int len = my_strlen(str);

    str[len] = to_add;
    str[len + 1] = '\0';
}
