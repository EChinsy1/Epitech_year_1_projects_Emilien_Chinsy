/*
** EPITECH PROJECT, 2025
** thirteenth task of the sixth day
** File description:
** I have to remake the str_isnum function
** from the standard library
*/

#include "my.h"

int my_char_isnum(char const chaaar)
{
    if (chaaar <= 57 && chaaar >= 48){
        return (1);
    } else {
        return (0);
    }
}
