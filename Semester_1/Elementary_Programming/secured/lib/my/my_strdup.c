/*
** EPITECH PROJECT, 2025
** my_strdup
** File description:
** first task of the eigth day,
** I have to write a function that allocates memory
** and copies the string given as argument in it
*/

#include "my.h"

char *my_strdup(char const *src)
{
    char *new_str = my_calloc(sizeof(char), my_strlen(src) + 1);

    my_strcpy(new_str, src);
    return (new_str);
}
