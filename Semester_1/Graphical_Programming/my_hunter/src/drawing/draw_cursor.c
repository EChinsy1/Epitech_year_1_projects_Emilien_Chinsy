/*
** EPITECH PROJECT, 2025
** draw_cursor
** File description:
** a file to draw the cursor
*/

#include "my.h"
#include "macros.h"
#include "struct_elements.h"

void draw_cursor(sfRenderWindow *window, sfSprite *cursor)
{
    sfVector2i pos = sfMouse_getPositionRenderWindow(window);
    sfVector2f pos_f;

    pos_f.x = pos.x - 5 * 12;
    pos_f.y = pos.y - 5 * 12;
    sfSprite_setPosition(cursor, pos_f);
    sfRenderWindow_drawSprite(window, cursor, NULL);
}

void draw_elements_cursor(sfRenderWindow *window, element_t **sprites,
    sfSprite *cursor)
{
    for (int i = 0; i < 3; ++i) {
        if (sprites[i] != NULL) {
            sfRenderWindow_drawSprite(window, sprites[i]->sprite, NULL);
        }
    }
    draw_cursor(window, cursor);
}

void draw_birds_cursor(sfRenderWindow *window, birds_t **sprites, int level,
    sfSprite *cursor)
{
    for (int i = level - 1; i >= 0; --i) {
        if (sprites[i] != NULL)
            choose_right_draw_func(window, &(sprites[i]), level);
    }
    draw_cursor(window, cursor);
}
