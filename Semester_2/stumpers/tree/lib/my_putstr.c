/*
** EPITECH PROJECT, 2026
** my_putstr
** File description:
** my_putstr
*/

#include <unistd.h>
#include "lib.h"

int my_putstr(char *str)
{
    int len = my_strlen(str);

    write(1, str, len);
    return (0);
}
