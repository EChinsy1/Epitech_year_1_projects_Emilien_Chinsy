/*
** EPITECH PROJECT, 2026
** 108trigo
** File description:
** this file has the functions
** for the sinh part of the project
*/

#include <stdlib.h>
#include <stdio.h>
#include "my.h"

double compute_factorial(int power)
{
    double fact = 1;

    for (int i = 1; i <= power; i++)
        fact *= i;
    return fact;
}

static void end_free(double **matrix, double **current_power, int n)
{
    free_matrix(current_power, n);
    free_matrix(matrix, n);
}

double **calculate_sinh(double **matrix, int n)
{
    double **power_matrix = copy_matrix(matrix, n);
    double **temp = NULL;
    double **result_matrix = copy_matrix(matrix, n);

    for (unsigned int i = 3; i < NUM_OF_ITERATIONS * 2; i += 2) {
        power_matrix = multiply_square_matrix(power_matrix, matrix, n);
        power_matrix = multiply_square_matrix(power_matrix, matrix, n);
        temp = copy_matrix(power_matrix, n);
        divide_by_double(temp, compute_factorial(i), n);
        add_two_matrix(result_matrix, temp, n);
        free_matrix(temp, n);
    }
    free_matrix(power_matrix, n);
    free_matrix(matrix, n);
    return (result_matrix);
}
