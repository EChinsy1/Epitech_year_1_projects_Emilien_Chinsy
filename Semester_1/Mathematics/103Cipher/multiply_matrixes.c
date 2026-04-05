/*
** EPITECH PROJECT, 2025
** bs
** File description:
** bs
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "my.h"

static float **add_line(float ***matrixes,
    float **final_result,
    int i,
    int *stat)
{
    for (int j = 0; j < stat[3]; ++j) {
        for (int k = 0; k < stat[1]; ++k)
            final_result[i][j] =
                final_result[i][j] +
                (matrixes[0][i][k] * matrixes[1][k][j]);
    }
    return (final_result);
}

float **multiply_matrix_real(float **matrix_1, float **matrix_2, int *stat)
{
    float **final_result;
    float **matrixes[2];

    matrixes[0] = matrix_1;
    matrixes[1] = matrix_2;
    if (stat[1] != stat[2])
        return (NULL);
    final_result = calloc(sizeof(float *), stat[0]);
    if (final_result == NULL)
        return (NULL);
    for (int i = 0; i < stat[0]; ++i) {
        final_result[i] = calloc(sizeof(float), stat[3]);
        if (final_result[i] == NULL)
            return NULL;
    }
    for (int i = 0; i < stat[0]; ++i) {
        final_result = add_line(matrixes, final_result, i, stat);
    }
    return (final_result);
}
