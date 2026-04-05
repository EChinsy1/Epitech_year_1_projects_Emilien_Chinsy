/*
** EPITECH PROJECT, 2025
** my_add_nbr
** File description:
** the file to hold the number showing functions
*/

#include "../../includes/my.h"

int size_of_num(int nb)
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

int add_minus_if_neg_and_end(int sign, char *buffer, int i)
{
    if (sign == 1) {
        buffer[i] = '-';
        i++;
    }
    buffer[i] = '\0';
    return (0);
}

char *my_add_nbr(intmax_t nb, char **other_args)
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
    add_minus_if_neg_and_end(sign, buffer, i);
    my_revstr(buffer);
    return (change_buffer_with_precision_int(buffer, other_args));
}

char *my_fake_pivot_add_nbr(intmax_t nb, char **other_args, char *buffer)
{
    char *temp_buffer = my_add_nbr(nb, other_args);

    my_strcat(buffer, temp_buffer);
    free(temp_buffer);
    return (buffer);
}

char *my_pivot_add_nbr(va_list args, char **other_args, char *buffer)
{
    char *temp_buffer = my_add_nbr(
        length_for_int(args, other_args),
        other_args);

    my_strcat(buffer, temp_buffer);
    free(temp_buffer);
    return (buffer);
}
