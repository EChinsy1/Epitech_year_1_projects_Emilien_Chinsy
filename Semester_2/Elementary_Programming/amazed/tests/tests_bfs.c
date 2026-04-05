/*
** EPITECH PROJECT, 2026
** amazed
** File description:
** file containing unit tests for amazed
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <stdio.h>
#include "bfs.h"

void redirect_all_std_2(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

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

Test(get_necessary_paths, basic_use_case, .init = redirect_all_std_2)
{
    int **graph = temp_make_graph();
    int **paths = get_necessary_paths(10000, (int[2]){1, 0}, 4, graph);

    if (paths[0][0] == 1 && paths[0][1] == 2 && paths[1][0] == 1 && paths[1][1] == 3)
        cr_assert(1 == 1);
    else
        cr_assert_(0 == 1);
}

Test(get_necessary_paths, null_graph, .init = redirect_all_std_2)
{
    int **graph = NULL;
    int **paths = get_necessary_paths(10000, (int[2]){1, 0}, 4, graph);

    cr_assert_(paths == NULL);
}