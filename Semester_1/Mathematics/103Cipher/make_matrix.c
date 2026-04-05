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

float **make_matrix(int height, int length)
{
    float **matrix = calloc(sizeof(float *), (height + 1));

    for (int i = 0; i < height; ++i) {
        matrix[i] = calloc(sizeof(float), (length + 1));
        for (int j = 0; j < length; ++j) {
            matrix[i][j] = 0;
        }
    }
    matrix[height] = NULL;
    return (matrix);
}

float **create_matrix_from_string(char *string)
{
    int len = strlen(string);
    int prime_sup = my_find_prime_sup(len);
    float **matrix = make_matrix(sqrt(prime_sup), sqrt(prime_sup));
    char *new_string = calloc(sizeof(char), prime_sup + 1);
    int num = 0;

    strcat(new_string, string);
    for (int i = 0; i < sqrt(prime_sup); ++i) {
        for (int j = 0; j < sqrt(prime_sup); ++j){
            matrix[i][j] = (float)new_string[num];
            ++num;
        }
    }
    return (matrix);
}

float **create_matrix_from_string_n(char *string, int n)
{
    int len = strlen(string);
    int num = 0;
    int max = ((len / n) + (len % n));
    char *new_string = calloc(sizeof(char), len + 2);
    float **matrix = make_matrix(max, n);

    strcat(new_string, string);
    for (int i = 0; i < max; ++i) {
        for (int j = 0; j < n; ++j){
            matrix[i][j] = (int)new_string[num];
            ++num;
        }
    }
    return (matrix);
}

float **create_matrix_from_num_string_n(char *string, int n)
{
    int len = (num_occurences(string, ' ') + 1);
    int max = ((len / n) + (len % n));
    int num = 0;
    char *new_string = string;
    float **matrix = make_matrix(max, n);
    char *temp = NULL;

    for (int i = 0; i < max; ++i) {
        for (int j = 0; j < n; ++j){
            temp = strtok(&new_string[num], " ");
            num += (strlen(temp) + 1);
            matrix[i][j] += atof(temp);
            temp = 0;
        }
    }
    return (matrix);
}

float **make_transpose(float **matrix, int height, int length)
{
    float **transposed_matrix = make_matrix(length, height);

    for (int i = 0; i < length; ++i)
        for (int j = 0; j < height; ++j)
            transposed_matrix[i][j] = matrix[j][i];
    return (matrix);
}
