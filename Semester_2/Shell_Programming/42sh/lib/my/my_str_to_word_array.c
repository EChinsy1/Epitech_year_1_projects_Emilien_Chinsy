/*
** EPITECH PROJECT, 2025
** my_str_to_word_array
** File description:
** write a function that splits a string into word
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "my.h"
#include "arguments.h"
#include "macros.h"

int in_delim(char *delim, char needle)
{
    int i = 0;

    while (delim[i] != '\0') {
        if (delim[i] == needle) {
            return (1);
        }
        ++i;
    }
    return (0);
}

static void update_quote_state(char c, inhib_states_t *state)
{
    if (c == '\'' && state->in_dquotes == 0 && state->in_backticks == 0
        && state->paren_depth == 0)
        state->in_quotes = !(state->in_quotes);
    if (c == '"' && state->in_quotes == 0 && state->in_backticks == 0
        && state->paren_depth == 0)
        state->in_dquotes = !(state->in_dquotes);
    if (c == '`' && state->in_quotes == 0 && state->in_dquotes == 0
        && state->paren_depth == 0)
        state->in_backticks = !(state->in_backticks);
    if (c == '(' && state->in_quotes == 0 && state->in_dquotes == 0
        && state->in_backticks == 0)
        state->paren_depth++;
    if (c == ')' && state->in_quotes == 0 && state->in_dquotes == 0
        && state->in_backticks == 0)
        state->paren_depth--;
}

static int skip_delim(char *str, char *delim, int i)
{
    inhib_states_t state = {0, 0, 0, 0, 0};

    while (str[i] != '\0') {
        update_quote_state(str[i], &state);
        if (!state.in_quotes && !state.in_dquotes && !state.in_backticks
            && state.paren_depth == 0 && in_delim(delim, str[i]) == 1)
            i++;
        else
            break;
    }
    return (i);
}

static int find_word_end(char *str, char *delim, int i)
{
    inhib_states_t state = {0, 0, 0, 0, 0};

    while (str[i] != '\0') {
        update_quote_state(str[i], &state);
        if (!state.in_quotes && !state.in_dquotes && !state.in_backticks
            && state.paren_depth == 0 && in_delim(delim, str[i]) == 1)
            break;
        i++;
    }
    return (i);
}

static void process_char(char c, char *delim, inhib_states_t *state, int *num)
{
    update_quote_state(c, state);
    if (!state->in_quotes && !state->in_dquotes && !state->in_backticks
        && state->paren_depth == 0 && in_delim(delim, c) == 1
        && c != '\n' && state->last_was_delim == 0) {
        (*num)++;
        state->last_was_delim = 1;
    } else if ((state->in_quotes || state->in_dquotes || state->in_backticks
            || state->paren_depth > 0)
        || (in_delim(delim, c) == 0 && c != '\n' && c != '\0'))
        state->last_was_delim = 0;
}

int get_num_of_words(char *str, char *delim)
{
    int i = 0;
    int num = 1;
    inhib_states_t state = {0, 0, 0, 0, 1};

    if (!str)
        return (-1);
    while (str[i] && in_delim(delim, str[i]))
        i++;
    while (str[i]) {
        process_char(str[i], delim, &state, &num);
        i++;
    }
    if (state.last_was_delim == 1)
        num--;
    return (num);
}

static void print_unmatched_error(inhib_states_t *state)
{
    if (state->in_quotes) {
        write(2, "Unmatched '''.\n", 16);
        return;
    }
    if (state->in_dquotes) {
        write(2, "Unmatched '\"'.\n", 15);
        return;
    }
    if (state->in_backticks) {
        write(2, "Unmatched '`'.\n", 15);
        return;
    }
    if (state->paren_depth > 0) {
        write(2, "Too many ('s.\n", 15);
        return;
    }
    if (state->paren_depth < 0) {
        write(2, "Too many )'s.\n", 15);
        return;
    }
}

int check_inhibitors_closed(char *str)
{
    int i = 0;
    inhib_states_t state = {0, 0, 0, 0, 0};

    while (str[i]) {
        update_quote_state(str[i], &state);
        i++;
    }
    if (state.in_quotes || state.in_dquotes || state.in_backticks
        || state.paren_depth != 0){
        print_unmatched_error(&state);
        return 0;
    }
    return (1);
}

static char **extras(char **word_array, int words, args_t *args, char *delim)
{
    word_array[words] = NULL;
    if (!word_array[words - 1])
        return (word_array);
    if (word_array[words - 1][my_strlen(word_array[words - 1]) - 1] == '\n')
        word_array[words - 1][my_strlen(word_array[words - 1]) - 1] = '\0';
    if (args == NULL)
        return (word_array);
    for (int i = 0; i < words && word_array[i]; ++i) {
        if (word_array[i][0] == '$')
            word_array[i] = find_in_env(word_array[i], args);
        if (word_array[i][0] == '!')
            word_array[i] = find_in_history(word_array[i], args);
    }
    if (delim[0] == SPACE_CHAR)
        word_array = apply_globbings(word_array);
    return (word_array);
}

char **my_str_to_word_array(char *str, char *delim, args_t *args)
{
    int words = get_num_of_words(str, delim);
    char **word_array = NULL;
    int start = 0;
    int end = 0;

    if (words <= 0)
        return (NULL);
    word_array = my_calloc(sizeof(char *), words + 1);
    if (!check_inhibitors_closed(str))
        return (NULL);
    for (int i = 0; i < words; ++i) {
        start = skip_delim(str, delim, start);
        end = find_word_end(str, delim, start);
        if (end != start) {
            word_array[i] = my_calloc(sizeof(char), (end - start + 1));
            my_strncat(word_array[i], &str[start], end - start);
        }
        start = end;
    }
    return (extras(word_array, words, args, delim));
}
