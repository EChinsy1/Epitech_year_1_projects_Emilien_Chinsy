/*
** EPITECH PROJECT, 2026
** amazed
** File description:
** getliaison
*/

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "amazed.h"
#include "my_string.h"
#include "macros.h"
#include "prints.h"

static int get_index(char *name, tmp_room_t *head)
{
    tmp_room_t *tmp = head;
    int index = 0;

    if (name == NULL)
        return NOPE;
    while (tmp){
        if (my_strcmp(tmp->name, name) == SUCCESS)
            return index;
        tmp = tmp->next;
        index++;
    }
    return NOPE;
}

void add_link(rooms_t *graph, char **links)
{
    int index_1 = get_index(links[0], graph->head);
    int index_2 = get_index(links[1], graph->head);

    if (index_1 == -1 || index_2 == -1)
        return;
    graph->liens[graph->ind_lien] = my_strdup(links[0]);
    graph->ind_lien++;
    graph->liens[graph->ind_lien] = my_strdup(links[1]);
    graph->ind_lien++;
    graph->matrix[index_1][index_2] = 1;
    graph->matrix[index_2][index_1] = 1;
    free_wordarr(links);
}

bool has_coords(int *coords, tmp_room_t *head)
{
    tmp_room_t *tmp = head;

    while (tmp){
        if (tmp->coords[0] == coords[0] && tmp->coords[1] == coords[1])
            return true;
        tmp = tmp->next;
    }
    return false;
}

bool has_room(char *name, tmp_room_t *head)
{
    tmp_room_t *tmp = head;

    while (tmp){
        if (my_strcmp(tmp->name, name) == SUCCESS)
            return true;
        tmp = tmp->next;
    }
    return false;
}

int is_link(char **input, tmp_room_t *head)
{
    if (input == NULL)
        return FALSE;
    if (input[0][0] == '#'){
        free_wordarr(input);
        return NOPE;
    }
    if (my_lenwordarr(input) < 2){
        free_wordarr(input);
        return FALSE;
    }
    if ((input[2]) != NULL && input[2][0] != '#'){
        free_wordarr(input);
        return FALSE;
    }
    if (has_room(input[0], head) && has_room(input[1], head))
        return TRUE;
    else
        return FALSE;
}

int get_link(rooms_t *graph)
{
    char *input = NULL;
    int link = TRUE;
    size_t size = 0;
    char **line = NULL;

    while (link != FALSE){
        if (getline(&input, &size, stdin) == -1){
            free(input);
            return FAIL;
        }
        if (input[my_strlen(input) - 1] == '\n')
            input[my_strlen(input) - 1] = '\0';
        line = my_str_to_wordarr(input, '-');
        link = is_link(line, graph->head);
        if (link == TRUE)
            add_link(graph, line);
    }
    free(input);
    return SUCCESS;
}
