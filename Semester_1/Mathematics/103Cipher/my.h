/*
** EPITECH PROJECT, 2025
** my_h
** File description:
** a
*/

#ifndef MY_H_
    #define MY_H_

int cipher(int argc, char **argv);
int my_find_prime_sup(double len);
float **multiply_matrix_real(float **matrix_1, float **matrix_2, int *stat);
float **make_matrix(int height, int length);
float **create_matrix_from_string(char *string);
float **create_matrix_from_string_n(char *string, int n);
float **make_transpose(float **matrix, int height, int length);
float **twoxtwo_inverse(float **matrix);
float threexthree_cofactor(float **matrix, int i, int j);
//float threexthree_determinant(float **matrix);
float **threexthree_inverse(float **matrix);
float **create_matrix_from_num_string_n(char *string, int n);
int num_occurences(char *str, char to_check);

#endif
