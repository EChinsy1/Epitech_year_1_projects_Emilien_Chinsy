/*
** EPITECH PROJECT, 2025
** my_getnbr
** File description:
** fifth task of the fourth day,
** I have to take a string
** and return the number written in that string
*/

#include "my.h"

static int get_sign(char const *str, int *i)
{
    int sign = 1;

    while ((str[*i] == 45) || (str[*i] == 43)){
        if (str[*i] == 45){
            sign = -sign;
        }
        (*i)++;
    }
    return (sign);
}

int my_getnbr(char const *str)
{
    long num = 0;
    int i = 0;
    int sign = get_sign(str, &i);

    for (int val = i; str[val] != '\0'; val++) {
        if ((((num * 10) + 8) > 2147483647)) {
            num = 0;
            break;
        }
        if (str[val] <= 57 && str[val] >= 48){
            num = num * 10 + (str[val] - 48);
        } else {
            break;
        }
    }
    return (num * sign);
}
