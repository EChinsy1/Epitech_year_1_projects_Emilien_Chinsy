/*
** EPITECH PROJECT, 2025
** quad tree
** File description:
** help
*/

#include <stdlib.h>
#include "my.h"
#include "macros.h"
#include "struct.h"
#include "quad_tree.h"

static qt_t *create_quad_divide(float x, float y, float height, float width)
{
    qt_t *divide = my_calloc(sizeof(qt_t), 1);
    aab_t *bounds = my_calloc(sizeof(aab_t), 1);

    bounds->x = x;
    bounds->y = y;
    bounds->height = height;
    bounds->width = width;
    divide->bounds = bounds;
    divide->tl = NULL;
    divide->tr = NULL;
    divide->bl = NULL;
    divide->br = NULL;
    divide->num_items = 0;
    divide->is_leaf = 1;
    return (divide);
}

static void subdivide(qt_t *tree)
{
    int x = tree->bounds->x;
    int y = tree->bounds->y;
    int height = tree->bounds->height;
    int width = tree->bounds->width;

    tree->tl = create_quad_divide(x, y, height / 2, width / 2);
    tree->tr = create_quad_divide(x + width / 2, y, height / 2, width / 2);
    tree->bl = create_quad_divide(x, y + height / 2, height / 2, width / 2);
    tree->br = create_quad_divide(x + width / 2,
        y + height / 2, height / 2, width / 2);
}

int contains(aab_t *bounds, float pos_plane[2])
{
    float bounds_x_mid = bounds->x + bounds->width / 2;
    float bounds_y_mid = bounds->y + bounds->height / 2;
    float x = pos_plane[0];
    float y = pos_plane[1];

    if ((x + SIZE_OF_PLANE) < bounds->x || x > bounds->x + bounds->width)
        return NOT_IN;
    if ((y + SIZE_OF_PLANE) < bounds->y || y > bounds->y + bounds->height)
        return NOT_IN;
    return IN;
}

static int is_not_leaf(qt_t *parent, planes_t *plane, int index, game_t *game)
{
    float bounds_x_mid = parent->bounds->x + parent->bounds->width / 2;
    float bounds_y_mid = parent->bounds->y + parent->bounds->height / 2;
    float x = plane->pos_x;
    float y = plane->pos_y;

    if (x > bounds_x_mid) {
        if (y < bounds_y_mid)
            add_node(parent->tr, plane, index, game);
        if (y + SIZE_OF_PLANE > bounds_y_mid)
            add_node(parent->br, plane, index, game);
    } else {
        if (y < bounds_y_mid)
            add_node(parent->tl, plane, index, game);
        if (y + SIZE_OF_PLANE > bounds_y_mid)
            add_node(parent->bl, plane, index, game);
    }
    return (1);
}

static int add_node_parent_leaf(qt_t *parent,
    planes_t *plane, int index, game_t *game)
{
    if (parent->num_items < MAX_NUM_ITEMS) {
        parent->indexes_inside[parent->num_items] = index;
        parent->num_items += 1;
        return (1);
    }
    subdivide(parent);
    parent->is_leaf = 0;
    parent->num_items = 0;
    for (int i = 0; i < MAX_NUM_ITEMS; ++i) {
        add_node(parent, game->planes[parent->indexes_inside[i]],
            parent->indexes_inside[i], game);
    }
    return (add_node(parent, plane, index, game));
}

int add_node(qt_t *parent, planes_t *plane, int index, game_t *game)
{
    int in_qt = 0;

    if (!plane)
        return (0);
    in_qt = contains(parent->bounds, PLANE_POSES);
    if (in_qt == NOT_IN)
        return (0);
    if (parent->is_leaf) {
        return (add_node_parent_leaf(parent, plane, index, game));
    } else {
        return (is_not_leaf(parent, plane, index, game));
    }
}

static int collision_checker(planes_t *plane_1, planes_t *plane_2)
{
    if ((plane_2->pos_x + SIZE_OF_PLANE) <= plane_1->pos_x)
        return (NOT_IN);
    if ((plane_1->pos_x + SIZE_OF_PLANE) <= plane_2->pos_x)
        return (NOT_IN);
    if ((plane_2->pos_y + SIZE_OF_PLANE) <= plane_1->pos_y)
        return (NOT_IN);
    if ((plane_1->pos_y + SIZE_OF_PLANE) <= plane_2->pos_y)
        return (NOT_IN);
    return (IN);
}

static int if_valid_for_collision(game_t **game, qt_t *tree, int i, int j)
{
    if ((*game)->planes[tree->indexes_inside[i]] == NULL) {
        return (NOT_VALID);
    }
    if (j == tree->indexes_inside[i]) {
        return (NOT_VALID);
    }
    if ((*game)->planes[tree->indexes_inside[i]]->in_tower == 1) {
        return (NOT_VALID);
    }
    if (collision_checker((*game)->planes[j],
            (*game)->planes[tree->indexes_inside[i]]) == 0) {
        return (NOT_VALID);
    }
    return (VALID);
}

int delete_no_tree(game_t **game, float pos_plane[2], qt_t *tree, int j)
{
    for (int i = 0; i < tree->num_items; ++i)
        if (if_valid_for_collision(game, tree, i, j)) {
            sfSprite_destroy((*game)->planes
                [tree->indexes_inside[i]]
                ->sprite);
            sfRectangleShape_destroy(
                (*game)->planes[tree->indexes_inside[i]]->hitbox);
            free((*game)->planes[tree->indexes_inside[i]]);
            (*game)->planes[tree->indexes_inside[i]] = NULL;
            sfSprite_destroy((*game)->planes[j]->sprite);
            sfRectangleShape_destroy((*game)->planes[j]->hitbox);
            free((*game)->planes[j]);
            (*game)->planes[j] = NULL;
            (*game)->num_of_crash += 2;
            return (VALID);
        }
    return (NOT_VALID);
}

int which_quadrant(game_t **game, qt_t *tree,
    planes_t *plane, int j)
{
    float bounds_x_mid = tree->bounds->x + tree->bounds->width / 2;
    float bounds_y_mid = tree->bounds->y + tree->bounds->height / 2;
    float x = plane->pos_x;
    float y = plane->pos_y;

    if (x > bounds_x_mid) {
        if (y < bounds_y_mid)
            return (TR);
        if (y + SIZE_OF_PLANE > bounds_y_mid)
            return (BR);
        return (NONE);
    } else {
        if (y < bounds_y_mid)
            return (TL);
        if (y + SIZE_OF_PLANE > bounds_y_mid)
            return (BL);
        return (NONE);
    }
    return (NONE);
}
