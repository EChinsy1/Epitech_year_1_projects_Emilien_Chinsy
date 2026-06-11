/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** tree
*/

#ifndef TREE_H_
    #define TREE_H_

    #include <stddef.h>

    #define IN 0
    #define OUT 1

typedef enum {
    EXECUTE,
    AND,
    OR,
    BACKGROUND,
} sep_pos_t;

typedef struct tree {
    char *symbol;
    char **value;
    size_t index;
    struct tree *left_node;
    struct tree *right_node;
} tree_t;

static const char *const SEPARATORS[] = {
    ";",
    "&&",
    "||",
    "&",
    NULL
};

static const char *const SYMBOLS[] = {
    "|",
    "<",
    "<<",
    " ",
    ">",
    "2>&1",
    ">>",
    ((void *)0),
};

void infixe(tree_t *tree);

#endif
