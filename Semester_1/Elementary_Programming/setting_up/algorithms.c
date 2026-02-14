/*
** EPITECH PROJECT, 2025
** algorithms
** File description:
** a
*/

#include "my.h"
#include "lib/my/my.h"
#include <stdio.h>

static int find_zeroes(int x, int y, int i, char **map)
{
    for (int j = 0; j <= i; ++j){
        if (map[x + i][y + j] != '.')
            return (0);
    }
    for (int j = 0; j < i; ++j){
        if (map[x + j][y + i] != '.')
            return (0);
    }
    return (1);
}

static int square_size_x_is_possible(int x, int y, int size, char **map)
{
    for (int i = 0; i < size; ++i){
        if (find_zeroes(x, y, i, map) == 0)
            return (0);
    }
    return (1);
}

static int square_checking(char **map,
    int maxes[2],
    int curr_max_size,
    int curr_coords[2])
{
    int valid = 1;

    while (valid == 1){
        if ((curr_max_size + 1 + curr_coords[0]) > (maxes[1])){
            valid = 0;
        }
        if ((curr_max_size + 1 + curr_coords[1]) > (maxes[0]))
            valid = 0;
        if (valid != 0) {
            valid = square_size_x_is_possible(curr_coords[0],
                curr_coords[1],
                curr_max_size + 1,
                map);
        }
        curr_max_size += valid;
    }
    return (curr_max_size);
}

static void draw(char **map, int coords[2], int size)
{
    for (int i = coords[0]; i < (size + coords[0]); i++){
        for (int j = coords[1]; j < (size + coords[1]); ++j){
            map[i][j] = 'x';
        }
    }
}

static void add_values(int addon,
    int biggest_coords[2],
    int *curr_max_size,
    int curr_coords[2])
{
    if (addon > *curr_max_size){
        *(curr_max_size) = addon;
        biggest_coords[0] = curr_coords[0];
        biggest_coords[1] = curr_coords[1];
    }
}

void search_and_replace(char **map, int max_x, int max_y)
{
    int curr_max_size = 0;
    int addon = 0;
    int curr_coords[2];
    int maxes[2] = {max_x, max_y};
    int biggest_coords[2] = {0, 0};

    for (int i = 0; i < (maxes[1] - (curr_max_size)); ++i){
        for (int j = 0; j < (maxes[0] - (curr_max_size + 1)); ++j){
            addon = 0;
            curr_coords[0] = i;
            curr_coords[1] = j;
            addon = square_checking(map, maxes, curr_max_size, curr_coords);
            add_values(addon, biggest_coords, &curr_max_size, curr_coords);
        }
    }
    draw(map, biggest_coords, curr_max_size);
}
