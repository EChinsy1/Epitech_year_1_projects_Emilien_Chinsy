/*
** EPITECH PROJECT, 2025
** 108trigo
** File description:
** matrix lib functions remade
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "math.h"
#include "my.h"

void free_matrix(double **m, int n)
{
    for (int i = 0; i < n; i++)
        free(m[i]);
    free(m);
}

double **copy_matrix(double **matrix, int n)
{
    double **copy = calloc(sizeof(double *), (n + 1));

    if (!copy)
        return (NULL);
    for (int i = 0; i < n; i++) {
        copy[i] = calloc(sizeof(double), (n + 1));
        for (int j = 0; j < n; j++)
            copy[i][j] = matrix[i][j];
    }
    return (copy);
}

static void print_matrix(double **matrix, int n)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j++)
            printf("%.2f\t", matrix[i][j]);
        printf("%.2f", matrix[i][n - 1]);
        printf("\n");
    }
}

static int my_find_prime_sup(double nb)
{
    double sqrted = sqrt(nb);
    int result = ceil(sqrted);

    return (pow(result, 2));
}

static int get_size_of_char_star_star(char **value)
{
    int i = 0;

    for (; value[i]; ++i){
    }
    return (i);
}

static double put_value(char **value, int num, int len)
{
    if (num < len)
        return (strtod(value[num], NULL));
    else
        return (0);
}

static double **create_matrix_from_argv(char **value, int *n)
{
    int len = get_size_of_char_star_star(value);
    int prime_sup = sqrt(my_find_prime_sup(len));
    double **matrix = make_matrix(prime_sup);
    int num = 0;

    *n = prime_sup;
    for (int i = 0; i < prime_sup; ++i) {
        for (int j = 0; j < prime_sup; ++j){
            matrix[i][j] = put_value(value, num, len);
            ++num;
        }
    }
    return (matrix);
}

static int verify_argv(char **argv)
{
    char *end = NULL;

    for (int i = 2; argv[i]; ++i) {
        strtol(argv[i], &end, 10);
        if (*argv[i] != '\0' && *end != '\0')
            return (-1);
    }
    return (0);
}

static double **execute_operation(int argc, char **argv, int *n)
{
    double **result = NULL;
    double **matrix = NULL;

    if (verify_argv(argv) < 0)
        return (matrix);
    matrix = create_matrix_from_argv(&argv[2], n);
    for (int i = 0; i < NUM_OF_OP; ++i) {
        if (strcmp(argv[1], OPERATIONS[i].name) == 0)
            result = OPERATIONS[i].fptr(matrix, *n);
    }
    return (result);
}

int main(int argc, char **argv)
{
    double **result = NULL;
    int n = 0;

    if (argc < 3 || sqrt(argc - 2) != (int)sqrt(argc - 2))
        return (84);
    result = execute_operation(argc, argv, &n);
    if (result == NULL)
        return (84);
    print_matrix(result, n);
    free_matrix(result, n);
    return (0);
}
