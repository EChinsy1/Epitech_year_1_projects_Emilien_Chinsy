/*
** EPITECH PROJECT, 2025
** my_addchar
** File description:
** a function that adds a char to the buffer
*/

#include "../../includes/my.h"

char *my_addchar(char c, char **other_args)
{
    char *buffer = my_calloc(2, sizeof(char));

    buffer[0] = c;
    buffer[1] = '\0';
    return (change_buffer_with_precision_str(buffer, other_args));
}

char *my_pivot_addchar(va_list args, char **other_args, char *buffer)
{
    char *temp_buffer = my_addchar(va_arg(args, int), other_args);

    my_strcat(buffer, temp_buffer);
    free(temp_buffer);
    return (buffer);
}
