/*
** EPITECH PROJECT, 2026
** 108trigo
** File description:
** this file has the functions
** for the cos part of the project
*/

#include <stdlib.h>
#include <stdio.h>
#include "my.h"

static void end_free(double **matrix, double **current_power, int n)
{
    free_matrix(current_power, n);
    free_matrix(matrix, n);
}

void subtract_two_matrix(double **matrix_1, double **matrix_2, int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            matrix_1[i][j] -= matrix_2[i][j];
}

double **calculate_cos(double **matrix, int n)
{
    double **power_matrix = make_identity_matrix(n);
    double **temp = NULL;
    double **result_matrix = make_identity_matrix(n);

    for (unsigned int i = 2; i < NUM_OF_ITERATIONS * 2; i += 2) {
        power_matrix = multiply_square_matrix(power_matrix, matrix, n);
        power_matrix = multiply_square_matrix(power_matrix, matrix, n);
        temp = copy_matrix(power_matrix, n);
        divide_by_double(temp, compute_factorial(i), n);
        if (i % 4 == 0) {
            add_two_matrix(result_matrix, temp, n);
        } else
            subtract_two_matrix(result_matrix, temp, n);
        free_matrix(temp, n);
    }
    free_matrix(power_matrix, n);
    free_matrix(matrix, n);
    return (result_matrix);
}
