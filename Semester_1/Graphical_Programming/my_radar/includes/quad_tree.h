/*
** EPITECH PROJECT, 2025
** quad_tree_h
** File description:
** a file containing the typedefs and defines for my quadtree
*/

#ifndef QUAD_TREE_H_
    #define QUAD_TREE_H_

    #define MAX_TREE_SIZE 100
    #define MAX_NUM_ITEMS 10
    #define NOT_IN 0
    #define NOT_VALID 0
    #define VALID 1
    #define IN 1
    #define SIZE_OF_QT 4

enum PART_OF_TREE {
    NONE,
    TL,
    TR,
    BL,
    BR
};

typedef struct axis_align_box {
    float x;
    float y;
    float width;
    float height;
} aab_t;

typedef struct quad_tree {
    struct axis_align_box *bounds;
    int indexes_inside[10];
    int is_leaf;
    int num_items;
    struct quad_tree *tl;
    struct quad_tree *tr;
    struct quad_tree *bl;
    struct quad_tree *br;
} qt_t;

#endif
