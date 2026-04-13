/*
** EPITECH PROJECT, 2025
** my_add_scientific_not_maj.c
** File description:
** handles the %E specifier
*/

#include "../../includes/my.h"

char *my_pivot_add_scientific_maj(va_list args, char **other_args, char *buff)
{
    char *temp_buffer = my_add_scientific_nota(
        length_for_double(args, other_args),
        other_args);
    int i = 0;

    while (temp_buffer[i]){
        if (temp_buffer[i] == 'e')
            temp_buffer[i] = 'E';
        i++;
    }
    my_strcat(buff, temp_buffer);
    free(temp_buffer);
    return (buff);
}
