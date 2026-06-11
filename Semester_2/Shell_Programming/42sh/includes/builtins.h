/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** builtins
*/

#ifndef BUILTINS_H_
    #define BUILTINS_H_

    #define BUILTINS 18
    #define EXIT 4

    #include <stdio.h>
    #include "arguments.h"
    #include "my.h"

typedef struct built_in_funcs {
    char *name;
    int (*func)(args_t *args, char **command_array);
} built_in_funcs_t;

int jobs(args_t *args, char **command_array);
int kill_job(args_t *args, char **command_array);
int put_to_fg(args_t *args, char **command_array);
int run_in_bg(args_t *args, char **command_array);
int stop(args_t *args, char **command_array);
int which(args_t *args, char **command_array);
int where_builtin(args_t *args, char **command_array);
int prompt_builtin(args_t *args, char **env);

static const struct built_in_funcs builtinfuncs[] = {
    {"setenv", &setenv_func},
    {"set", &set_func},
    {"unsetenv", &unsetenv_func},
    {"env", &print_env},
    {"exit", &exit_func},
    {"cd", &cd_func},
    {"history", &history_funct},
    {"jobs", &jobs},
    {"alias", &alias_funct},
    {"kill", &kill_job},
    {"fg", &put_to_fg},
    {"bg", &run_in_bg},
    {"stop", &stop},
    {"pipe", &my_pipe},
    {"hello", &shrek},
    {"which", &which},
    {"where", &where_builtin},
    {"help", &prompt_builtin},
    {NULL, NULL}};

#endif
