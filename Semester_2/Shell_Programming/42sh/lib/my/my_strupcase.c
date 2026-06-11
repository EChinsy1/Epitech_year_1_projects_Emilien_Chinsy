/*
** EPITECH PROJECT, 2025
** my_strupcase
** File description:
** the eigth task for the sixth day,
** I have to reproduce the strupcase.
*/

#include "my.h"

char *my_strupcase(char *str)
{
    int i = 0;

    while (str[i] != '\0'){
        if (str[i] >= 97 && str[i] <= 122){
            str[i] = str[i] - 32;
        }
        i++;
    }
    return (str);
}
