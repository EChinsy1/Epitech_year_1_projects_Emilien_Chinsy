/*
** EPITECH PROJECT, 2026
** amazed
** File description:
** struct_shenanigans
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "intake.h"
#include "my_string.h"
#include "macros.h"
#include "prints.h"
#include "amazed.h"

static void free_other(tmp_room_t *room, char **wordarr)
{
    if (room == NULL)
        free_wordarr(wordarr);
    else
        free(room);
}

tmp_room_t *create_room(char *input, rooms_t *graph)
{
    int len = len_deli(input, ' ');
    tmp_room_t *room = malloc(sizeof(tmp_room_t));
    char **wordarr = my_str_to_wordarr(input, ' ');

    if (room == NULL || wordarr == NULL){
        free_other(room, wordarr);
        return NULL;
    }
    room->name = my_strdup(wordarr[0]);
    room->coords[0] = my_getnbr(wordarr[1]);
    room->coords[1] = my_getnbr(wordarr[2]);
    if (has_room(wordarr[0], graph->head) ||
        has_coords(room->coords, graph->head)){
        free(room);
        free_wordarr(wordarr);
        return NULL;
    }
    room->next = NULL;
    free_wordarr(wordarr);
    return room;
}

int add_room(char *input, rooms_t *graph, int *nb_rooms)
{
    tmp_room_t *room = create_room(input, graph);

    if (room == NULL)
        return FAIL;
    if (graph->head == NULL)
        graph->head = room;
    else {
        room->next = graph->head;
        graph->head = room;
    }
    *nb_rooms = *nb_rooms + 1;
    return SUCCESS;
}

rooms_t *create_graph(void)
{
    rooms_t *graph = malloc(sizeof(rooms_t));

    if (graph == NULL)
        return NULL;
    graph->end = -1;
    graph->start = -1;
    graph->len_mat = -1;
    graph->head = NULL;
    graph->nb_robi = 0;
    graph->names = NULL;
    graph->matrix = NULL;
    graph->robots = NULL;
    graph->liens = NULL;
    graph->occupied = NULL;
    graph->ind_lien = 0;
    return graph;
}
