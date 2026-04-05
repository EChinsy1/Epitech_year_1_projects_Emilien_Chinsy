/*
** EPITECH PROJECT, 2026
** amazed
** File description:
** file containing the amazed function
*/

#include <stdio.h>
#include <stdlib.h>
#include "amazed.h"
#include "bfs.h"
#include "intake.h"
#include "my_string.h"

static void free_temp_rooms(tmp_room_t *rooms)
{
    if (!rooms)
        return;
    free_temp_rooms(rooms->next);
    free(rooms->name);
    free(rooms);
}

static void free_robots(robot_t *robots)
{
    if (!robots)
        return;
    free_robots(robots->next);
    free(robots);
}

static int init_path(robot_t *robot, int **paths, rooms_t *graph)
{
    int index = 0;

    while (paths[index] != NULL){
        if (graph->occupied[paths[index][1]] == 0){
            robot->path_index = index;
            robot->path_step = 1;
            return 0;
        }
        index++;
    }
    return -1;
}

static void display_movements(robot_t *robot, rooms_t *graph, int moves)
{
    if (moves > 0)
        mini_printf(" ");
    mini_printf("P%d-%s", robot->id, graph->names[robot->room]);
}

static void move_robots(robot_t *robots, int **paths, rooms_t *graph, int moves)
{
    if (!robots)
        return;
    if (robots->path_index < 0){
        if (init_path(robots, paths, graph) < 0)
            return;
    }
    if (robots->path_step >= 0 &&
        graph->occupied[paths[robots->path_index][robots->path_step]] != 1){
        graph->occupied[robots->room] = 0;
        graph->occupied[paths[robots->path_index][robots->path_step]] = 1;
        robots->room = paths[robots->path_index][robots->path_step];
        display_movements(robots, graph, moves);
        robots->path_step++;
        if (paths[robots->path_index][robots->path_step] < 0){
            graph->occupied[robots->room] = 0;
            robots->path_step = -1;
        }
        moves++;
    }
    move_robots(robots->next, paths, graph, moves);
}

static void populate_robots(int amt_of_robots, robot_t **list_addr, int start)
{
    robot_t *robot = NULL;

    if (amt_of_robots == 0)
        return;
    robot = malloc(sizeof(robot_t));
    if (!robot)
        return;
    robot->room = start;
    robot->id = amt_of_robots;
    robot->next = *list_addr;
    robot->path_index = -1;
    robot->path_step = 0;
    *list_addr = robot;
    populate_robots(amt_of_robots - 1, list_addr, start);
}

static int is_over(robot_t *robots)
{
    if (!robots)
        return 1;
    if (robots->path_step >= 0)
        return 0;
    return is_over(robots->next);
}

static void handle_robots(rooms_t *graph, int **paths)
{
    robot_t *robots = NULL;

    populate_robots(graph->nb_robi, &robots, graph->start);
    while (is_over(robots) != 1){
        move_robots(robots, paths, graph, 0);
        mini_printf("\n");
    }
    free_robots(robots);
}

void free_graph(rooms_t *graph)
{
    free_wordarr(graph->names);
    free_int_array(graph->matrix);
    free_temp_rooms(graph->head);
    if (graph->occupied)
        free(graph->occupied);
    for (int i = 0; i < graph->ind_lien; i++)
        free(graph->liens[i]);
    free(graph->liens);
    free(graph);
}

int amazed(void)
{
    rooms_t *graph = get_inputs();
    int **paths = NULL;

    if (!graph)
        return 84;
    display_input(graph);
    graph->occupied = my_calloc(graph->len_mat, sizeof(int));
    paths = get_necessary_paths(graph->nb_robi,
        (int[2]){graph->start, graph->end},
        graph->len_mat, graph->matrix);
    if (!paths || !paths[0]){
        free_graph(graph);
        return 84;
    }
    handle_robots(graph, paths);
    free_graph(graph);
    free_int_array(paths);
    return 0;
}
