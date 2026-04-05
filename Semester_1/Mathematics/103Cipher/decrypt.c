/*
** EPITECH PROJECT, 2025
** decrypt
** File description:
** decrypt file
*/

#include <math.h>
#include <stdlib.h>
#include "my.h"

static float twoxtwo_determinant(float **matrix)
{
    float determinant = ((matrix[0][0] * matrix[1][1]) -
        (matrix[0][1] * matrix[1][0]));

    return (determinant);
}

float **twoxtwo_inverse(float **matrix)
{
    double determinant = twoxtwo_determinant(matrix);
    float temp = matrix[0][0];

    if (determinant == 0)
        return (NULL);
    matrix[0][0] = matrix[1][1];
    matrix[1][1] = temp;
    matrix[0][1] = -matrix[0][1];
    matrix[1][0] = -matrix[1][0];
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j) {
            matrix[i][j] = matrix[i][j] / determinant;
        }
    return (matrix);
}

float threexthree_cofactor(float **matrix, int i, int j)
{
    float cofactor;
    int sign = pow(-1, i + j);
    float part_one;
    float part_two;
    float result;

    i--;
    j--;
    part_one = matrix[(i + 1) % 3][(j + 1) % 3] *
        matrix[(i + 2) % 3][(j + 2) % 3];
    part_two = matrix[(i + 1) % 3][(j + 2) % 3] *
        matrix[(i + 2) % 3][(j + 1) % 3];
    result = part_one - part_two;
    cofactor = result * sign;
    if (j == 1)
        cofactor = 0 - cofactor;
    return (cofactor);
}

static float threexthree_determinant(float **matrix)
{
    float determinant = 0;

    determinant += (matrix[0][0] * threexthree_cofactor(matrix, 1, 1));
    determinant += (matrix[0][1] * threexthree_cofactor(matrix, 1, 2));
    determinant += (matrix[0][2] * threexthree_cofactor(matrix, 1, 3));
    return (determinant);
}

float **threexthree_inverse(float **matrix)
{
    float **inverse = malloc(sizeof(float *) * 4);
    float determinant = threexthree_determinant(matrix);

    if (determinant == 0)
        return (NULL);
    for (int i = 0; i < 3; ++i) {
        inverse[i] = malloc(sizeof(float) * 3);
        for (int j = 0; j < 3; ++j) {
            inverse[i][j] = (threexthree_cofactor(matrix, j + 1, i + 1)
                / determinant);
        }
        inverse[i][1] = inverse[i][1] * -1;
    }
    inverse[3] = NULL;
    return (inverse);
}
