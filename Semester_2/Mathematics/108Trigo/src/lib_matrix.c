/*
** EPITECH PROJECT, 2025
** 108trigo
** File description:
** matrix lib functions remade
*/

#include <stdio.h>
#include <stdlib.h>
#include "my.h"

double **make_matrix(int size)
{
    double **matrix = calloc(sizeof(double *), (size + 1));

    if (matrix == NULL)
        return (NULL);
    for (int i = 0; i < size; ++i) {
        matrix[i] = calloc(sizeof(double), (size + 1));
        if (matrix[i] == NULL)
            return (NULL);
        for (int j = 0; j < size; ++j) {
            matrix[i][j] = 0;
        }
    }
    matrix[size] = NULL;
    return (matrix);
}

static double do_i_put_a_one(int i, int j)
{
    if (i == j)
        return (1);
    return (0);
}

double **make_identity_matrix(int n)
{
    double **Identity_matrix = make_matrix(n);

    if (Identity_matrix == NULL)
        return (NULL);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; ++j)
            Identity_matrix[i][j] = do_i_put_a_one(i, j);
    return (Identity_matrix);
}

static double **apply_multiplication(double **matrix_1, double **matrix_2,
    double **multiplied, int values[3])
{
    for (int k = 0; k < values[2]; k++)
        multiplied[values[0]][values[1]] +=
            matrix_1[values[0]][k] * matrix_2[k][values[1]];
    return (multiplied);
}

double **multiply_square_matrix(double **matrix_1,
    double **matrix_2, int n)
{
    double **multiplied = make_matrix(n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            multiplied = apply_multiplication(matrix_1,
                matrix_2, multiplied, (int [3]){i, j, n});
    free_matrix(matrix_1, n);
    return (multiplied);
}

void add_two_matrix(double **matrix_1, double **matrix_2, int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            matrix_1[i][j] += matrix_2[i][j];
}

void divide_by_double(double **matrix_1, double value, int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            matrix_1[i][j] /= value;
}
