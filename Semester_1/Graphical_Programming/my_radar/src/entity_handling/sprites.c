/*
** EPITECH PROJECT, 2025
** text.c
** File description:
** file containing sprites stuff
*/

#include <stdlib.h>
#include "my.h"
#include "struct.h"
#include "macros.h"

sprite_t *create_sprite(const char *filepath, sfVector2f *scale)
{
    sprite_t *cursor = malloc(sizeof(sprite_t) * 1);
    sfSprite *cursor_sprite = sfSprite_create();
    sfTexture *cursor_texture = sfTexture_createFromFile(filepath, NULL);

    cursor->texture = cursor_texture;
    cursor->sprite = cursor_sprite;
    sfSprite_setTexture(cursor->sprite, cursor->texture, sfTrue);
    sfSprite_setScale(cursor->sprite, *scale);
    return (cursor);
}
