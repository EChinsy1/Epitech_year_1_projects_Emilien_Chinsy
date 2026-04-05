/*
** EPITECH PROJECT, 2025
** my_show_word_array
** File description:
** write a funciton that displays the content of an array of words
*/

#include <stdlib.h>
#include "my.h"

int my_show_word_array(char *const *tab)
{
    int i = 0;
    char newline[] = "\n";

    while (tab[i] != NULL){
        my_putstr(tab[i]);
        my_putstr(newline);
        i++;
    }
    return (0);
}
