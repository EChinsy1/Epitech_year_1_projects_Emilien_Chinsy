/*
** EPITECH PROJECT, 2025
** collisions
** File description:
** collisions
*/

#include <stdlib.h>
#include "my.h"
#include "struct.h"
#include "macros.h"

void qt_free(qt_t *item)
{
    if (item == NULL)
        return;
    qt_free(item->tl);
    qt_free(item->tr);
    qt_free(item->bl);
    qt_free(item->br);
    free(item->bounds);
    free(item);
    item = NULL;
}

void init_qt(qt_t **item, float height, float width)
{
    aab_t *bounds = my_calloc(sizeof(aab_t), 1);

    bounds->x = 0.0;
    bounds->y = 0.0;
    bounds->height = height;
    bounds->width = width;
    (*item)->tl = NULL;
    (*item)->tr = NULL;
    (*item)->bl = NULL;
    (*item)->br = NULL;
    (*item)->bounds = bounds;
    (*item)->num_items = 0;
    (*item)->is_leaf = 1;
}

int check_quad_tree_collision(game_t **game, qt_t *tree,
    planes_t *plane, int j)
{
    int quadrant = 0;

    if (contains(tree->bounds, (float[2]){plane->pos_x, plane->pos_y}) == 0)
        return (0);
    quadrant = which_quadrant(game, tree, plane, j);
    if (quadrant == 0 || tree->is_leaf == 1) {
        delete_no_tree(game, (float[2]){plane->pos_x, plane->pos_y}, tree, j);
    } else {
        switch (quadrant) {
            case TL:
                return (check_quad_tree_collision(game, tree->tl, plane, j));
            case TR:
                return (check_quad_tree_collision(game, tree->tr, plane, j));
            case BL:
                return (check_quad_tree_collision(game, tree->bl, plane, j));
            case BR:
                return (check_quad_tree_collision(game, tree->br, plane, j));
        }
    }
    return (0);
}

static int intersect_circle_rectangle(towers_t *tower, planes_t *plane)
{
    float closest_x = 0;
    float closest_y = 0;
    float d_x = 0;
    float d_y = 0;

    if (tower->pos_x < plane->pos_x) {
        closest_x = plane->pos_x;
    } else if (tower->pos_x > (plane->pos_x + SIZE_OF_PLANE)) {
        closest_x = (plane->pos_x + SIZE_OF_PLANE);
    } else
        closest_x = tower->pos_x;
    if (tower->pos_y < plane->pos_y) {
        closest_y = plane->pos_y;
    } else if (tower->pos_y > (plane->pos_y + SIZE_OF_PLANE)) {
        closest_y = (plane->pos_y + SIZE_OF_PLANE);
    } else
        closest_y = tower->pos_y;
    d_x = closest_x - tower->pos_x;
    d_y = closest_y - tower->pos_y;
    return (((d_x * d_x) + (d_y * d_y)) <= (tower->radius * tower->radius));
}

void in_tower(game_t **game, planes_t **plane, int i)
{
    for (int j = 0; j < (*game)->num_of_towers; ++j) {
        if (intersect_circle_rectangle((*game)->towers[j], *plane)) {
            (*plane)->in_tower = 1;
            return;
        }
    }
    (*plane)->in_tower = 0;
    add_node((*game)->tree, (*game)->planes[i], i, (*game));
}

void check_collisions(game_t **game)
{
    (*game)->tree = my_calloc(sizeof(qt_t), 1);
    init_qt(&((*game)->tree), WINDOW_Y, WINDOW_X);
    for (int i = 0; i < (*game)->num_of_planes; ++i) {
        if ((*game)->planes[i] != NULL && (*game)->planes[i]->spawned == 1)
            in_tower(game, &((*game)->planes[i]), i);
    }
    for (int i = 0; i < (*game)->num_of_planes; ++i) {
        if ((*game)->planes[i] != NULL && (*game)->planes[i]->spawned == 1)
            check_quad_tree_collision(game, (*game)->tree,
                (*game)->planes[i], i);
    }
    qt_free((*game)->tree);
    (*game)->tree = NULL;
    free((*game)->tree);
}
