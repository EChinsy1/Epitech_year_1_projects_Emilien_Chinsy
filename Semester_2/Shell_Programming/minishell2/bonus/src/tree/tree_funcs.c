/*
** EPITECH PROJECT, 2025
** my_sh_parsing_tree
** File description:
** parse and put in tree to be able to handle stuff better
*/

#include <unistd.h>
#include <stdio.h>
#include "macros.h"
#include <stdlib.h>
#include "my.h"
#include "tree.h"

//error handling, oublie pas que si le premier truc qui est pas un espace
// c'est une symbole, autre que ; tu mets Invalid null command

static int cmp_symbol_strength(char *symbol1, char *symbol2)
{
    int i = 0;

    while (SYMBOLS[i] != NULL) {
        if (symbol1[0] == SYMBOLS[i][0])
            return (-1);
        if (symbol2[0] == SYMBOLS[i][0])
            return (1);
        ++i;
    }
    return (0);
}

void init_tree(tree_t **tree, char **value, char *symbol)
{
    (*tree) = my_calloc(sizeof(tree_t), 2);
    (*tree)->value = value;
    (*tree)->symbol = my_strdup(symbol);
    (*tree)->left_node = NULL;
    (*tree)->right_node = NULL;
}

void insert_tree(tree_t **tree, char **value, char *symbol)
{
    int i = 0;

    if (value == NULL || symbol == NULL)
        return;
    if ((*tree) == NULL) {
        init_tree(tree, value, symbol);
        return;
    }
    if (cmp_symbol_strength(symbol, (*tree)->symbol) == -1) {
        insert_tree(&(*tree)->left_node, value, symbol);
    } else {
        insert_tree(&(*tree)->right_node, value, symbol);
    }
}

void infixe_free(tree_t *tree)
{
    int i = 0;

    if (tree != NULL){
        infixe_free(tree->left_node);
        infixe_free(tree->right_node);
        free_word_array(tree->value);
        free(tree->symbol);
        free(tree);
    }
}

int count_commands(tree_t *tree)
{
    int i = 1;
    tree_t *temp_tree = tree;

    while (temp_tree->symbol[0] != ' ') {
        ++i;
        temp_tree = temp_tree->left_node;
    }
    return (i);
}

static tree_t **write_n_return(tree_t **tree,
    int in_or_out, args_t **args, int i)
{
    if (in_or_out == OUT)
        my_putstr(2, "Ambiguous output redirect.\n");
    else
        my_putstr(2, "Ambiguous input redirect.\n");
    for (int j = 0; tree[j]; ++j)
        infixe_free(tree[i]);
    free(tree);
    (*args)->last_command_return = 1;
    return (NULL);
}

static int validate_redirections(tree_t *tree,
    tree_t **trees, args_t **args, int i)
{
    if (tree->right_node && tree->right_node->value[1] == NULL) {
        my_putstr(2, "Missing name for redirect.\n");
        for (int j = 0; trees[j]; ++j)
            infixe_free(trees[j]);
        free(trees);
        (*args)->last_command_return = 1;
        return (INVALID);
    }
    if (tree->left_node && tree->left_node->value[1] == NULL) {
        my_putstr(2, "Missing name for redirect.\n");
        for (int j = 0; trees[j]; ++j)
            infixe_free(trees[j]);
        free(trees);
        (*args)->last_command_return = 1;
        return (INVALID);
    }
    return (0);
}

static tree_t **if_null_command(tree_t **trees, args_t **args, int i)
{
    my_putstr(2, "Invalid null command.\n");
    for (int j = 0; trees[j]; ++j)
        infixe_free(trees[j]);
    free(trees);
    (*args)->last_command_return = 1;
    return (NULL);
}

static tree_t **validate_cmd_in_tree(tree_t **trees,
    tree_t *tree, int i, args_t **args)
{
    if (tree != NULL && tree->value == NULL && !tree->symbol)
        return (trees);
    if (validate_redirections(tree, trees, args, i) == INVALID)
        return (NULL);
    if (tree->value == NULL)
        return (if_null_command(trees, args, i));
    if (i > 0 && tree->right_node)
        return (write_n_return(trees, OUT, args, i));
    if (tree->right_node && (tree->right_node->right_node ||
            tree->right_node->left_node))
        return (write_n_return(trees, OUT, args, i));
    if (tree->left_node && (tree->left_node->right_node ||
            tree->left_node->left_node))
        return (write_n_return(trees, IN, args, i));
    return (trees);
}

tree_t **validate_tree(tree_t **trees, int i, args_t *args)
{
    tree_t *tree = trees[i];

    if (trees == NULL || tree == NULL || tree->value == NULL)
        return (NULL);
    for (int j = 0; tree->symbol && tree->symbol[0] == '|'; ++j) {
        if (validate_redirections(tree->right_node, trees, &args, i) == INVALID)
            return (NULL);
        if (tree->right_node && tree->right_node->value == NULL)
            return (if_null_command(trees, &args, i));
        if (tree->right_node->left_node)
            return (write_n_return(trees, IN, &args, i));
        if (j > 0 && tree->right_node->right_node)
            return (write_n_return(trees, OUT, &args, i));
        if (tree->right_node->right_node &&
            (tree->right_node->right_node->right_node ||
                tree->right_node->right_node->left_node))
            return (write_n_return(trees, OUT, &args, i));
        tree = tree->left_node;
    }
    return (validate_cmd_in_tree(trees, tree, i, &args));
}
/*
void infixe(tree_t *tree)
{
    int i = 0;

    if (tree != NULL){
        infixe(tree->left_node);
        printf("tree->symbol = %s\n", tree->symbol);
        for (int i = 0; tree->value[i]; ++i)
            printf("value = %s\n", tree->value[i]);
        printf("next\n");
        infixe(tree->right_node);
    }
}
*/
