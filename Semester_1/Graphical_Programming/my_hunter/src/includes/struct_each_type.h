/*
** EPITECH PROJECT, 2025
** struct.h
** File description:
** contains the structure for the game elements.
** the function pointer contains the function to call when clicked on.
*/

#ifndef STRUCT_EACH_TYPE_H_
    #define STRUCT_EACH_TYPE_H_

    #include "my.h"
    #include "struct_elements.h"
    #include "macros.h"

typedef struct different_functions{
    char const *type;
    int base_speed;
    int wind_up;
    int hp;
    void (*mov_n_animate)(sfTime *time, birds_t **bird, sfClock *clock);
    void (*draw)(sfRenderWindow *window, birds_t **bird);
    float vertical_speed;
    char *sprite;
} diff_funcs_t;

static const struct different_functions EACH_TYPE[] = {
    {"normal", NORMAL_SPEED, WIND_UP_NORMAL, NORMAL_HP,
        &update_normal_bird_pos, &draw_normal_bird, 0.1,
        "sprites/bird_spritesheet.png"},
    {"evil", NORMAL_SPEED, WIND_UP_NORMAL, EVIL_HP, &update_evil_bird_pos,
        &draw_evil_bird, 10, "sprites/evil_bird_spritesheet.png"},
    {"supersonic", SUPERSONIC_SPEED, WIND_UP_SUPERSONIC, SUPERSONIC_HP,
        &update_supersonic_bird_pos, &draw_supersonic_bird, 0.1,
        "sprites/fast_bird_spritesheet.png"},
    {"nothing", 0, 0, 0, NULL, NULL, 0, "nothing"}};

#endif
