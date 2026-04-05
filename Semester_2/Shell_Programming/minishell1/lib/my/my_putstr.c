/*
** EPITECH PROJECT, 2025
** my_putstr
** File description:
** Second task of day 4,
** I have to display the characters of a string
*/

#include <unistd.h>
#include "my.h"

int my_putstr(int fd, const char *str)
{
    int i = 0;

    write(fd, str, my_strlen(str));
    return (0);
}
