/*
** EPITECH PROJECT, 2026
** exclamation_mark
** File description:
** exclamation_mark
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "history.h"
#include "macros.h"
#include "my.h"

static char *get_history_command(history_list_t *history, char *str)
{
    history_node_t *curr = history->tail;
    size_t len = strlen(str);
    char *true_command = strtok(str, " ");

    while (curr != NULL) {
        if (strncmp(curr->command, true_command, len) == 0)
            return curr->command;
        curr = curr->next;
    }
    return NULL;
}

static char *get_history_id(history_list_t *history, int id)
{
    history_node_t *curr = history->head;

    while (curr != NULL) {
        if (curr->id == id)
            return curr->command;
        curr = curr->next;
    }
    return NULL;
}

static int string_excla_mark(char **buffer, history_list_t *history, size_t *s)
{
    char *str = *buffer + 1;
    char *command = NULL;
    size_t len = strlen(str);

    if (len > 0 && str[len - 1] == '\n')
        str[len - 1] = '\0';
    command = get_history_command(history, str);
    if (command == NULL) {
        fprintf(stderr, "%s: Event not found.\n", str);
        return ERROR;
    }
    free(*buffer);
    *buffer = strdup(command);
    if (*buffer == NULL)
        return ERROR;
    *s = strlen(*buffer) + 1;
    printf("%s", *buffer);
    return SUCCESS;
}

static int id_excla_mark(char **buffer, history_list_t *history, size_t *size)
{
    int id = 0;
    char *endptr = NULL;
    char *command = NULL;

    id = strtol(*buffer + 1, &endptr, 10);
    if (*endptr != '\0' && *endptr != '\n')
        return ERROR;
    command = get_history_id(history, id);
    if (command == NULL) {
        fprintf(stderr, "%d: Event not found.\n", id);
        return ERROR;
    }
    free(*buffer);
    *buffer = strdup(command);
    if (*buffer == NULL)
        return ERROR;
    *size = strlen(*buffer) + 1;
    printf("%s", *buffer);
    return SUCCESS;
}

static int double_excla_mark(char **buffer, history_list_t *history, size_t *s)
{
    char *last_command = NULL;

    if (history->tail == NULL) {
        fprintf(stderr, "0: Event not found.\n");
        return ERROR;
    }
    last_command = history->tail->command;
    free(*buffer);
    *buffer = strdup(last_command);
    if (*buffer == NULL)
        return ERROR;
    *s = strlen(*buffer) + 1;
    printf("%s", *buffer);
    return SUCCESS;
}

int check_exclamation_mark(char **buffer, history_list_t *history, size_t *s)
{
    int id = 0;

    if (*buffer == NULL || history == NULL)
        return SUCCESS;
    if ((*buffer)[0] == '!') {
        if ((*buffer)[1] == '!')
            return double_excla_mark(buffer, history, s);
        if (is_int(*buffer + 1) == SUCCESS)
            return id_excla_mark(buffer, history, s);
        else
            return string_excla_mark(buffer, history, s);
    }
    return SUCCESS;
}
