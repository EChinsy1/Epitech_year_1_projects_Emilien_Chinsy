/*
** EPITECH PROJECT, 2025
** rush3.c
** File description:
** emacs
*/

#include "stumper.h"
#include "lib/my/my.h"

int rush3(char *buff, int length, int height)
{
    if (length < 1 || height < 1) {
        return 84;
    }
    if (length == 1 && height == 1) {
        result_if_length_and_height_are_one(buff);
        return 0;
    }
    if (length == 1 && height > 1) {
        check_for_1_length(buff);
        return 0;
    }
    if (length > 1 && height == 1) {
        check_for_1_height(buff);
        return 0;
    } else {
        bigger_than_one(buff, length, height);
        return 0;
    }
}
