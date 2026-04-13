/*
** EPITECH PROJECT, 2025
** my_putstr
** File description:
** a reproduction of the library function putstr
*/

#include <unistd.h>
#include "my.h"

void my_putstr(char *str)
{
    int len = my_strlen(str);

    write(1, str, len);
}
