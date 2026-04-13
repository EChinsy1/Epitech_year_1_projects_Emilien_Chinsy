/*
** EPITECH PROJECT, 2025
** my_strncpy
** File description:
** we have to write to write a copy of the strncpy function
** from the c standard library
*/

#include "my.h"

char *my_strncpy(char *dest, char const *src, int n)
{
    int i = 0;

    while (i != n){
        dest[i] = src[i];
        i++;
    }
    return dest;
}
