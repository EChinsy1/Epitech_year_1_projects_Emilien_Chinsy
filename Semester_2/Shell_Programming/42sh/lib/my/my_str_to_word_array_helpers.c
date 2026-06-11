/*
** EPITECH PROJECT, 2025
** my_str_to_word_array
** File description:
** write a function that splits a string into word
*/

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "my.h"
#include "arguments.h"
#include "macros.h"

static int get_key_len(char *str)
{
    int i = 0;

    while (str[i] && (str[i] == '_' ||
            (str[i] >= 'A' && str[i] <= 'Z') ||
            (str[i] >= 'a' && str[i] <= 'z') ||
            (str[i] >= '0' && str[i] <= '9')))
        i++;
    return i;
}

static char *get_from_env(char *key, int key_len, char **env, char *value)
{
    char *res = NULL;

    for (int i = 0; env && env[i]; ++i) {
        if (my_strncmp(key, env[i], key_len) == 0
            && env[i][key_len] == '=') {
            res = my_strdup(&env[i][key_len + 1]);
            free(value);
            return res;
        }
    }
    return NULL;
}

static char *get_from_local(char *key, int key_len, char **local, char *value)
{
    char *res = NULL;

    for (int i = 0; local && local[i]; ++i) {
        if (my_strncmp(key, local[i], key_len) == 0
            && local[i][key_len] == '\t') {
            res = my_strdup(&local[i][key_len + 1]);
            free(value);
            return res;
        }
    }
    return NULL;
}

static char *undefined_var(char *key, char *value, args_t *args)
{
    dprintf(2, "%s: Undefined variable.", key);
    args->last_command_return = 1;
    free(value);
    return my_strdup("");
}

static char *get_speci_var(args_t *args, char *value)
{
    char *endptr = NULL;
    int nb = 0;

    for (size_t i = 0; i < SPECI_VAR_AMT; i++)
        if (strcmp(value, SPECI_VARS[i].str) == 0)
            return SPECI_VARS[i].fptr(args, value);
    nb = strtol(value + 1, &endptr, 10);
    if (*endptr != 0)
        return NULL;
    return arg_nb(args, value);
}

char *find_in_env(char *value, args_t *args)
{
    char *key;
    char *res;
    int key_len;

    if (!value[1])
        return value;
    res = get_speci_var(args, value);
    if (res != NULL)
        return res;
    key = &value[1];
    key_len = get_key_len(key);
    res = get_from_env(key, key_len, args->env, value);
    if (res)
        return res;
    res = get_from_local(key, key_len, args->local, value);
    if (res)
        return res;
    return undefined_var(key, value, args);
}

/* old version, too long
char *find_in_env(char *value, args_t *args)
{
    if (!value[1])
        return value;
    if (value[1] == '?') {
        free(value);
        return (my_strdup(my_itoa(args->last_command_return)));
    }
    for (int i = 0; args->env != NULL && args->env[i]; ++i) {
        if (my_strncmp(&value[1], args->env[i], my_strlen(&value[1])) == 0) {
            free(value);
            return (my_strdup(&args->env[i][find_equal(args->env[i]) - 1]));
        }
    }
    for (int i = 0; args->local != NULL && args->local[i]; ++i) {
        if (my_strncmp(&value[1], args->local[i], my_strlen(&value[1])) == 0) {
            free(value);
            return (my_strdup(&args->local[i][find_tab(args->local[i]) - 1]));
        }
    }
    dprintf(2, "%s: Undefined variable.", &value[1]);
    free(value);
    return (my_strdup(""));
}
*/
char *find_in_history(char *value, args_t *args)
{
    int pos = 0;

    for (int i = 0; args->history[i]; ++i) {
        printf("%s & %s\n", &value[1], args->history[i]);
        if (my_strncmp(&value[1], args->history[i],
                my_strlen(&value[1])) == 0) {
            free(value);
            return (my_strdup(args->history[i]));
        }
    }
    return (value);
}

void free_word_array(char **word_array)
{
    if (word_array == NULL)
        return;
    for (int i = 0; word_array[i]; ++i) {
        free(word_array[i]);
    }
    free(word_array);
}
