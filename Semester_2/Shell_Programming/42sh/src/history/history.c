/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** history
*/

#include <stdio.h>
#include <string.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include "arguments.h"
#include "macros.h"
#include "history.h"

int add_to_history(history_list_t *list, const char *command)
{
    history_node_t *new_node = NULL;

    if (list == NULL || command == NULL)
        return ERROR;
    new_node = malloc(sizeof(history_node_t));
    if (new_node == NULL)
        return ERROR;
    new_node->command = strdup(command);
    list->total_command++;
    new_node->id = list->total_command;
    new_node->next = NULL;
    new_node->prev = list->tail;
    if (list->tail != NULL)
        list->tail->next = new_node;
    else
        list->head = new_node;
    list->tail = new_node;
    return SUCCESS;
}

int load_history(history_list_t *history)
{
    FILE *fd = fopen(HISTORY_FILE, "r");
    char *line = NULL;
    size_t len = 0;

    if (fd == NULL)
        return ERROR;
    while (getline(&line, &len, fd) != ERROR) {
        line[strlen(line) - 1] = '\0';
        add_to_history(history, line);
    }
    free(line);
    fclose(fd);
    return SUCCESS;
}

history_list_t *init_history(void)
{
    history_list_t *list = calloc(sizeof(history_list_t), 1);

    if (load_history(list) != ERROR)
        return list;
    if (list == NULL)
        return NULL;
    list->head = NULL;
    list->tail = NULL;
    list->total_command = 0;
    return list;
}

int history_funct(args_t *args, UNUSED char**cmd)
{
    history_node_t *current = NULL;

    if (args->history == NULL || args->history->head == NULL) {
        printf("Your history is empty.\n");
        printf("Type something in your terminal to create it.\n");
        return SUCCESS;
    }
    current = args->history->head;
    while (current != NULL) {
        printf("%d\t%s\n", current->id, current->command);
        current = current->next;
    }
    return SUCCESS;
}

int history(char *command, history_list_t *history)
{
    FILE *fd = NULL;

    if (add_to_history(history, command) == ERROR)
        return ERROR;
    fd = fopen(HISTORY_FILE, "a");
    if (fd != NULL) {
        fprintf(fd, "%s\n", command);
        fclose(fd);
    }
    return SUCCESS;
}
