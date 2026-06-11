/*
** EPITECH PROJECT, 2026
** scripting
** File description:
** scripting
*/

#ifndef SCRIPTING_H_
    #define SCRIPTING_H_

    #include <stdio.h>
    #include "arguments.h"

int not_impelemented(char *buffer, args_t *args, FILE *file);
int foreach(char *buffer, args_t *args, FILE *file);
int repeat(char *buffer, args_t *args, FILE *file);
int where(char *buffer, args_t *args, FILE *file);
int which(args_t *args, char **command_array);
int where_builtin(args_t *args, char **command_array);

int exec(char *buffer, args_t *args);

typedef struct keyword_and_func {
    char *keyword;
    int (*fptr)(char *buffer, args_t *args, FILE *file);
} k_n_f_t;

static const struct keyword_and_func keywords[] = {
    {"if", &not_impelemented},
    {"then", &not_impelemented},
    {"else", &not_impelemented},
    {"endif", &not_impelemented},
    {"while", &not_impelemented},
    {"end", &not_impelemented},
    {"where", &where},
    {"foreach", &foreach},
    {"repeat", &repeat},
    {NULL, NULL}
};

#endif
