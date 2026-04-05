/*
** EPITECH PROJECT, 2025
** struct
** File description:
** a struct that holds vector
*/

#ifndef STRUCT_H_
    #define STRUCT_H_

typedef struct math_holder {
    char flag;
    float **(*fptr)(float, float);
} math_holder_t;

static const struct math_holder EACH_MATH_FUNC[] = {
    {'r', &make_rotation_matrix},
    {'s', &make_reflection_matrix},
    {'t', &make_translation_matrix},
    {'z', &make_scaling_matrix}};

static const char ONE_ARG[] = {
    'r',
    's',
    '\0'};

#endif
