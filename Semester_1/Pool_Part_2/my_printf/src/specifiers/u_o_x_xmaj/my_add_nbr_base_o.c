/*
** EPITECH PROJECT, 2025
** my_add_nbr_base_o.c
** File description:
** handles the %o specifier for printf
*/

#include "../../includes/my.h"

int size_of_num_base_o(unsigned int nb)
{
    int result = 0;
    long number = nb;

    if (nb == 0)
        return (1);
    while (number > 0){
        result++;
        number = number / 8;
    }
    return (result);
}

char *my_add_nbr_base_o(uintmax_t nb, char **other_args)
{
    unsigned int number = nb;
    char *buffer = my_calloc((size_of_num_base_o(number) + 1), sizeof(char));
    int i = 0;

    if (number == 0){
        buffer[i] = number + '0';
        i++;
    }
    while (number > 0){
        buffer[i] = ((number % 8) + '0');
        number = number / 8;
        i++;
    }
    buffer[i] = '\0';
    my_revstr(buffer);
    return (change_buffer_with_precision_int(buffer, other_args));
}

char *my_pivot_add_nbr_o(va_list args, char **other_args, char *buffer)
{
    char *temp_buffer = my_add_nbr_base_o(
        length_for_ui(args, other_args),
        other_args);

    my_strcat(buffer, temp_buffer);
    free(temp_buffer);
    return (buffer);
}
