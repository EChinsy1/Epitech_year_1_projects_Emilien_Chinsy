/*
** EPITECH PROJECT, 2025
** length_height.c
** File description:
** emacs
*/

#include "stumper.h"
#include "lib/my/my.h"

int length(char *buff)
{
    int i = 0;
    int length = 0;

    while (buff[i] != '\n') {
        i++;
        length++;
    }
    return length;
}

int height(char *buff)
{
    int i = 0;
    int height = 0;

    while (buff[i] != '\0') {
        if (buff[i] == '\n') {
            height++;
        }
        i++;
    }
    return height;
}
