/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** minishell1
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "my.h"
#include "arguments.h"

void free_alias(alias_t **alias)
{
    if (alias == NULL)
        return;
    for (int i = 0; alias[i] != NULL; i++) {
        free(alias[i]->alias_command);
        free(alias[i]->true_command);
        free(alias[i]);
    }
    free(alias);
}

void free_list(history_list_t *history)
{
    history_node_t *curr = history->head;
    history_node_t *next = NULL;

    if (history == NULL)
        return;
    while (curr != NULL) {
        next = curr->next;
        free(curr->command);
        free(curr);
        curr = next;
    }
    free(history);
}

int exit_func(args_t *args, char **command_array)
{
    if (args->jobs != NULL){
        dprintf(2, "exit: there are unfinished jobs\n");
        return 1;
    }
    if (args->trees != NULL) {
        for (int i = 0; args->trees[i]; ++i)
            infixe_free(args->trees[i]);
        free(args->trees);
    }
    free(args->buffer);
    free(args->old_dir);
    free(args->home_dir);
    remove(BACKTICK_FILE);
    if (args->alias)
        free_alias(args->alias);
    if (args->history)
        free_list(args->history);
    free_word_array(args->local);
    free_word_array(args->env);
    exit(args->last_command_return);
}
