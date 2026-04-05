/*
** EPITECH PROJECT, 2026
** amazed
** File description:
** is_number
*/

#include <unistd.h>
#include "macros.h"

int is_number(char *str)
{
    if (str == NULL)
        return FALSE;
    for (int i = 0; str[i] != '\0'; i++){
        if (!(str[i] >= 48 && str[i] <= 57))
            return FALSE;
    }
    return TRUE;
}
