/*
** EPITECH PROJECT, 2025
** my_compute_power_rec
** File description:
** tas 4 day 5, recursive way to calculate powers
*/

#include "my.h"

static long power_calc_rec(int nb, int p, long result)
{
    if ((result > 2147483647) || (nb == 0)){
        return (0);
    } else if (p == 0){
        return (1);
    } else {
        result = result * nb;
        return (nb * (power_calc_rec(nb, p - 1, result)));
    }
}

int my_compute_power_rec(int nb, int p)
{
    long result = 1;
    int true_result;

    if ((nb == 1) || ((nb == 0) && (p == 0))){
        return (1);
    } else if ((nb == 0) && (p == 0)){
        return (0);
    }
    result = power_calc_rec(nb, p, result);
    true_result = result;
    return (true_result);
}
