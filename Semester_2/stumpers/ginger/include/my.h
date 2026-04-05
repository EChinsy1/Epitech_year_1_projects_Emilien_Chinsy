/*
** EPITECH PROJECT, 2026
** my.h
** File description:
** my.h
*/

#ifndef MY_H_
    #define MY_H_

    #include "struct.h"
coords_t **find_all_coords(int size_x, int size_y, char **map);
unsigned char *parsing(char **array);
char **get_array(char *str, char **map);
int pathfinding(coords_t **all_coords, int moves, char **map);
void free_all_coords(coords_t **all_coords);
void print_map(char **map);

#endif
