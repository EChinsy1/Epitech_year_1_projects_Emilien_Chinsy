/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** redirections
*/

#ifndef REDIRECTIONS_H_
    #define REDIRECTIONS_H_

typedef struct redirections {
    char *name;
    int (*func)(char *where, char *call);
} redirections_t;

static const struct redirections redirection_array[] = {
    {"<<", &redirection_ss},
    {"<", &redirection_s},
    {">", &redirection_b},
    {"2>&1", &redirection_b_n_err},
    {">>", &redirection_bb},
    {NULL, NULL}};

#endif
