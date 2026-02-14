/*
** EPITECH PROJECT, 2025
** my_swap
** File description:
** first task of day 4,
** I have to write a function that,
** using pointers, swaps the content of two integers.
*/

#include "my.h"

void my_swap(int *a, int *b)
{
    int temp = 0;

    temp = *a;
    *a = *b;
    *b = temp;
}
