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
    if (args->trees != NULL) {
        for (int i = 0; args->trees[i]; ++i) {
            infixe_free(args->trees[i]);
        }
        free(args->trees);
    }
    for (int i = 0; args->history[i]; ++i)
        free(args->history[i]);
    free(args->buffer);
    free(args->old_dir);
    free(args->home_dir);
    free_word_array(args->env);
    exit(args->last_command_return);
}
