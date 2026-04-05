/*
** EPITECH PROJECT, 2025
** math part one
** File description:
** a file that contains part one of the mathing functions
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


static float remove_minus_zero(float element)
{
    if (element < -0.000 && element > -0.005)
        element = 0.00;
    return (element);
}

float **make_identity_matrix(int height, int length)
{
    float **matrix = malloc(sizeof(float *) * (height + 1));

    for (int i = 0; i < height; ++i) {
        matrix[i] = malloc(sizeof(float) * (length + 1));
        for (int j = 0; j < length; ++j) {
            matrix[i][j] = 0;
        }
        matrix[i][i] = 1;
    }
    matrix[height] = NULL;
    return (matrix);
}

float **make_translation_matrix(float i, float j)
{
    float **matrix = make_identity_matrix(3, 3);

    printf("Translation along vector (%.0f, %.0f)\n", i, j);
    matrix[0][2] = i;
    matrix[1][2] = j;
    return (matrix);
}

float **make_scaling_matrix(float m, float n)
{
    float **matrix = make_identity_matrix(3, 3);

    printf("Scaling by factors %.0f and %.0f\n", m, n);
    matrix[0][0] = m;
    matrix[1][1] = n;
    return (matrix);
}

float **make_rotation_matrix(float teta, float nothing)
{
    float **matrix = make_identity_matrix(3, 3);

    printf("Rotation by a %.0f degree angle\n", teta);
    teta = teta * (M_PI / 180);
    matrix[0][0] = cos(teta);
    matrix[0][1] = -sin(teta);
    matrix[1][0] = sin(teta);
    matrix[1][1] = cos(teta);
    for (int i = 0; i < 2; ++i){
        for (int j = 0; j < 2; ++j){
            matrix[i][j] = remove_minus_zero(matrix[i][j]);
        }
    }
    return (matrix);
}

float **make_reflection_matrix(float teta, float nothing)
{
    float **matrix = make_identity_matrix(3, 3);

    printf("Reflection over an axis");
    printf(" with an inclination angle of %.0f degrees\n", teta);
    teta = teta * (M_PI / 180);
    matrix[0][0] = cos(2 * teta);
    matrix[0][1] = sin(2 * teta);
    matrix[1][0] = sin(2 * teta);
    matrix[1][1] = -cos(2 * teta);
    for (int i = 0; i < 2; ++i){
        for (int j = 0; j < 2; ++j){
            matrix[i][j] = remove_minus_zero(matrix[i][j]);
        }
    }
    return (matrix);
}
