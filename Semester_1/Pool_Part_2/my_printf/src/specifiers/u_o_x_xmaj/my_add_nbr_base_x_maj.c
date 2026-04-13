/*
** EPITECH PROJECT, 2025
** my_add_nbr_base_x.c
** File description:
** handles the %x specifier for printf
*/

#include "../../includes/my.h"

int size_of_num_base_x_maj(unsigned int nb)
{
    int result = 0;
    long number = nb;

    if (nb == 0)
        return (1);
    while (number > 0){
        result++;
        number = number / 16;
    }
    return (result);
}

char *my_add_nbr_base_x_maj(uintmax_t nb, char **other_args)
{
    unsigned int number = nb;
    char *buffer = my_calloc((size_of_num_base_x_maj(number) + 1),
        sizeof(char));
    int i = 0;
    char *base = "0123456789ABCDEF";

    if (number == 0){
        buffer[i] = number + '0';
        i++;
    }
    while (number > 0){
        buffer[i] = base[(number % 16)];
        number = number / 16;
        i++;
    }
    buffer[i] = '\0';
    my_revstr(buffer);
    return (change_buffer_with_precision_int(buffer, other_args));
}

char *my_pivot_add_nbr_x_maj(va_list args, char **other_args, char *buffer)
{
    char *temp_buffer = my_add_nbr_base_x_maj(
        length_for_ui(args, other_args),
        other_args);

    my_strcat(buffer, temp_buffer);
    free(temp_buffer);
    return (buffer);
}
