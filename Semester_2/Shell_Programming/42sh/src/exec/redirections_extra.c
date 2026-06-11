/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** redirections
*/


#include <fcntl.h>
#include <limits.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "my.h"
#include "redirections.h"

int infixe_redirections(tree_t *tree)
{
    int i = 0;
    int redirect_success = 0;
    int other_success = 0;

    if (tree == NULL)
        return (0);
    other_success += infixe_redirections(tree->left_node);
    while (redirection_array[i].name != NULL) {
        if (my_strncmp(redirection_array[i].name,
                tree->symbol, strlen(redirection_array[i].name)) == 0) {
            redirect_success = redirection_array[i].func(tree->value[1],
                tree->symbol);
        }
        ++i;
        if (redirect_success == 1)
            return (1);
    }
    other_success += infixe_redirections(tree->right_node);
    return (other_success);
}
