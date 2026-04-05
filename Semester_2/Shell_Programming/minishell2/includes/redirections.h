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
    int (*func)(char *where);
} redirections_t;

static const struct redirections redirection_array[] = {
    {"<", &redirection_s},
    {"<<", &redirection_ss},
    {">", &redirection_b},
    {">>", &redirection_bb},
    {NULL, NULL}};

#endif
