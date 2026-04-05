/*
** EPITECH PROJECT, 2025
** mini_printf
** File description:
** first project of cpool part 2
*/

#include <unistd.h>
#include <stdarg.h>
#include <stddef.h>

static void my_putchar(char const c)
{
    write(1, &c, 1);
}

static int power_of_ten(int power)
{
    int result = 1;

    for (int i = 0; i < power; i++){
        result = result * 10;
    }
    return (result);
}

static int get_number(long nb)
{
    long local_nb = nb;
    long current_digit = nb;
    int amount_of_digits = 0;
    int max_digits;

    while (current_digit > 9){
        current_digit = current_digit / 10;
        amount_of_digits++;
    }
    max_digits = amount_of_digits + 1;
    while (amount_of_digits >= 0){
        amount_of_digits--;
        current_digit = local_nb;
        current_digit = current_digit / power_of_ten(amount_of_digits + 1);
        current_digit = (current_digit % 10) + '0';
        my_putchar(current_digit);
    }
    return (max_digits);
}

static int my_putstr(char const *str)
{
    int index = 0;
    int count = 0;

    while (str[index] != '\0'){
        my_putchar(str[index]);
        index++;
        count++;
    }
    return (count);
}

static int my_put_nbr(int nb)
{
    long number;

    number = nb;
    if (number < 0){
        my_putchar('-');
        number = number * -1;
    }
    return (get_number(number));
}

static int handle_flags(char flag, va_list args)
{
    switch (flag){
        case 'd':
            return (my_put_nbr(va_arg(args, int)));
        case 'i':
            return (my_put_nbr(va_arg(args, int)));
        case 's':
            return (my_putstr(va_arg(args, char *)));
        case 'c':
            my_putchar(va_arg(args, int));
            return (1);
        case '%':
            my_putchar('%');
            return (1);
    }
    return (0);
}

int mini_printf(const char *format, ...)
{
    va_list args;
    int index = 0;
    int amount = 0;

    va_start(args, format);
    while (format[index]){
        if (format[index] != '%'){
            my_putchar(format[index]);
            amount++;
        } else {
            amount += handle_flags(format[index + 1], args);
            index++;
        }
        index++;
    }
    va_end(args);
    return (amount);
}
