/*
** EPITECH PROJECT, 2025
** my char is length
** File description:
** a function that checks if a char is length or not
*/

#include "../../includes/my.h"

int my_char_is_length(const char to_check)
{
    if (to_check == 'h' ||
        to_check == 'l' ||
        to_check == 'q' ||
        to_check == 'L' ||
        to_check == 'j' ||
        to_check == 'z' ||
        to_check == 'Z' ||
        to_check == 't'){
        return (1);
    }
    return (0);
}
