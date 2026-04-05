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
    char *buffer;
    char *old_dir;
    char *home_dir;
    tree_t **trees;
} args_t;

#endif
