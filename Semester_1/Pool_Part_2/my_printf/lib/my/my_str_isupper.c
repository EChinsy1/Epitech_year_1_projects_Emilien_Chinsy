/*
** EPITECH PROJECT, 2025
** str_isupper
** File description:
** fifteenth task of the sixth day,
** I have to remake the str_isupper function,
** from the standard library
*/

#include "my.h"

int my_str_isupper(char const *str)
{
    int i = 0;

    while (str[i] != '\0'){
        if (str[i] <= 90 && str[i] >= 65){
            i++;
        } else {
            return (0);
        }
    }
    return (1);
}
