/*
** EPITECH PROJECT, 2026
** amazed
** File description:
** file containing functions to display the input results
*/

#include <stddef.h>
#include "amazed.h"
#include "my_string.h"

static tmp_room_t *get_room_from_name(tmp_room_t *rooms, char *name)
{
    if (my_strcmp(name, rooms->name) == 0)
        return rooms;
    return get_room_from_name(rooms->next, name);
}

static void display_rooms(rooms_t *graph)
{
    tmp_room_t *current_room = NULL;

    for (int i = graph->len_mat - 1; i >= 0; i--){
        current_room = get_room_from_name(graph->head, graph->names[i]);
        if (i == graph->start)
            mini_printf("##start\n");
        if (i == graph->end)
            mini_printf("##end\n");
        mini_printf("%s %d %d\n", graph->names[i],
            current_room->coords[0], current_room->coords[1]);
    }
}

static void display_tunnels(rooms_t *graph)
{
    int index = 0;

    mini_printf("#tunnels\n");
    while (graph->liens[index] != NULL){
        mini_printf("%s-%s\n", graph->liens[index],
            graph->liens[index + 1]);
        index += 2;
    }
}

void display_input(rooms_t *graph)
{
    mini_printf("#number_of_robots\n%d\n", graph->nb_robi);
    mini_printf("#rooms\n");
    display_rooms(graph);
    display_tunnels(graph);
    mini_printf("#moves\n");
}
