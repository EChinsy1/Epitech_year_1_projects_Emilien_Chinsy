/*
** EPITECH PROJECT, 2025
** my_sort_in_array
** File description:
** task 4 day 6, i have to return a sorted array
*/

#include "my.h"

static void swapper(int *a, int *b)
{
    int temp = *a;

    if (*a > *b){
        *a = *b;
        *b = temp;
    }
}

int my_sort_int_array(int *array, int size)
{
    for (int i = 0; i < size - 1; i++){
        for (int j = 0; j < size - i - 1; j++){
            swapper(&array[j], &array[j + 1]);
        }
    }
    return (0);
}
