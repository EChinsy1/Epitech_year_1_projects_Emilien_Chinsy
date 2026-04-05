/*
** EPITECH PROJECT, 2026
** amazed
** File description:
** file containing stuff
*/

#include <stdio.h>
#include <stdlib.h>
#include "amazed.h"
#include "macros.h"

int start_handler(char *input, rooms_t *graph, int *nb_rooms)
{
    int result = ERROR;
    size_t size = 0;

    getline(&input, &size, stdin);
    if (graph->start == -1)
        result = get_room(input, graph, nb_rooms);
    if (result == NEXT)
        graph->start = *nb_rooms - 1;
    free(input);
    return result;
}

int free_and_return(char *to_free, int to_return)
{
    free(to_free);
    return to_return;
}
