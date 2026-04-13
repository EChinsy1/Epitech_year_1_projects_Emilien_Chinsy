/*
** EPITECH PROJECT, 2025
** my_strlen
** File description:
** task 3 of day 4, counts the number of characters in a string.
*/

#include <unistd.h>
#include "my.h"

int my_strlen(char const *str)
{
    int i = 0;

    while (str[i] != '\0'){
        i++;
    }
    return (i);
}
