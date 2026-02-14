/*
** EPITECH PROJECT, 2025
** my add nbr
** File description:
** my add nbr
*/

#include "my.h"

static int size_of_num(int nb)
{
    int result = 0;
    long number = nb;

    if (number < 0){
        number = number * -1;
        result++;
    }
    if (number == 0){
        result++;
    }
    while (number > 0){
        result++;
        number = number / 10;
    }
    return (result);
}

char *my_add_nbr(int nb)
{
    char *buffer = my_calloc(((size_of_num(nb)) + 1), sizeof(int));
    int i = 0;
    int sign = 0;

    if (nb < 0){
        sign = 1;
        nb = nb * -1;
    }
    if (nb == 0){
        buffer[i] = ('0');
        i++;
    }
    while (nb > 0){
        buffer[i] = ((nb % 10) + '0');
        nb = nb / 10;
        i++;
    }
    my_revstr(buffer);
    return (buffer);
}
