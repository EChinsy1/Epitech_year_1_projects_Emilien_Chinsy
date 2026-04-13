/*
** EPITECH PROJECT, 2025
** my_compute_square_root
** File description:
** returns the square root of a number if it is a whole number.
*/

#include "my.h"

int my_compute_square_root(int nb)
{
    int checker;

    for (int i = 1; i <= 46340; i++){
        checker = i * i;
        if (checker == nb){
            return i;
        }
        if (checker > nb){
            return (0);
        }
    }
    return (0);
}
