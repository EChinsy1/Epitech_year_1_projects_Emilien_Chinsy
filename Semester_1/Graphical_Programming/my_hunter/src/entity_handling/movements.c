/*
** EPITECH PROJECT, 2025
** movements
** File description:
** function to handle the birds movements
*/

#include <string.h>
#include "my.h"
#include "struct_elements.h"
#include "struct_each_type.h"

void update_normal_bird_pos(sfTime *time, birds_t **bird, sfClock *clock)
{
    if ((*bird)->hp > 0 && (*bird)->spawned == 1) {
        if (sfTime_asMicroseconds(*time) > 100000) {
            animate_sprite((*bird)->sprite, 110, 3);
            sfClock_restart(clock);
        }
        move_sprite((*bird)->sprite, (*bird)->speed, 0.1);
    } else {
        death_handling(bird, time, clock);
    }
}

void update_evil_bird_pos(sfTime *time, birds_t **bird, sfClock *clock)
{
    sfFloatRect rect = sfSprite_getGlobalBounds((*bird)->sprite);
    float height = rect.top;

    if ((height > 900 && (*bird)->height > 0) ||
        (height < 10 && (*bird)->height < 0))
        (*bird)->height = (*bird)->height * -1;
    if ((*bird)->hp > 0 && (*bird)->spawned == 1) {
        if (sfTime_asMicroseconds(*time) > 100000) {
            animate_sprite((*bird)->sprite, 110, 3);
            sfClock_restart(clock);
        }
        move_sprite((*bird)->sprite, (*bird)->speed, (*bird)->height);
    } else {
        death_handling(bird, time, clock);
    }
}

void update_supersonic_bird_pos(sfTime *time, birds_t **bird, sfClock *clock)
{
    if ((*bird)->hp > 0 && (*bird)->spawned == 1) {
        if (sfTime_asMicroseconds(*time) > 100000) {
            animate_sprite((*bird)->sprite, 110, 3);
            sfClock_restart(clock);
        }
        move_sprite((*bird)->sprite, (*bird)->speed, 0.1);
    } else {
        death_handling(bird, time, clock);
    }
}

void update_bird_pos(sfTime *time, birds_t **bird, sfClock *clock)
{
    int i = 0;

    while (EACH_TYPE[i].mov_n_animate != NULL) {
        if (my_strcmp((*bird)->type, EACH_TYPE[i].type) == 0
            && (*bird)->spawned == 1) {
            return (EACH_TYPE[i].mov_n_animate(time, bird, clock));
        }
        ++i;
    }
}

void choose_right_draw_func(sfRenderWindow *window, birds_t **bird, int level)
{
    int j = 0;

    while (EACH_TYPE[j].draw != NULL) {
        if (my_strcmp((*bird)->type, EACH_TYPE[j].type) == 0) {
            return (EACH_TYPE[j].draw(window, bird));
        }
        ++j;
    }
}
