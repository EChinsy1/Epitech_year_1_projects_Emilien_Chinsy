/*
** EPITECH PROJECT, 2025
** validate_trees
** File description:
** validate_trees
*/

#include <stdlib.h>
#include "arguments.h"
#include "tree.h"
#include "my.h"

void free_the_tree(args_t **args)
{
    int j = 0;

    for (; (*args)->trees[j] == NULL; ++j)
        j = j;
    for (; (*args)->trees[j]; ++j)
        infixe_free((*args)->trees[j]);
}

void free_tree_not_end(args_t **args)
{
    free_the_tree(args);
    free((*args)->trees);
    free_not_end(*args);
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

static tree_t **validate_tree(tree_t **trees, int i, args_t *args)
{
    tree_t *tree = trees[i];

    if (trees == NULL || tree == NULL)
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

tree_t **validate_trees(tree_t **tree_array, args_t *args)
{
    for (int i = 0; tree_array && tree_array[i]; ++i)
        tree_array = validate_tree(tree_array, i, args);
    return (tree_array);
}
