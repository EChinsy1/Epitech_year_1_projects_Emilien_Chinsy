/*
** EPITECH PROJECT, 2026
** amazed
** File description:
** matrix
*/

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "amazed.h"
#include "my_string.h"
#include "macros.h"
#include "prints.h"

int **create_matrix(int nb_rooms)
{
    int **matrix = malloc(sizeof(int *) * (nb_rooms + 1));

    if (matrix == NULL)
        return NULL;
    for (int y = 0; y < nb_rooms; y++){
        matrix[y] = malloc(sizeof(int) * (nb_rooms + 1));
        for (int x = 0; x < nb_rooms; x++)
            matrix[y][x] = 0;
        matrix[y][nb_rooms] = -1;
    }
    matrix[nb_rooms] = NULL;
    return matrix;
}
