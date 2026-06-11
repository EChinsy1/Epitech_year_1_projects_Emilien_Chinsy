/*
** EPITECH PROJECT, 2025
** my_sh_parsing_tree
** File description:
** parse and put in tree to be able to handle stuff better
*/

#include <unistd.h>
#include <string.h>
#include "macros.h"
#include <stdlib.h>
#include "my.h"
#include "tree.h"

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

void init_tree(tree_t **tree, char **value, char *symbol, size_t index)
{
    (*tree) = my_calloc(sizeof(tree_t), 2);
    (*tree)->value = value;
    (*tree)->symbol = my_strdup(symbol);
    (*tree)->left_node = NULL;
    (*tree)->right_node = NULL;
    (*tree)->index = index;
}

void insert_tree(tree_t **tree, char **value, char *symbol, size_t index)
{
    int i = 0;

    if (value == NULL || symbol == NULL)
        return;
    if ((*tree) == NULL) {
        init_tree(tree, value, symbol, index);
        return;
    }
    if (cmp_symbol_strength(symbol, (*tree)->symbol) == -1) {
        insert_tree(&(*tree)->left_node, value, symbol, index);
    } else {
        insert_tree(&(*tree)->right_node, value, symbol, index);
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
