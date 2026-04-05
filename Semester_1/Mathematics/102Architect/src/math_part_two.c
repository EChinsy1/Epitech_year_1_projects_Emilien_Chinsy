/*
** EPITECH PROJECT, 2025
** math part one
** File description:
** a file that contains part one of the mathing functions
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "my.h"

float *create_vector(float x, float y, float z)
{
    float *vector = malloc(sizeof(int) * 3);

    if (vector == NULL)
        return NULL;
    vector[0] = x;
    vector[1] = y;
    vector[2] = z;
    return (vector);
}

float *multiply_matrix_1(float *threexone, float **threexthree)
{
    float *final_vector = create_vector(0, 0, 0);

    for (int i = 0; i < 3; ++i) {
        final_vector[i] = 0;
        for (int j = 0; j < 3; ++j) {
            final_vector[i] += threexone[j] * threexthree[i][j];
        }
    }
    return (final_vector);
}

float **add_line(float **matrix_1,
    float **matrix_2,
    float **final_result,
    int height)
{
    final_result[height] = calloc(sizeof(float), 3);
    if (final_result[height] == NULL)
        return (NULL);
    for (int length = 0; length < 3; ++length) {
        for (int i = 0; i < 3; ++i)
            final_result[height][length] =
                final_result[height][length] +
                (matrix_1[height][i] * matrix_2[i][length]);
    }
    return (final_result);
}

float **multiply_matrix_real(float **matrix_1, float **matrix_2)
{
    float **final_result;

    final_result = calloc(sizeof(float *), 3);
    if (final_result == NULL)
        return (NULL);
    for (int height = 0; height < 3; ++height) {
        final_result = add_line(matrix_1, matrix_2, final_result, height);
    }
    free_matrix(matrix_2, 3);
    return (final_result);
}
