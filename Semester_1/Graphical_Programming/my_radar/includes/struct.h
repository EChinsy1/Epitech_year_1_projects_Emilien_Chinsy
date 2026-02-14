/*
** EPITECH PROJECT, 2025
** struct.h
** File description:
** struct
*/

#ifndef STRUCT_H_
    #define STRUCT_H_

    #include "quad_tree.h"

typedef struct planes {
    sfTexture *texture;
    sfSprite *sprite;
    sfRectangleShape *hitbox;
    float departure_x;
    float departure_y;
    float arrival_x;
    float arrival_y;
    float speed;
    float move_x;
    float move_y;
    float offset_x;
    float offset_y;
    float pos_x;
    float pos_y;
    int delay;
    int in_tower;
    int spawned;
} planes_t;

typedef struct towers {
    sfTexture *texture;
    sfSprite *sprite;
    sfCircleShape *hitsphere;
    int pos_x;
    int pos_y;
    int radius;
} towers_t;

typedef struct sprite_n_texture {
    sfTexture *texture;
    sfSprite *sprite;
} sprite_t;

typedef struct text_n_font {
    char *text_value;
    sfText *text;
    sfFont *font;
} text_n_font_t;

typedef struct game {
    struct towers **towers;
    struct planes **planes;
    int num_of_towers;
    int num_of_planes;
    int num_of_crash;
    int num_of_land;
    int show_hitbox;
    int show_sprites;
    sfClock *game_clock;
    struct quad_tree *tree;
    sfTexture *plane_t;
    sfTexture *tower_t;
} game_t;

#endif
