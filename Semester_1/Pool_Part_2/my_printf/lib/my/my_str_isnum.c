/*
** EPITECH PROJECT, 2025
** thirteenth task of the sixth day
** File description:
** I have to remake the str_isnum function
** from the standard library
*/

#include "my.h"

int my_str_isnum(char const *str)
{
    int i = 0;

    while (str[i] != '\0'){
        if (str[i] <= 57 && str[i] >= 48){
            i++;
        } else {
            return (0);
        }
    }
    return (1);
}
