/*
** EPITECH PROJECT, 2025
** my_putstr
** File description:
** a file to hold the string showing functions
*/

#include "../../includes/my.h"

char *my_addstr(char const *str, char **other_args)
{
    int i = 0;
    char *buffer = my_calloc((my_strlen(str) + 2), sizeof(char));

    while (str[i] != '\0') {
        buffer[i] = str[i];
        i++;
    }
    buffer[i] = '\0';
    return (change_buffer_with_precision_str(buffer, other_args));
}

char *my_pivot_addstr(va_list args, char **other_args, char *buffer)
{
    char *temp_buffer = my_addstr(va_arg(args, char*), other_args);

    my_strcat(buffer, temp_buffer);
    free(temp_buffer);
    return (buffer);
}
