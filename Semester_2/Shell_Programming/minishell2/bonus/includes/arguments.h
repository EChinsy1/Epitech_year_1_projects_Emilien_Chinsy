/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** arguments
*/

#ifndef ARGUMENTS_H_
    #define ARGUMENTS_H_

    #include "tree.h"

typedef struct arguments {
    char **env;
    int last_command_return;
    int was_error;
    char *buffer;
    char *old_dir;
    char *home_dir;
    char **history;
    int hist_index;
    tree_t **trees;
} args_t;

#endif
