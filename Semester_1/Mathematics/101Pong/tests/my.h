/*
** EPITECH PROJECT, 2025
** my.h
** File description:
** a
*/

#ifndef MY_H_
    #define MY_H_

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <math.h>
    #include <ctype.h>
    #include "struct.h"
int my_argv_is_valid(int argc, char **argv);
int pong(int argc, char **argv);
double calc_angle(vector_t *vector);
void make_vector(double x, double y, double z, vector_t *vector);
void make_velocity(vector_t *coords,
    vector_t *coords2,
    vector_t *velocity);
double calc_norm(vector_t *vector);

#endif
