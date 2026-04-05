/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** arguments
*/

#ifndef ARGUMENTS_H_
    #define ARGUMENTS_H_

typedef struct arguments {
    char **env;
    int last_command_return;
    char ***command_args;
    char *buffer;
    char *old_dir;
    char *home_dir;
} args_t;

#endif
