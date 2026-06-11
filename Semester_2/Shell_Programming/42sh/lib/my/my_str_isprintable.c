/*
** EPITECH PROJECT, 2025
** the sixteenth task of the sixth day
** File description:
** I have to write the str_isprintable function from the standard library
*/

#include "my.h"

int my_str_isprintable(char *str)
{
    int i = 0;

    while (str[i] != '\0'){
        if ((str[i] <= 90 && str[i] >= 65) ||
            (str[i] <= 122 && str[i] >= 97) ||
            str[i] <= 57 && str[i] >= 48){
            i++;
        } else {
            return (0);
        }
    }
    return (1);
}
