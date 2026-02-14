/*
** EPITECH PROJECT, 2025
** flag finder
** File description:
** a file that has function to find flags
*/


#include "../../includes/my.h"

static int valid_zero(char **other_args, char *buffer)
{
    if (my_str_is_num_or_float(buffer) == 1)
        return (1);
    if ((buffer[0] == '-' || buffer[0] == '+')
        && my_str_is_num_or_float(&buffer[1]))
        return (1);
    if (*other_args[4] == 'a' || *other_args[4] == 'A')
        return (1);
    if (*other_args[4] == 'x' || *other_args[4] == 'X')
        return (1);
    if (*other_args[4] == 'e' || *other_args[4] == 'E')
        return (1);
    if (*other_args[4] == 'g' || *other_args[4] == 'G')
        return (1);
    return (0);
}

char flag_is_zero(char **other_args, char *buffer)
{
    char width_char = ' ';

    for (int y = 0; y < my_strlen(other_args[0]); y++){
        if (other_args[0][y] == '0' && valid_zero(other_args, buffer) == 1){
            width_char = '0';
        }
    }
    return (width_char);
}

char flag_is_space(char **other_args, char *buffer)
{
    int valid = 0;

    if ((my_strlen(other_args[2]) == 0 || my_str_is_num_or_float(buffer) == 1)
        && my_strlen(buffer) != 0){
        valid = 1;
    }
    for (int y = 0; y < my_strlen(other_args[0]); y++){
        if (other_args[0][y] == ' ' &&
            my_str_is_num_or_float(buffer) == 1 && valid == 1){
            return (1);
        }
    }
    return (0);
}

char flag_is_minus(char **other_args, char *buffer)
{
    for (int y = 0; y < my_strlen(other_args[0]); y++){
        if (other_args[0][y] == '-'){
            return (1);
        }
    }
    return (0);
}

char flag_is_plus(char **other_args, char *buffer)
{
    for (int y = 0; y < my_strlen(other_args[0]); y++){
        if (other_args[0][y] == '+' && my_str_is_num_or_float(buffer) == 1 &&
            buffer[0] != '-'){
            return (1);
        }
    }
    return (0);
}

char flag_is_hash(char **other_args)
{
    for (int y = 0; y < my_strlen(other_args[0]); y++){
        if (other_args[0][y] == '#'){
            return (1);
        }
    }
    return (0);
}
