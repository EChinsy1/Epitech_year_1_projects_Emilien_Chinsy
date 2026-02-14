/*
** EPITECH PROJECT, 2025
** events
** File description:
** a file which will contain some of the event calls
*/

#include <stdlib.h>
#include "my.h"
#include "macros.h"

static void move_to_death(birds_t *birds)
{
    sfIntRect rect = sfSprite_getTextureRect(birds->sprite);

    if (birds->hp > 0){
        birds->hp = birds->hp - 1;
        if (birds->hp == 0){
            rect.left = 330;
            sfSprite_setTextureRect(birds->sprite, rect);
        }
    }
}

static void close_window_birds(sfRenderWindow *window,
    birds_t **birds,
    int level)
{
    sfRenderWindow_close(window);
}

static int mouse_click(sfRenderWindow *window,
    sfMouseButtonEvent *event,
    birds_t **birds,
    int i)
{
    sfVector2f pos = sfSprite_getPosition(birds[i]->sprite);
    int x = pos.x;
    int y = pos.y;
    int size_x = birds[i]->size.x;
    int size_y = birds[i]->size.y;
    int scale_x = birds[i]->scale.x;
    int scale_y = birds[i]->scale.y;

    if (birds[i]->hp <= 0)
        return (0);
    if (event->x >= x && event->x <= (x + (size_x * scale_x))){
        if (event->y >= y && event->y <= (y + (size_y * scale_y))){
            sfMusic_play(birds[i]->sound);
            move_to_death(birds[i]);
            return (1);
        }
    }
    return (0);
}

static int execute_click(sfRenderWindow *window,
    sfEvent event,
    birds_t **birds,
    int level)
{
    for (int i = 0; i < level; ++i){
        if (birds[i] != NULL &&
            mouse_click(window, &event.mouseButton, birds, i) == 1){
            return (1);
        }
    }
    return (0);
}

int analyse_events_b(sfRenderWindow *window,
    sfEvent event,
    birds_t **birds,
    int level)
{
    int level_abs = ABS(level);
    int return_value = 0;

    while (sfRenderWindow_pollEvent(window, &event) && return_value == 0) {
        if (event.type == sfEvtClosed || ((event.type == sfEvtKeyPressed)
                && (((sfKeyEvent *)&event)->scancode == sfScanEscape)))
            close_window_birds(window, birds, level_abs);
        if (event.type == sfEvtMouseButtonPressed)
            return_value = execute_click(window, event, birds, level_abs);
    }
    sfRenderWindow_display(window);
    return (return_value);
}
