/*
** EPITECH PROJECT, 2025
** arg and sort func
** File description:
** a struct that
*/

#ifndef ARG_N_SORT_FUNC_
    #define ARG_N_SORT_FUNC_

typedef struct arg_n_sort_func {
    char *arg;
    int (*cmp_func)(void *one, void *two, char **args, int i);
} arg_n_sort_t;

const struct arg_n_sort_func SORT_FUNCS[] = {
    {"TYPE", &type_cmp_func},
    {"NAME", &name_cmp_func},
    {"ID", &id_cmp_func},
    {((void *)0), ((void *)0)}};

#endif
