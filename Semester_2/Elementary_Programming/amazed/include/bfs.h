/*
** EPITECH PROJECT, 2026
** bfs
** File description:
** header file for the bfs
*/

#ifndef BFS_H_
    #define BFS_H_

    #include <sys/types.h>
int **get_necessary_paths(int num_robots,
    int search_n_start[2], int n, int **graph);
void *my_calloc(size_t length, size_t size);

#endif
