/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** arguments
*/

#ifndef ARGUMENTS_H_
    #define ARGUMENTS_H_

    #include "tree.h"
    #include "history.h"
    #include "jobs.h"
    #include "alias.h"

typedef struct arguments {
    char **env;
    char **local;
    int argc;
    char **argv;
    int last_command_return;
    pid_t last_pid;
    int was_error;
    char *buffer;
    char *old_dir;
    char *home_dir;
    int size_of_cwd;
    int hist_index;
    tree_t **trees;
    history_list_t *history;
    job_t *jobs;
    history_list_t *tmp;
    history_node_t *tmp_t;
    alias_t **alias;
    int nb_alias;
} args_t;

#endif
