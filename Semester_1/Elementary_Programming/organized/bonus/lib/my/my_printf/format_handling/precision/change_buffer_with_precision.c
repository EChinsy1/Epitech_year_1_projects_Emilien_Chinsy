/*
** EPITECH PROJECT, 2025
** change buffer with precision
** File description:
** a file that handles precision
*/

#include "../../includes/my.h"

static char *precision_int(char *buffer,
    char **other_args,
    int i,
    int precision)
{
    char *new_buffer = my_calloc((precision + 1), sizeof(char));

    for (; i < (precision - my_strlen(buffer)); i++){
        new_buffer[i] = '0';
    }
    for (int j = 0; j < my_strlen(buffer); j++){
        new_buffer[i] = buffer[j];
        i++;
    }
    new_buffer[i] = '\0';
    free(buffer);
    return (change_buffer_with_width(new_buffer, other_args));
}

static char *precision_int_minus(char *buffer,
    char **other_args,
    int i,
    int precision)
{
    char *new_buffer_minus = my_calloc((precision + 2), sizeof(char));

    new_buffer_minus[0] = '-';
    for (; i < ((precision - my_strlen(buffer)) + 2); i++){
        new_buffer_minus[i] = '0';
    }
    for (int j = 1; j < (my_strlen(buffer)); j++){
        new_buffer_minus[i] = buffer[j];
        i++;
    }
    new_buffer_minus[i] = '\0';
    free(buffer);
    return (change_buffer_with_width(new_buffer_minus, other_args));
}

char *change_buffer_with_precision_int(char *buffer, char **other_args)
{
    int precision = my_getnbr(other_args[2]);
    int i = 0;
    int if_minus_plus_one = 0;

    if (precision > my_strlen(buffer)){
        if (buffer[0] == '-'){
            i++;
            return (precision_int_minus(buffer, other_args, i, precision));
        } else {
            return (precision_int(buffer, other_args, i, precision));
        }
    } else {
        return (change_buffer_with_width(buffer, other_args));
    }
}

char *change_buffer_with_precision_str(char *buffer, char **other_args)
{
    int precision = my_getnbr(other_args[2]);
    char *new_buffer = NULL;
    int i = 0;

    if ((precision < my_strlen(buffer)) && my_strlen(other_args[2]) > 0){
        new_buffer = my_calloc((precision + 1), sizeof(char));
        for (; i < precision; i++){
            new_buffer[i] = buffer[i];
        }
        new_buffer[i] = '\0';
        free(buffer);
        return (change_buffer_with_width(new_buffer, other_args));
    } else {
        return (change_buffer_with_width(buffer, other_args));
    }
}
