/*
** EPITECH PROJECT, 2025
** twleth task of the sixth day
** File description:
** I have to remake the str_isalpha function
** from the standard library
*/

#include "my.h"

int my_str_isalpha(char const *str)
{
    int i = 0;

    while (str[i] != '\0'){
        if ((str[i] <= 90 && str[i] >= 65) || (str[i] <= 122 && str[i] >= 97)){
            i++;
        } else {
            return (0);
        }
    }
    return (1);
}
