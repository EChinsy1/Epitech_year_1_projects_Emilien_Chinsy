/*
** EPITECH PROJECT, 2025
** my_add_nbr_base_a_maj.c
** File description:
** handles specifier %A
*/

#include "../../includes/my.h"

char *my_pivot_add_nbr_a_maj(va_list args, char **other_args, char *buffer)
{
    char *temp_buffer = my_add_nbr_base_a(
        length_for_double(args, other_args),
        other_args);
    int i = 0;

    while (temp_buffer[i]){
        if (temp_buffer[i] >= 'a' && temp_buffer[i] <= 'f')
            temp_buffer[i] = temp_buffer[i] - 32;
        if (temp_buffer[i] == 'x')
            temp_buffer[i] = 'X';
        if (temp_buffer[i] == 'p')
            temp_buffer[i] = 'P';
        i++;
    }
    my_strcat(buffer, temp_buffer);
    free(temp_buffer);
    return (buffer);
}
