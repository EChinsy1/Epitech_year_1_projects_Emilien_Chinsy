/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** builtins
*/

#ifndef BUILTINS_H_
    #define BUILTINS_H_

    #include "arguments.h"

typedef struct built_in_funcs {
    char *name;
    int (*func)(args_t *args);
} built_in_funcs_t;

static const struct built_in_funcs builtinfuncs[] = {
    {"setenv", &setenv_func},
    {"unsetenv", &unsetenv_func},
    {"env", &print_env},
    {"exit", &exit_func},
    {"cd", &cd_func},
    {NULL, NULL}};

#endif
