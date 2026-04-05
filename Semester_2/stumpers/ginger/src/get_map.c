/*
** EPITECH PROJECT, 2026
** ginger
** File description:
** main
*/

#include <stdlib.h>
#include <stdio.h>
#include "test.h"
#include "struct.h"

void free_all_coords(coords_t **all_coords)
{
    free(all_coords[0]);
    free(all_coords[1]);
    free(all_coords[2]);
    free(all_coords);
}

static coords_t *find_tokens(coords_t *token_coords, int i, int j, char **map)
{
    int size = 0;

    if (map[i][j] == 'T') {
        while (token_coords[size].x != -1)
            ++size;
        token_coords = realloc(token_coords, sizeof(coords_t) * (size + 2));
        token_coords[size].x = i;
        token_coords[size].y = j;
        token_coords[size + 1].x = -1;
        token_coords[size + 1].y = -1;
    }
    return (token_coords);
}

static coords_t *find_foods(coords_t *food_coords, int i, int j, char **map)
{
    int size = 0;

    if (map[i][j] == 'F') {
        while (food_coords[size].x != -1)
            ++size;
        food_coords = realloc(food_coords, sizeof(coords_t) * (size + 2));
        food_coords[size].x = i;
        food_coords[size].y = j;
        food_coords[size + 1].x = -1;
        food_coords[size + 1].y = -1;
    }
    return (food_coords);
}

static coords_t *find_gingers(coords_t *ginger_coords, int i, int j, char **map)
{
    int size = 0;

    if (map[i][j] == 'G') {
        while (ginger_coords[size].x != -1)
            ++size;
        ginger_coords = realloc(ginger_coords, sizeof(coords_t) * (size + 2));
        ginger_coords[size].x = i;
        ginger_coords[size].y = j;
        ginger_coords[size + 1].x = -1;
        ginger_coords[size + 1].y = -1;
    }
    return (ginger_coords);
}

static coords_t **check_valid_map(coords_t **all_coords)
{
    int i = 0;
    int j = 0;

    while (all_coords[0][i].x != -1) {
        ++i;
    }
    while (all_coords[2][j].x != -1) {
        ++j;
    }
    if (i < 1 || j != 1) {
        free_all_coords(all_coords);
        return (NULL);
    }
    return (all_coords);
}

static coords_t **get_the_values(coords_t **all_coords,
    char **map, int size_x, int size_y)
{
    for (int i = 0; i < size_x; ++i) {
        for (int j = 0; j < size_y; ++j) {
            all_coords[0] = find_tokens(all_coords[0], i, j, map);
            all_coords[1] = find_foods(all_coords[1], i, j, map);
            all_coords[2] = find_gingers(all_coords[2], i, j, map);
        }
    }
    return (all_coords);
}

coords_t **find_all_coords(int size_x, int size_y, char **map)
{
    coords_t **all_coords = malloc(sizeof(coords_t *) * 4);

    if (all_coords == NULL)
        return (NULL);
    all_coords[0] = calloc(sizeof(coords_t), 1);
    all_coords[0][0].x = -1;
    all_coords[0][0].y = -1;
    all_coords[1] = calloc(sizeof(coords_t), 1);
    all_coords[1][0].x = -1;
    all_coords[1][0].y = -1;
    all_coords[2] = calloc(sizeof(coords_t), 1);
    all_coords[2][0].x = -1;
    all_coords[2][0].y = -1;
    all_coords[3] = NULL;
    all_coords = get_the_values(all_coords, map, size_x, size_y);
    return (check_valid_map(all_coords));
}
