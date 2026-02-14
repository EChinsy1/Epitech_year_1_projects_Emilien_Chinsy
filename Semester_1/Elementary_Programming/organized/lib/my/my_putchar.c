/*
** EPITECH PROJECT, 2025
** my_putchar.c
** File description:
** the my_putchar.c function stored elsewhere to help with tests
*/

#include <unistd.h>
#include "my.h"

void my_putchar(char c)
{
    write(1, &c, 1);
}
