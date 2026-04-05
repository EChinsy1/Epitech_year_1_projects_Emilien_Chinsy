/*
** EPITECH PROJECT, 2025
** 104neutrinos
** File description:
** File that does the required calculations
*/

#include <math.h>
#include <stdio.h>

long double arithmetic_mean(long double n, long double a, long double new_val)
{
    long double result = 0.00;

    result = ((a * n) + new_val) / (n + 1);
    return result;
}

long double standard_dev(long double n, long double sd,
    long double a, long double new_val)
{
    long double result = 0.00;

    result = ((sd * sd) + ((pow(a - new_val, 2) / (n + 1))));
    result = result * (n / (n + 1));
    result = sqrt(result);
    return (result);
}

long double new_root_mean_square(long double n, long double rms,
    long double new_val)
{
    long double result = 0.00;

    for (int i = 0; i < n; i++)
        result += (1 / n) * pow(rms, 2);
    result = sqrt(result);
    return result;
}

long double actual_root_mean_square(long double sd, long double a)
{
    long double result = 0.00;
    long double variance = sd * sd;
    long double arit_mean_sq = a * a;

    result = sqrtl(variance + arit_mean_sq);
    return (result);
}

long double harmonic_mean(long double n, long double h, long double new_val)
{
    long double result = 0.00;

    result = ((n + 1) / ((n / h) + (1 / new_val)));
    return result;
}
