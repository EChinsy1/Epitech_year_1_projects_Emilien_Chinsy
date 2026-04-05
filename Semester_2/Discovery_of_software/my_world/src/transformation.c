/*
** EPITECH PROJECT, 2026
** my_world
** File description:
** transformation
*/

#include <stdlib.h>
#include <unistd.h>
#include "transformation.h"

trans_t *create_trans(void)
{
    trans_t *trans = malloc(sizeof(trans_t));

    if (trans == NULL)
        return NULL;
    trans->point = calloc(2, sizeof(int));
    trans->coord_x = -1;
    trans->coord_y = -1;
    return trans;
}
