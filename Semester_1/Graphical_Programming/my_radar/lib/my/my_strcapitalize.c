/*
** EPITECH PROJECT, 2025
** the tenth task of the sixth day
** File description:
** I have to rewrite the strcapitalize function
** from the standard library.
*/

#include "my.h"

char *my_strcapitalize(char *str)
{
    int i = 1;
    int n;

    if (str[0] <= 122 && str[0] >= 97){
        str[0] = str[0] - 32;
    }
    while (str[i + 1] != '\0'){
        n = str[i - 1];
        if ((str[i] >= 97 && str[i] <= 122) && (n == 32 || n == 43 || n == 45)){
            str[i] = str[i] - 32;
        }
        i++;
    }
    return (str);
}
