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

int num_occurences(char *str, char to_check)
{
    int i = 0;
    int res = 0;
    int len = strlen(str);

    while (i < len){
        if (str[i] == to_check)
            ++res;
        ++i;
    }
    return (res);
}

static void print_inv_matrix(float **matrix, int nb_rows, int nb_cols, int type)
{
    printf("Key matrix:\n");
    for (int i = 0; i < nb_rows; ++i) {
        for (int j = 0; j < nb_cols - 1; ++j)
            printf("%.3f \t", matrix[i][j]);
        if (type == 0) {
            printf("%.3f", matrix[i][nb_cols - 1]);
            printf("\n");
        }
        if (type == 1 && i == nb_rows - 1) {
            printf("%.3f", matrix[i][nb_cols - 1]);
        }
        if (type == 1 && i != nb_rows - 1)
            printf("%.3f\t", matrix[i][nb_cols - 1]);
    }
}

static void print_char(float chare)
{
    if ((int)chare == '\0') {
        return;
    }
    printf("%c", (int)round(chare));
}

static void print_decrypted_matrix(float **matrix, int nb_rows, int nb_cols,
    int type)
{
    printf("\nDecrypted message:\n");
    for (int i = 0; i < nb_rows; ++i) {
        for (int j = 0; j < nb_cols; ++j) {
            print_char(matrix[i][j]);
        }
    }
    printf("\n");
}

static void print_matrix(float **matrix, int nb_rows, int nb_cols, int type)
{
    for (int i = 0; i < nb_rows; ++i) {
        for (int j = 0; j < nb_cols - 1; ++j)
            printf("%.0f \t", matrix[i][j]);
        if (type == 0) {
            printf("%.0f", matrix[i][nb_cols - 1]);
            printf("\n");
        }
        if (type == 1 && i == nb_rows - 1) {
            printf("%.0f", matrix[i][nb_cols - 1]);
        }
        if (type == 1 && i != nb_rows - 1)
            printf("%.0f\t", matrix[i][nb_cols - 1]);
    }
}

int crypt_matrix(int argc, char **argv)
{
    int len = strlen(argv[2]);
    int matrix_size = sqrt(my_find_prime_sup(len));
    int big_len = ((strlen(argv[1]) / matrix_size) +
        (strlen(argv[1]) % matrix_size));
    float **matrix_2 = create_matrix_from_string(argv[2]);
    float **matrix = create_matrix_from_string_n(argv[1], matrix_size);
    float **muled = NULL;

    if (matrix_size > 3)
        big_len = big_len - (matrix_size - 3);
    muled = multiply_matrix_real(matrix, matrix_2,
        (int[4]){big_len,
            matrix_size, matrix_size, matrix_size});
    printf("Key matrix:\n");
    print_matrix(matrix_2, matrix_size, matrix_size, 0);
    printf("\nEncrypted message:\n");
    print_matrix(muled, big_len, matrix_size, 1);
    printf("\n");
    return (0);
}

static float **make_inv(int key_size, float **matrix)
{
    float **inv = NULL;

    if (key_size == 3)
        inv = threexthree_inverse(matrix);
    else if (key_size == 2)
        inv = twoxtwo_inverse(matrix);
    else
        return (NULL);
    return (inv);
}

int decrypt_matrix(int argc, char **argv)
{
    int len = strlen(argv[2]);
    int key_size = sqrt(my_find_prime_sup(len));
    int size = ceil((num_occurences(argv[1], ' ') /
            sqrt(my_find_prime_sup(strlen(argv[2]))))) + 1;
    float **muled = create_matrix_from_num_string_n(argv[1], key_size);
    float **matrix = create_matrix_from_string(argv[2]);
    float **inv = NULL;
    float **result = NULL;

    inv = make_inv(key_size, matrix);
    if (inv == NULL)
        return (-1);
    result = multiply_matrix_real(muled, inv,
        (int[4]){size - 1, key_size, key_size, key_size});
    print_inv_matrix(inv, key_size, key_size, 0);
    print_decrypted_matrix(result, size - 1, key_size, 1);
    return (0);
}

int cipher(int argc, char **argv)
{
    if (argc != 4)
        return (84);
    if (strlen(argv[1]) == 0 || strlen(argv[2]) == 0)
        return (84);
    if (atoi(argv[argc - 1]) == 0) {
        crypt_matrix(argc, argv);
        return (0);
    }
    if (atoi(argv[argc - 1]) == 1) {
        if (decrypt_matrix(argc, argv) == -2) {
            return (84);
        }
        return (0);
    }
    return (84);
}
