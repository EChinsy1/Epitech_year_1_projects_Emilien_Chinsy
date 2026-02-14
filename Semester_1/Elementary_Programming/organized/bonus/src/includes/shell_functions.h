/*
** EPITECH PROJECT, 2025
** shell functions
** File description:
** shell functions
*/

#ifndef SHELL_FUNCTIONS
    #define SHELL_FUNCTIONS

    #define BUF_SIZE 1000

typedef struct shell_funcs {
    char *name;
    int (*fptr)(void *data, char **args);
} shell_funcs_t;

const struct shell_funcs SHELL_FUNCS[] = {
    {"add", &add},
    {"sort", &sort},
    {"del", &del},
    {"disp", &disp},
    {"empty", &empty},
    {"parse", &parse},
    {"stats", &stats},
    {"help", &help},
    {"save", &save},
    {((void *)0), ((void *)0)}
};

#endif
