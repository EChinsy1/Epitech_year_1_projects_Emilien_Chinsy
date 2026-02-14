/*
** EPITECH PROJECT, 2025
** my_put_nbr
** File description:
** This is the seventh task of the day, I have to print out a number
*/

#include <unistd.h>
#include "my.h"

int my_put_nbr(int nb)
{
    size_t temp = 0;

    if (nb > 9) {
        temp = nb % 10;
        my_put_nbr(nb / 10);
        my_putchar(temp + 48);
        return (0);
    } else {
        my_putchar(nb + 48);
        return (0);
    }
}
