/*
** EPITECH PROJECT, 2025
** my_strncmp
** File description:
** seventh task of the sixth day,
** I have to rewrite the strncmp function
** from the standard library
*/

#include "my.h"

int my_strncmp(char const *s1, char const *s2, int n)
{
    int i = 0;

    while ((s1[i] == s2[i]) && (s1[i] != '\0') && (s2[i] != '\0') && i < n - 1){
        i++;
    }
    if (s1[i] != '\0' && s2[i] == '\0'){
        return (1);
    } else if (s2[i] != '\0' && s1[i] == '\0'){
        return (-1);
    }
    if (s1[i] > s2[i]){
        return (1);
    } else if (s2[i] > s1[i]){
        return (-1);
    } else {
        return (0);
    }
}
