/*
** EPITECH PROJECT, 2026
** bfs
** File description:
** the quickest path algorithm for now,
** it checks the x quickest paths
** where is x is the lowest between the number of robots,
** the number of paths linked to the start node
** and the number of paths linked to the end node,
** it will then calculate x paths by doing a bfs search,
** finding the quickest current path,
** storing it, and removing these connections from the graph.
** It will then return an NULL terminated int array containing these paths.
*/

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include "bfs.h"

static int update_tables(int curr_n_prev_n_rear[3],
    int *dist_n_prev[2], int *queue, int **graph)
{
    for (int i = 0; i < curr_n_prev_n_rear[1]; i++) {
        if (graph[curr_n_prev_n_rear[0]][i] == 1 &&
            dist_n_prev[0][i] == INT_MAX) {
            dist_n_prev[0][i] =
                dist_n_prev[0][curr_n_prev_n_rear[0]] + 1;
            dist_n_prev[1][i] = curr_n_prev_n_rear[0];
            queue[curr_n_prev_n_rear[2]] = i;
            ++(curr_n_prev_n_rear[2]);
        }
    }
    return (curr_n_prev_n_rear[2]);
}

static int *make_prev(int n)
{
    int *prev = my_calloc(sizeof(int), n + 1);

    for (int i = 0; i < n; ++i)
        prev[i] = -1;
    return (prev);
}

int *bfs(int n, int src, int searched, int **graph)
{
    int dist[n];
    int queue[n];
    int *prev = make_prev(n);
    int rear = src;
    int curr = 0;

    for (int i = 0; i < n; i++)
        dist[i] = INT_MAX;
    dist[src] = 0;
    queue[rear] = src;
    ++rear;
    while (src < rear) {
        curr = queue[src];
        ++src;
        rear = update_tables((int[3]){curr, n, rear},
            (int *[2]){dist, prev}, queue, graph);
        if (curr == searched)
            break;
    }
    return (prev);
}

int *get_paths(int **graph, int n, int search, int start)
{
    int stop = 0;
    int *true_result = my_calloc(sizeof(int), n + 1);
    int *prev = bfs(n, start, search, graph);

    for (int i = 0; i < n + 1; ++i)
        true_result[i] = -1;
    if (prev[search] == -1){
        free(true_result);
        free(prev);
        return (NULL);
    }
    true_result[0] = search;
    for (int i = 0; search != start; ++i) {
        true_result[i + 1] = prev[search];
        search = true_result[i + 1];
    }
    free(prev);
    return (true_result);
}
/*
int **temp_make_graph(void)
{
    int **graph = calloc(sizeof(int *), 5);

    graph[4] = NULL;
    graph[0] = calloc(sizeof(int), 4);
    graph[1] = calloc(sizeof(int), 4);
    graph[2] = calloc(sizeof(int), 4);
    graph[3] = calloc(sizeof(int), 4);
    graph[0][0] = 2;
    graph[0][1] = 3;
    graph[0][2] = -1;
    graph[0][3] = -1;
    graph[1][0] = 2;
    graph[1][1] = 3;
    graph[1][2] = -1;
    graph[1][3] = -1;
    graph[2][0] = 0;
    graph[2][1] = 1;
    graph[2][2] = 3;
    graph[2][3] = -1;
    graph[3][0] = 0;
    graph[3][1] = 2;
    graph[3][2] = 1;
    graph[3][3] = -1;
    return (graph);
}
*/
static int get_num_to_find(int **graph, int start, int end, int n)
{
    int num_start = 0;
    int num_end = 0;

    for (int i = 0; i < n; ++i) {
        if (graph[start][i] == 1)
            ++num_start;
    }
    for (int i = 0; i < n; ++i) {
        if (graph[end][i] == 1)
            ++num_end;
    }
    if (num_end < num_start)
        return (num_end);
    return (num_start);
}

static int **remove_adjacency(int **graph, int i, int j, int n)
{
    graph[i][j] = 0;
    graph[j][i] = 0;
    return (graph);
}

int **get_necessary_paths(int num_robots,
    int search_n_start[2], int n, int **graph)
{
    int num_to_find = 0;
    int **paths = NULL;

    if (graph == NULL)
        return (NULL);
    num_to_find = get_num_to_find(graph,
        search_n_start[0], search_n_start[1], n);
    if (num_robots < num_to_find)
        num_to_find = num_robots;
    paths = my_calloc(sizeof(int *), num_to_find + 1);
    paths[num_to_find] = NULL;
    for (int i = 0; i < num_to_find; ++i) {
        paths[i] = get_paths(graph, n, search_n_start[0], search_n_start[1]);
        for (int j = 0; paths[i] && paths[i][j + 1] != -1; ++j) {
            remove_adjacency(graph, paths[i][j + 1], paths[i][j], n);
        }
    }
    return (paths);
}
