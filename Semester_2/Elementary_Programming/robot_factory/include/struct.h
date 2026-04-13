/*
** EPITECH PROJECT, 2025
** robot factory
** File description:
** struct
*/

#ifndef STRUCT_H_
    #define STRUCT_H_

    #include "op.h"

typedef struct indexes_s {
    char *name;
    char *value;
    int line;
} idx_t;

typedef struct is_index {
    char *name;
    char is_index;
} is_in_t;

typedef struct instructions_s {
    char *name;
    char *comment;
    char ***commands;
    idx_t **indexes;
    int *sizes;
} ins_t;

#endif
