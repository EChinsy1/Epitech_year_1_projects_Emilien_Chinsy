/*
** EPITECH PROJECT, 2025
** 101pong
** File description:
** math module exercise 1
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "struct.h"

static int time_shift_isnum(char const *str)
{
    int i = 0;

    while (str[i] != '\0'){
        if (str[i] <= 57 && str[i] >= 48){
            i++;
        } else {
            return (0);
        }
    }
    return (1);
}

static int my_str_isnum(char const *str)
{
    int i = 0;

    while (str[i] != '\0'){
        if ((str[i] <= 57 && str[i] >= 48) || str[i] == 45){
            i++;
        } else {
            return (0);
        }
    }
    return (1);
}

static int my_str_isfloat(char const *str)
{
    int valid_float = 0;
    int point = 0;
    int i = 0;

    while (str[i] != '\0'){
        if (str[i] <= 57 && str[i] >= 48 || str[i] == 45){
            valid_float++;
        }
        if (str[i] == '.'){
            valid_float++;
            ++point;
        }
        i++;
    }
    if (point != 1 || i != valid_float){
        return (0);
    }
    return (1);
}

int my_argv_is_valid(int argc, char **argv)
{
    int result = 0;

    for (int i = 0; i < argc - 1; ++i){
        if (i == 6){
            return (time_shift_isnum(argv[i]));
        }
        result = my_str_isnum(argv[i]);
        result = result + my_str_isfloat(argv[i]);
        if (result == 0) {
            return (0);
        }
        result = 0;
    }
    return (1);
}
