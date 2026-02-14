/*
** EPITECH PROJECT, 2025
** draw_cursor
** File description:
** a file to draw the cursor
*/

#include "my.h"

void draw_supersonic_bird(sfRenderWindow *window, birds_t **bird)
{
    sfTime time;

    if ((*bird) != NULL)
        time = sfClock_getElapsedTime((*bird)->clock);
    if ((*bird) != NULL && (*bird)->spawned == 0 &&
        (*bird)->wind_up_time <= sfTime_asMicroseconds(time)) {
        (*bird)->spawned = 1;
    }
    if ((*bird) != NULL && (*bird)->spawned == 1) {
        time = sfClock_getElapsedTime((*bird)->clock);
        update_bird_pos(&time, bird, (*bird)->clock);
    }
    sfRenderWindow_drawSprite(window, (*bird)->sprite, NULL);
}

void draw_normal_bird(sfRenderWindow *window, birds_t **bird)
{
    sfTime time;

    if ((*bird) != NULL)
        time = sfClock_getElapsedTime((*bird)->clock);
    if ((*bird) != NULL && (*bird)->spawned == 0 &&
        (*bird)->wind_up_time <= sfTime_asMicroseconds(time)) {
        (*bird)->spawned = 1;
    }
    if ((*bird) != NULL && (*bird)->spawned == 1) {
        time = sfClock_getElapsedTime((*bird)->clock);
        sfRenderWindow_drawSprite(window, (*bird)->sprite, NULL);
        update_bird_pos(&time, bird, (*bird)->clock);
    }
}

void draw_evil_bird(sfRenderWindow *window, birds_t **bird)
{
    sfTime time;

    if ((*bird) != NULL)
        time = sfClock_getElapsedTime((*bird)->clock);
    if ((*bird) != NULL && (*bird)->spawned == 0 &&
        (*bird)->wind_up_time <= sfTime_asMicroseconds(time)) {
        (*bird)->spawned = 1;
    }
    if ((*bird) != NULL && (*bird)->spawned == 1) {
        time = sfClock_getElapsedTime((*bird)->clock);
        sfRenderWindow_drawSprite(window, (*bird)->sprite, NULL);
        update_bird_pos(&time, bird, (*bird)->clock);
    }
}
