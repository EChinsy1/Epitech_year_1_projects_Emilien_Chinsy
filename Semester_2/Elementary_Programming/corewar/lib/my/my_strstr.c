/*
** EPITECH PROJECT, 2025
** my_strstr
** File description:
** Remake of strstr
*/

#include <stdio.h>
#include "my.h"

char *my_strstr(char *str, char const *to_find)
{
    int i = 0;
    int j = 0;
    int len_of_to_find = my_strlen(to_find);
    int len_of_str = my_strlen(str);

    for (; str[i + 1] != '\0'; i++) {
        for (; str[i + j] == to_find[j] && ((i + j) < len_of_str); j++);
        if (j == len_of_to_find)
            return (&str[i]);
        j = 0;
    }
    return NULL;
}
