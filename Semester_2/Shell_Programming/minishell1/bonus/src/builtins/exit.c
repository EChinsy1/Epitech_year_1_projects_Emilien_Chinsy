/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** minishell1
*/

#include <unistd.h>
#include <stdlib.h>
#include "my.h"
#include "arguments.h"

int exit_func(args_t *args, char **command_array)
{
    for (int i = 0; args->command_args[i]; ++i)
        free_word_array(args->command_args[i]);
    free(args->command_args);
    free(args->buffer);
    free(args->old_dir);
    free(args->home_dir);
    free_word_array(args->env);
    exit(args->last_command_return);
}
