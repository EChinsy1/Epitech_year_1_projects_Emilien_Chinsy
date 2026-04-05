/*
** EPITECH PROJECT, 2025
** 108trigo
** File description:
** exponential
*/

#include <stdio.h>
#include <stdlib.h>
#include "my.h"

static void end_free(double **matrix, double **current_power, int n)
{
    free_matrix(current_power, n);
    free_matrix(matrix, n);
}

double **calculate_exponential(double **matrix, int n)
{
    double **power_matrix = make_identity_matrix(n);
    double **temp = NULL;
    double **result_matrix = make_identity_matrix(n);

    for (unsigned int i = 1; i < NUM_OF_ITERATIONS; ++i) {
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
