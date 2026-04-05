/*
** EPITECH PROJECT, 2026
** pathfinding
** File description:
** pathfinding
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "my.h"
#include "struct.h"
#include "test.h"

static int get_next_food(coords_t **all_coords, int movements,
    int *which_f, int *distance_f)
{
    int temp = 0;

    for (int i = 0; all_coords[1][i].x != -1; ++i) {
        temp = abs(all_coords[2][0].x - all_coords[1][i].x) +
            abs(all_coords[2][0].y - all_coords[1][i].y);
        if (temp < (*distance_f)) {
            (*distance_f) = temp;
            (*which_f) = i;
        }
    }
    return (0);
}

static int change_and_return(int distance_t, int distance_f,
    int which, ginger_stats_t **stats)
{
    if (distance_t > distance_f) {
        (*stats)->type_chasing = 1;
        return (which);
    }
    (*stats)->type_chasing = 0;
    return (which);
}

static int next_node(coords_t **all_coords, int movements,
    ginger_stats_t **stats)
{
    int distance_f = INT_MAX;
    int distance_t = INT_MAX;
    int which_t = 0;
    int which_f = 0;
    int temp = 0;

    for (int i = 0; all_coords[0][i].x != -1; ++i) {
        temp = abs(all_coords[2][0].x - all_coords[0][i].x) +
            abs(all_coords[2][0].y - all_coords[0][i].y);
        if (temp < distance_t) {
            distance_t = temp;
            which_t = i;
        }
    }
    get_next_food(all_coords, movements, &which_f, &distance_f);
    if (distance_t > distance_f) {
        return (change_and_return(distance_t, distance_f, which_t, stats));
    }
    return (change_and_return(distance_t, distance_f, which_f, stats));
}

static void print_status(coords_t **all_coords,
    ginger_stats_t **stats, char **map)
{
    if (map[all_coords[2][0].x][all_coords[2][0].y] == 'T') {
        (*stats)->curr_tokens += 1;
    }
    if (map[all_coords[2][0].x][all_coords[2][0].y] == 'F') {
        (*stats)->curr_movement += (*stats)->total_movement;
    }
    map[all_coords[2][0].x][all_coords[2][0].y] = 'G';
    (*stats)->curr_movement -= 1;
    printf("Tokens: %d/%d\n", (*stats)->curr_tokens, (*stats)->total_tokens);
    printf("Movement points: %d\n", (*stats)->curr_movement);
    print_map(map);
}

static coords_t **do_op(coords_t **all_coords,
    int which, ginger_stats_t **stats)
{
    if (which == 0) {
        if (all_coords[0][(*stats)->index_chasing].x < all_coords[2][0].x)
            all_coords[2][0].x -= 1;
        else
            all_coords[2][0].x += 1;
    } else {
        if (all_coords[0][(*stats)->index_chasing].y < all_coords[2][0].y)
            all_coords[2][0].y -= 1;
        else
            all_coords[2][0].y += 1;
    }
    return (all_coords);
}

static coords_t **move_ginger(coords_t **all_coords,
    ginger_stats_t **stats, char **map)
{
    while (all_coords[0][(*stats)->index_chasing].x != all_coords[2][0].x) {
        map[all_coords[2][0].x][all_coords[2][0].y] = '.';
        if ((*stats)->curr_movement == 0)
            return (all_coords);
        all_coords = do_op(all_coords, 0, stats);
        print_status(all_coords, stats, map);
    }
    while (all_coords[0][(*stats)->index_chasing].y != all_coords[2][0].y) {
        map[all_coords[2][0].x][all_coords[2][0].y] = '.';
        if ((*stats)->curr_movement == 0)
            return (all_coords);
        all_coords = do_op(all_coords, 1, stats);
        print_status(all_coords, stats, map);
    }
    return (all_coords);
}

static ginger_stats_t *init_stats(int moves)
{
    ginger_stats_t *stats = malloc(sizeof(ginger_stats_t) * 1);

    stats->total_tokens = 0;
    stats->curr_tokens = 0;
    stats->total_movement = moves;
    stats->curr_movement = moves + 1;
    stats->index_chasing = 0;
    stats->type_chasing = 0;
    return (stats);
}

static int free_n_return(ginger_stats_t *stats)
{
    int return_value = 1;

    if (stats->curr_tokens != stats->total_tokens)
        return_value = 0;
    free(stats);
    return (return_value);
}

static coords_t **delete_found(coords_t **all_coords,
    int *last_t, int *last_f, ginger_stats_t *stats)
{
    if (stats->type_chasing == 0) {
        all_coords[0][stats->index_chasing].x = all_coords[0][*last_t].x;
        all_coords[0][stats->index_chasing].y = all_coords[0][*last_t].y;
        all_coords[0][*last_t].x = -1;
        all_coords[0][*last_t].y = -1;
        *last_t = *last_t - 1;
    } else {
        all_coords[1][stats->index_chasing].x = all_coords[1][*last_f].x;
        all_coords[1][stats->index_chasing].y = all_coords[1][*last_f].y;
        all_coords[1][*last_f].x = -1;
        all_coords[1][*last_f].y = -1;
        *last_f = *last_f - 1;
    }
    return (all_coords);
}

int pathfinding(coords_t **all_coords, int moves, char **map)
{
    int last_t = 0;
    int last_f = 0;
    ginger_stats_t *stats = init_stats(moves);

    for (int i = 0; all_coords[0][i].x != -1; ++i)
        stats->total_tokens += 1;
    for (int i = 0; all_coords[1][i].x != -1; ++i)
        last_f += 1;
    last_t = stats->total_tokens;
    print_status(all_coords, &stats, map);
    for (int i = 0; i < stats->total_tokens; ++i) {
        if (stats->curr_movement == 0)
            return (free_n_return(stats));
        stats->index_chasing = next_node(all_coords, moves, &stats);
        move_ginger(all_coords, &stats, map);
        delete_found(all_coords, &last_t, &last_f, stats);
    }
    return (free_n_return(stats));
}
