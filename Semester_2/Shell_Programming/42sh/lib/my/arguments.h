/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** arguments
*/

#ifndef ARGUMENTS_H_
    #define ARGUMENTS_H_

    #include <sys/wait.h>
    #include "tree.h"

    #define SPECI_VAR_AMT 6

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
    char **history;
    int hist_index;
    int size_of_cwd;
    tree_t **trees;
} args_t;

typedef struct inhibitor_states {
    int in_quotes;
    int in_dquotes;
    int in_backticks;
    int paren_depth;
    int last_was_delim;
} inhib_states_t;

typedef struct {
    char *str;
    char *(*fptr)(args_t *args, char *value);
} speci_vars_t;

char *last_return(args_t *args, char *value);
char *arg_nb(args_t *args, char *value);
char *cmd_name(args_t *args, char *value);
char *amt_of_arg(args_t *args, char *value);
char *shell_pid(args_t *args, char *value);
char *arg_list(args_t *args, char *value);
char *bg_pid(args_t *args, char *value);

static const speci_vars_t SPECI_VARS[] = {
    {"$?", &last_return},
    {"$0", &cmd_name},
    {"$#", &amt_of_arg},
    {"$$", &shell_pid},
    {"$*", &arg_list},
    {"$!", &bg_pid},
};

#endif
