/*
** EPITECH PROJECT, 2025
** my.h
** File description:
** a
*/

#ifndef MY_H_
    #define MY_H_

    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
int show_help(void);
float **make_identity_matrix(int height, int length);
float **make_translation_matrix(float i, float j);
float **make_scaling_matrix(float m, float n);
float **make_rotation_matrix(float teta, float nothing);
float **make_reflection_matrix(float teta, float nothing);
float *create_vector(float x, float y, float z);
float *multiply_matrix_1(float *threexone, float **threexthree);
float **multiply_matrix_real(float **matrix_1, float **matrix_2);
float **free_matrix(float **matrix, int size);
int architect(int argc, char **argv);
int verify_args(int argc, char **argv);
float **do_operation(float **matrix, int *i, char **av);

#endif
