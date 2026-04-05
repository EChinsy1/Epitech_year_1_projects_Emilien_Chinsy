/*
** EPITECH PROJECT, 2025
** my_sh_parsing_tree
** File description:
** parse and put in tree to be able to handle stuff better
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "my.h"
#include "macros.h"
#include "tree.h"

static int get_number_of_commands(char *str)
{
    int i = 0;
    int num = 1;

    if (str == NULL)
        return (0);
    while (str[i] != '\0') {
        if (str[i] == ';')
            ++num;
        ++i;
    }
    return (num);
}

static int is_symbol(char *string)
{
    int i = 0;

    while (SYMBOLS[i + 1] != NULL) {
        if (my_strcmp(string, SYMBOLS[i + 1]) == 0)
            return (1);
        ++i;
    }
    if (my_strcmp(string, SYMBOLS[0]) == 0)
        return (2);
    return (0);
}

static char **make_command_array(char **word_array, int start, int end)
{
    char **command_array = NULL;

    if (word_array == NULL || start == end)
        return (NULL);
    command_array = my_calloc(sizeof(char *), ((end - start) + 1));
    for (int i = start; i < end; ++i)
        command_array[i - start] = my_strdup(word_array[i]);
    command_array[end - start] = NULL;
    return (command_array);
}

static int get_command(tree_t **tree, char **word_array, int *i)
{
    int start = *i;
    char **command_array = NULL;

    while (word_array[*i] != NULL && is_symbol(word_array[*i]) == 0) {
        ++(*i);
    }
    command_array = make_command_array(word_array, start, *i);
    (*tree)->value = command_array;
    --(*i);
    return (0);
}

static int get_redirection(tree_t **tree, char **word_array, int *i)
{
    int start = *i;
    char *symbol = word_array[start];
    char **command_array = NULL;

    (*i) = (*i) + REDIR_LEN;
    if (word_array[*i - 1] == NULL) {
        command_array = make_command_array(word_array, start, *i - 1);
        (*i) = (*i) - REDIR_LEN;
    } else {
        command_array = make_command_array(word_array, start, *i);
        --(*i);
    }
    insert_tree(tree, command_array, symbol);
    return (0);
}

static tree_t *get_pipe(tree_t *tree, char **word_array, int *i, int symbol)
{
    tree_t *new_tree = NULL;
    int start = *i;
    char **pipe_array = my_calloc(sizeof(char *), 2);

    pipe_array[0] = my_strdup("|");
    pipe_array[1] = NULL;
    init_tree(&new_tree, pipe_array, "|");
    new_tree->left_node = tree;
    ++(*i);
    init_tree(&new_tree->right_node, NULL, " ");
    for (; word_array[*i] && word_array[*i][0] != '|'
        && word_array[*i][0] != '\n'; ++(*i)) {
        symbol = is_symbol(word_array[*i]);
        if (symbol == 0)
            get_command(&new_tree->right_node, word_array, i);
        if (symbol == 1)
            get_redirection(&new_tree->right_node, word_array, i);
    }
    --(*i);
    return (new_tree);
}

static tree_t *make_tree(char **word_array)
{
    int i = 0;
    int symbol = 0;
    tree_t *tree = NULL;

    init_tree(&tree, NULL, " ");
    if (!tree || !word_array || !word_array[0])
        return NULL;
    for (; word_array[i]; ++i) {
        symbol = is_symbol(word_array[i]);
        if (symbol == COMMAND)
            get_command(&tree, word_array, &i);
        if (symbol == REDIRECTION)
            get_redirection(&tree, word_array, &i);
        if (symbol == PIPE)
            tree = get_pipe(tree, word_array, &i, symbol);
    }
    free_word_array(word_array);
    return (tree);
}

tree_t **parse_trees(char *str, args_t *args)
{
    int num_of_commands = get_number_of_commands(str);
    char **word_array = my_str_to_word_array(str, ";");
    tree_t **tree_array = NULL;

    if (num_of_commands == 0 || str == NULL || word_array == NULL)
        return (NULL);
    tree_array = malloc(sizeof(tree_t *) * (num_of_commands + 1));
    for (int i = 0; i < num_of_commands; ++i) {
        tree_array[i] = NULL;
        if (word_array[i] != NULL)
            tree_array[i] = make_tree(
                my_str_to_word_array(word_array[i], " \t"));
    }
    tree_array[num_of_commands] = NULL;
    free_word_array(word_array);
    for (int i = 0; tree_array && tree_array[i]; ++i)
        tree_array = validate_tree(tree_array, i, args);
    return (tree_array);
}
