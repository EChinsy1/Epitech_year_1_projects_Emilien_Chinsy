/*
** EPITECH PROJECT, 2025
** my_putstr
** File description:
** Second task of day 4,
** I have to display the characters of a string
*/

#include "my.h"

int my_putstr(char const *str)
{
    int i = 0;

    while (str[i] != '\0') {
        my_putchar(str[i]);
        i++;
    }
    return (0);
}
