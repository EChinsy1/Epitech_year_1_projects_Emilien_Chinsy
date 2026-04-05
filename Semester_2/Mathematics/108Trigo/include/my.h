/*
** EPITECH PROJECT, 2025
** 104neutrinos
** File description:
** Header file for 104neutrinos
*/

#ifndef MY_H
    #define MY_H

    #define NUM_OF_OP 5
    #define NUM_OF_ITERATIONS 100

void divide_by_double(double **matrix_1, double value, int n);
void add_two_matrix(double **matrix_1, double **matrix_2, int n);
void subtract_two_matrix(double **matrix_1, double **matrix_2, int n);
double **multiply_square_matrix(double **matrix_1,
    double **matrix_2, int n);
double **make_identity_matrix(int n);
double **make_matrix(int n);
double **calculate_exponential(double **matrix, int n);
double **calculate_cos(double **matrix, int n);
double **calculate_cosh(double **matrix, int n);
double **calculate_sin(double **matrix, int n);
double **calculate_sinh(double **matrix, int n);
void free_matrix(double **m, int n);
double **copy_matrix(double **matrix, int n);
double compute_factorial(int power);

typedef struct name_n_func {
    char *name;
    double **(*fptr)(double **matrix, int n);
} name_n_func_t;

static const name_n_func_t OPERATIONS[] = {
    {"EXP", &calculate_exponential},
    {"COS", &calculate_cos},
    {"SIN", &calculate_sin},
    {"COSH", &calculate_cosh},
    {"SINH", &calculate_sinh},
};

#endif
