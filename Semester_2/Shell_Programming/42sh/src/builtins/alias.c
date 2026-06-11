/*
** EPITECH PROJECT, 2026
** alias
** File description:
** alias
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "my.h"
#include "macros.h"
#include "arguments.h"

static char *get_true_cmd(char **command_array)
{
    char *true_cmd = calloc(sizeof(char), 1);

    if (command_array[1] == NULL || command_array[2] == NULL)
        return NULL;
    for (int i = 2; command_array[i] != NULL; i++) {
        true_cmd = realloc(true_cmd,
            sizeof(char) * (strlen(command_array[i]) + strlen(true_cmd) + 2));
        true_cmd = strcat(true_cmd, command_array[i]);
        if (command_array[i + 1] != NULL)
            true_cmd = strcat(true_cmd, " ");
    }
    return true_cmd;
}

static int complete_alias(args_t *args, char **command_array)
{
    char *true_cmd = get_true_cmd(command_array);

    if (true_cmd == NULL)
        return ERROR;
    args->alias[args->nb_alias]->alias_command = strdup(command_array[1]);
    args->alias[args->nb_alias]->true_command = strdup(true_cmd);
    if (args->alias[args->nb_alias]->alias_command == NULL ||
        args->alias[args->nb_alias]->true_command == NULL)
        return ERROR;
    args->nb_alias++;
    args->alias[args->nb_alias] = NULL;
    free(true_cmd);
    return SUCCESS;
}

static int update_alias(args_t *args, int idx, char **command_array)
{
    char *true_cmd = get_true_cmd(command_array);

    if (true_cmd == NULL)
        return ERROR;
    free(args->alias[idx]->alias_command);
    free(args->alias[idx]->true_command);
    args->alias[idx]->alias_command = NULL;
    args->alias[idx]->true_command = NULL;
    if (true_cmd == NULL)
        return ERROR;
    args->alias[idx]->alias_command = strdup(command_array[1]);
    args->alias[idx]->true_command = strdup(true_cmd);
    if (args->alias[idx]->alias_command == NULL ||
        args->alias[idx]->true_command == NULL)
        return ERROR;
    free(true_cmd);
    return SUCCESS;
}

static int print_alias(args_t *args)
{
    for (int i = 0; i < args->nb_alias; i++) {
        if (strchr(args->alias[i]->true_command, ' ') != NULL) {
            printf("%s\t(%s)\n", args->alias[i]->alias_command,
                args->alias[i]->true_command);
        } else {
            printf("%s\t%s\n", args->alias[i]->alias_command,
                args->alias[i]->true_command);
        }
    }
    return SUCCESS;
}

static int replace_alias(args_t *args, char *alias_name, char **command_array)
{
    for (int i = 0; i < args->nb_alias; i++) {
        if (strcmp(args->alias[i]->alias_command, alias_name) == 0)
            return update_alias(args, i, command_array);
    }
    return ERROR;
}

int alias_funct(args_t *args, char **command_array)
{
    char **alias_args = NULL;

    if (args == NULL || command_array == NULL)
        return ERROR;
    if (command_array[1] == NULL)
        return print_alias(args);
    if (array_len(command_array) < 3)
        return SUCCESS;
    if (replace_alias(args, command_array[1], command_array) == SUCCESS)
        return SUCCESS;
    args->alias = realloc(args->alias,
        sizeof(alias_t *) * (args->nb_alias + 2));
    if (args->alias == NULL)
        return ERROR;
    args->alias[args->nb_alias] = calloc(sizeof(alias_t), 1);
    if (args->alias[args->nb_alias] == NULL ||
        complete_alias(args, command_array) == ERROR)
        return ERROR;
    free_word_array(alias_args);
    return SUCCESS;
}

int check_alias(char **buffer, alias_t **alias, size_t *s)
{
    size_t len = 0;

    if (*buffer == NULL || alias == NULL)
        return SUCCESS;
    len = strlen(*buffer);
    if (len > 0 && (*buffer)[len - 1] == '\n')
        (*buffer)[len - 1] = '\0';
    for (int i = 0; alias[i] != NULL; i++) {
        if (strcmp(alias[i]->alias_command, *buffer) == SUCCESS) {
            free(*buffer);
            *buffer = strdup(alias[i]->true_command);
        }
    }
    if (*buffer == NULL)
        return ERROR;
    *s = strlen(*buffer);
    return SUCCESS;
}
