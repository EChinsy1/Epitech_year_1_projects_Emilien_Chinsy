/*
** EPITECH PROJECT, 2026
** main
** File description:
** main
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my.h"
#include "struct.h"

static int size(char **map)
{
    int i = 0;

    for (; map[i] != NULL; i++);
    return i;
}

static void free_all(coords_t **all_coords, char **array,
    unsigned char *map, int success)
{
    if (success == 0)
        printf("Ginger is too old for that!\n");
    else
        printf("Ginger never loses!");
    free(map);
    free(array);
    free_all_coords(all_coords);
}

int get_moov(char **array)
{
    for (int i = 0; array[i] != NULL; i++){
        if (array[i][0] == '-' && array[i][1] == 'm')
            return atoi(array[i + 1]);
    }
    return (0);
}

int main(int ac, char **av)
{
    coords_t **all_coords = NULL;
    unsigned char *map = NULL;
    char **array = NULL;
    int success = 0;

    if (ac != 5)
        return (84);
    map = parsing(&av[1]);
    if (map == NULL)
        return (84);
    array = get_array((char *)map, array);
    if (array == NULL)
        return (84);
    all_coords = find_all_coords(size(array), strlen(array[0]), array);
    if (all_coords == (NULL)) {
        return (84);
    }
    success = pathfinding(all_coords, get_moov(&av[1]), array);
    free_all(all_coords, array, map, success);
    return (0);
}
