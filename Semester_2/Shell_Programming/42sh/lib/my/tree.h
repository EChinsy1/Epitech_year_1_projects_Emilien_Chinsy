/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** tree
*/

#ifndef TREE_H_
    #define TREE_H_

    #define IN 0
    #define OUT 1

typedef struct tree {
    char *symbol;
    char **value;
    struct tree *left_node;
    struct tree *right_node;
} tree_t;

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
