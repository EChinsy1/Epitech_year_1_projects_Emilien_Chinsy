/*
** EPITECH PROJECT, 2025
** mini printf
** File description:
** first mini project of the year,
** we have to make a mini printf function
** that is a printf that handles the:
** s, i, d, c and % flags
*/

#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

static int my_putchar(char c)
{
    write(1, &c, 1);
    return (1);
}

int my_put_nbr(int nb)
{
    size_t temp = 0;

    if (nb < 0) {
        my_putchar('-');
        if (nb < -2147483647) {
            my_putchar('2');
            my_put_nbr(147483648);
            return (0);
        }
        my_put_nbr(nb * -1);
        return (0);
    } else if (nb > 9) {
        temp = nb % 10;
        my_put_nbr(nb / 10);
        my_putchar(temp + 48);
        return (0);
    } else {
        my_putchar(nb + 48);
        return (0);
    }
}

static int size_of_num(int nb)
{
    int result = 0;

    my_put_nbr(nb);
    while (nb % 10){
        result++;
        nb = nb / 10;
    }
    return (result - 2);
}

static int my_strlen(char const *str)
{
    int i = 0;

    while (str[i] != '\0'){
        i++;
    }
    return (i);
}

static int my_putstr(char const *str)
{
    int i = 0;

    while (str[i] != '\0') {
        my_putchar(str[i]);
        i++;
    }
    return (i - 1);
}

int which_type(va_list args, char to_check)
{
    switch (to_check) {
        case 's':
            return (my_putstr(va_arg(args, char*)));
        case 'c':
            return (my_putchar(va_arg(args, int)));
        case 'd':
            return (size_of_num(va_arg(args, int)));
        case 'i':
            return (size_of_num(va_arg(args, unsigned int)));
        case '%':
            my_putchar('%');
    }
    return (0);
}

int mini_printf(const char *format, ...)
{
    va_list args;
    int j = 0;
    int total = 0;

    va_start(args, format);
    for (int i = 0; i < my_strlen(format); ++i) {
        j = i + 1;
        if (format[i] == '%' && format[j] != '\0'){
            i++;
            total = total + which_type(args, format[i]);
        } else {
            my_putchar(format[i]);
        }
    }
    va_end(args);
    total = total + j;
    return (total);
}
