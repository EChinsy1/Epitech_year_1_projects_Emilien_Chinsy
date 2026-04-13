/*
** EPITECH PROJECT, 2025
** thirteenth task of the sixth day
** File description:
** I have to remake the str_isnum function
** from the standard library
*/

#include "my.h"

int my_str_isfloat(char const *str)
{
    int valid_float = 0;
    int point = 0;
    int i = 0;

    while (str[i] != '\0'){
        if (str[i] <= 57 && str[i] >= 48){
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

int my_str_is_num_or_float(char const *str)
{
    int result = 0;

    result = result + my_str_isnum(str);
    result = result + my_str_isfloat(str);
    if (result > 0){
        return (1);
    } else {
        return (0);
    }
}
