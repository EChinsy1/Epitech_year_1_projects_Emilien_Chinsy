/*
** EPITECH PROJECT, 2025
** my_isneg
** File description:
** this is my submission for the fourth task of the third day,
** I need a function that writes N if the int passed is negative
** and P otherwise
*/

#include <unistd.h>
#include "my.h"

int my_isneg(int n)
{
    if (n < 0) {
        my_putchar('N');
    } else {
        my_putchar('P');
    }
    return (0);
}
