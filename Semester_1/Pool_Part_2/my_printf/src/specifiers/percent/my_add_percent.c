/*
** EPITECH PROJECT, 2025
** my print percent
** File description:
** a function to print the percent sign
*/

#include "../../includes/my.h"

char *my_add_percent(va_list args, char **other_args, char *buffer)
{
    char *temp_buffer = my_calloc(2, sizeof(char));

    temp_buffer[0] = '%';
    temp_buffer[1] = '\0';
    temp_buffer = change_buffer_with_precision_str(temp_buffer, other_args);
    my_strcat(buffer, temp_buffer);
    free(temp_buffer);
    return (buffer);
}
