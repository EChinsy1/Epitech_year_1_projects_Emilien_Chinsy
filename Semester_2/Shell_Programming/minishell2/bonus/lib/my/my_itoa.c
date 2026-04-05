/*
** EPITECH PROJECT, 2025
** my_calloc
** File description:
** a reproduction of the library function calloc
*/

#include "stdlib.h"

 
static int count_digits(unsigned int n)
{
    int len = 0;

    if (n == 0)
        return 1;
    while (n) {
        n /= 10;
        len++;
    }
    return len;
}

char *my_itoa(unsigned int n)
{
    int len = count_digits(n);
    char *str = malloc(len + 1);

    if (!str)
        return NULL;
    str[len] = '\0';
    if (n == 0) {
        str[0] = '0';
        return str;
    }
    while (len > 0) {
        str[len - 1] = '0' + (n % 10);
        n /= 10;
        len--;
    }
    return str;
}