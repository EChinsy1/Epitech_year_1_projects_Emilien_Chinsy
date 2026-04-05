/*
** EPITECH PROJECT, 2026
** amazed
** File description:
** getinputs
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

/*
static void put_room(tmp_room_t *room)
{
    my_putstr(room->name);
    my_putchar('\n');
    my_putnbr(room->coords[0]);
    my_putchar('\n');
    my_putnbr(room->coords[1]);
    my_putchar('\n');
}

static void put_rooms(rooms_t *graph)
{
    tmp_room_t *tmp = NULL;

    if (graph == NULL)
        return;
    tmp = graph->head;
    if (tmp == NULL)
        return;
    while (tmp){
        put_room(tmp);
        my_putchar('\n');
        tmp = tmp->next;
    }
    return;
}

static void put_graph(rooms_t *graph)
{
    printf("nb robi %d\n", (graph->nb_robi));
    printf("start %d\n", graph->start);
    printf("end %d\n\n", graph->end);
    put_wordarr(graph->names);
}

void put_matrix(int **matrix, int len_mat)
{
    for (int i = 0; i < len_mat; i++){
        for (int j = 0; j < len_mat; j++){
            my_putnbr(matrix[i][j]);
        }
        my_putchar('\n');
    }
}
*/
static void get_names(rooms_t *graph, int nb_rooms)
{
    tmp_room_t *tmp = graph->head;
    char **names = malloc(sizeof(char *) * (nb_rooms + 1));
    int index = 0;

    if (names == NULL)
        return;
    while (tmp){
        names[index] = my_strdup(tmp->name);
        index++;
        tmp = tmp->next;
    }
    names[index] = NULL;
    graph->names = names;
}

static bool is_start(char *input)
{
    if (my_strcmp(input, "##start") == SUCCESS)
        return true;
    return false;
}

static bool is_end(char *input)
{
    if (my_strcmp(input, "##end") == SUCCESS)
        return true;
    return false;
}

static int get_nb_robots(rooms_t *graph)
{
    char *input = NULL;
    size_t size = 0;

    while (getline(&input, &size, stdin) != -1){
        if (input[0] == '#')
            continue;
        graph->nb_robi = my_getnbr(input);
        free(input);
        return graph->nb_robi;
    }
    return FALSE;
}

static int is_room(char *input)
{
    char **wordarr = my_str_to_wordarr(input, ' ');

    if (wordarr == NULL)
        return FALSE;
    if (my_lenwordarr(wordarr) < 3){
        free_wordarr(wordarr);
        return FALSE;
    }
    if (is_number(wordarr[1]) == FALSE){
        free_wordarr(wordarr);
        return FALSE;
    }
    if ((wordarr[3]) != NULL && wordarr[3][0] != '#'){
        free_wordarr(wordarr);
        return FALSE;
    }
    free_wordarr(wordarr);
    return TRUE;
}

int get_room(char *input, rooms_t *graph, int *nb_rooms)
{
    if (is_room(input)){
        if (add_room(input, graph, nb_rooms) == FAIL)
            return ERROR;
        return NEXT;
    } else
        return ERROR;
}

static int special_input(char *input, rooms_t *graph, int *nb_rooms)
{
    size_t size = 0;
    int result = ERROR;

    if (is_start(input))
        return start_handler(input, graph, nb_rooms);
    if (is_end(input)){
        getline(&input, &size, stdin);
        if (graph->end == -1)
            result = get_room(input, graph, nb_rooms);
        if (result == NEXT)
            graph->end = *nb_rooms - 1;
        free(input);
        return result;
    }
    return NOPE;
}

static int check_link(char *input, rooms_t *graph, int *nb_rooms)
{
    char **line = my_str_to_wordarr(input, '-');
    int result = is_link(line, graph->head);

    if (result == FALSE)
        return ERROR;
    if (result == TRUE){
        graph->liens = my_calloc(sizeof(char *),
            ((*nb_rooms * *nb_rooms * 2) + 1));
        graph->matrix = create_matrix(*nb_rooms);
        add_link(graph, line);
        return NEXT;
    }
    free(line);
    return result;
}

static int get_until_links(rooms_t *graph, int *nb_rooms)
{
    int result = 0;
    char *input = NULL;
    size_t size = 0;

    while (getline(&input, &size, stdin) != -1){
        input[my_strlen(input) - 1] = '\0';
        result = special_input(input, graph, nb_rooms);
        if (result == ERROR)
            return free_and_return(input, ERROR);
        if (input[0] == '#' || result == NEXT ||
            get_room(input, graph, nb_rooms) == NEXT){
            continue;
        }
        result = check_link(input, graph, nb_rooms);
        if (result != NOPE)
            return free_and_return(input, result);
    }
    return free_and_return(input, ERROR);
}

rooms_t *get_inputs(void)
{
    rooms_t *graph = create_graph();
    int nb_rooms = 0;

    if (graph == NULL)
        return NULL;
    if (get_nb_robots(graph) == 0 ||
        get_until_links(graph, &nb_rooms) == ERROR){
        free_graph(graph);
        return NULL;
    }
    if (graph->start == -1 || graph->end == -1 || graph->head == NULL){
        free_graph(graph);
        return NULL;
    }
    graph->len_mat = nb_rooms;
    get_link(graph);
    get_names(graph, nb_rooms);
    graph->start = nb_rooms - graph->start - 1;
    graph->end = nb_rooms - graph->end - 1;
    return graph;
}
