/*
** EPITECH PROJECT, 2025
** my_strlowcase
** File description:
** the ninth task for the sixth day,
** I have to reproduce the strlowcase function.
** From the standard library.
*/

#include <stdio.h>
#include "my.h"

char *my_strlowcase(char *str)
{
    int i = 0;

    while (str[i] != '\0'){
        if (str[i] >= 65 && str[i] <= 90){
            str[i] = str[i] + 32;
        }
        i++;
    }
    return (str);
}
