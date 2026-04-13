/*
** EPITECH PROJECT, 2025
** my compute power
** File description:
** a my compute power function 
*/

#include "my.h"

long double my_compute_power(int base, int result)
{
    int exp = base;
    long double result_long = result;
    
    while (exp != 0) {
        result_long *= base;
        --exp;
    }
    return (result_long);
}
