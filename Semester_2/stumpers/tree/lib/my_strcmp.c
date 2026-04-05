/*
** EPITECH PROJECT, 2026
** my_strcmp.c
** File description:
** compare
*/
#include "../include/lib.h"

int compare_characters(char c1, char c2)
{
    if (c1 >= 'A' && c1 <= 'Z')
        c1 += 32;
    if (c2 >= 'A' && c2 <= 'Z')
        c2 += 32;
    return (c1 - c2);
}

int my_strcmp(char *s1, char *s2)
{
    int lens1 = my_strlen(s1);
    int lens2 = my_strlen(s2);
    int cmp_res = 0;

    for (int i = 0; s1[i] && s2[i]; i++){
        cmp_res = compare_characters(s1[i], s2[i]);
        if (cmp_res != 0)
            return (cmp_res);
    }
    if (lens1 != lens2)
        return (lens1 - lens2);
    return 0;
}
