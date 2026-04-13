/*
** EPITECH PROJECT, 2025
** my_strstr
** File description:
** the fifth task of the sixth day, I have to remake the strstr
*/

#include <stdio.h>
#include "my.h"

static int my_strlen_05(char const *str)
{
    int i = 0;

    while (str[i] != '\0'){
        i++;
    }
    return (i);
}

char *my_strstr(char *str, char const *to_find)
{
    int i = 0;
    int len_of_to_find = my_strlen_05(to_find);
    int len_of_str = my_strlen_05(str);
    int j = 0;

    while (str[i + 1] != '\0'){
        while (str[i + j] == to_find[j] && ((i + j) < len_of_str)){
            j++;
        }
        if (j == len_of_to_find){
            return (&str[i]);
        }
        j = 0;
        i++;
    }
    return (NULL);
}
