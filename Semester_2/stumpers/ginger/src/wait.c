/*
** EPITECH PROJECT, 2026
** main
** File description:
** main
*/

#include <stdio.h>
#include "my.h"
#include "struct.h"

int main(void)
{
    coords_t **all_coords = find_all_coords(4, 5);
    int i = 0;

    if (all_coords == ((void *)0)) {
        return (84);
    }
    printf("all_good\n");
    pathfinding(all_coords, 10);
    free_all_coords(all_coords);
    return (0);
}
