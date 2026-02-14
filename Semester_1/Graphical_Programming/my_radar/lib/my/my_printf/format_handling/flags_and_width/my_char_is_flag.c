/*
** EPITECH PROJECT, 2025
** my char is flag
** File description:
** a function that checks if a char is a flag or not
*/

#include "../../includes/my.h"

int my_char_is_flag(char to_check)
{
    if (to_check == 39 ||
        to_check == '+' ||
        to_check == ' ' ||
        to_check == '-' ||
        to_check == '#' ||
        to_check == '0'){
        return (1);
    }
    return (0);
}
