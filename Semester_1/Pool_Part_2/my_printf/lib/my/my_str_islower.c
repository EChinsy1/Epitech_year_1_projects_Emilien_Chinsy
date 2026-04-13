/*
** EPITECH PROJECT, 2025
** str_islower
** File description:
** fourteenth task of the sixth day,
** I have to remake the str_islower function,
** from the standard library
*/

#include "my.h"

int my_str_islower(char const *str)
{
    int i = 0;

    while (str[i] != '\0'){
        if (str[i] <= 122 && str[i] >= 97){
            i++;
        } else {
            return (0);
        }
    }
    return (1);
}
