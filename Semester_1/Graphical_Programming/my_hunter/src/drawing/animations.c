/*
** EPITECH PROJECT, 2025
** sprites
** File description:
** a file that handles sprites
*/

#include "my.h"

void move_rect(sfIntRect *rect, int offset, int max_value)
{
    rect->left = (rect->left + offset);
    if (rect->left >= max_value)
        rect->left = 0;
}

void move_sprite(sfSprite *sprite, float up, float left)
{
    sfVector2f offset;

    offset.x = up;
    offset.y = left;
    sfSprite_move(sprite, offset);
}

void animate_sprite(sfSprite *sprite, int offset, int frame_count)
{
    sfIntRect area = sfSprite_getTextureRect(sprite);

    move_rect(&area, offset, offset * frame_count);
    sfSprite_setTextureRect(sprite, area);
}

void death_handling(birds_t **bird, sfTime *time, sfClock *clock)
{
    sfIntRect area = sfSprite_getTextureRect((*bird)->sprite);

    if ((*bird)->hp < 0 && sfTime_asMicroseconds(*time) > 10000){
        (*bird)->hp = (*bird)->hp - 1;
        move_sprite((*bird)->sprite, 0.0, 10.0);
        if ((*bird)->hp < -10 && area.left == 550){
            (*bird)->hp = -1;
            area.left = 440;
        }
        if ((*bird)->hp < -10 && area.left == 440){
            (*bird)->hp = -1;
            area.left = 550;
        }
        sfSprite_setTextureRect((*bird)->sprite, area);
        sfClock_restart(clock);
    } else if ((*bird)->hp == 0 && sfTime_asMicroseconds(*time) > 400000) {
        (*bird)->hp = (*bird)->hp - 1;
        animate_sprite((*bird)->sprite, 110, 6);
        sfClock_restart(clock);
    }
}
