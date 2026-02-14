/*
** EPITECH PROJECT, 2025
** death
** File description:
** a file to handle making the birds disappearing
*/

#include "my.h"
#include "macros.h"

static void kill_player(sfRenderWindow *window, birds_t **bird, int *level)
{
    sfVector2u window_pos = sfRenderWindow_getSize(window);
    sfVector2f pos = sfSprite_getPosition((*bird)->sprite);
    unsigned int x = pos.x;

    if (x >= window_pos.x) {
        *level = *level * -1;
    }
}

static void kill_bird(sfRenderWindow *window, birds_t **bird)
{
    sfVector2u window_pos = sfRenderWindow_getSize(window);
    sfVector2f pos = sfSprite_getPosition((*bird)->sprite);
    unsigned int y = pos.y;

    if (y >= window_pos.y){
        sfClock_destroy((*bird)->clock);
        sfTexture_destroy((*bird)->texture);
        sfSprite_destroy((*bird)->sprite);
        sfMusic_destroy((*bird)->sound);
        free(*bird);
        (*bird) = NULL;
    }
}

birds_t **kill_bird_or_player(sfRenderWindow *window, birds_t **birds,
    int *level, int type)
{
    int num_of_birds = num_birds(*level, type);

    for (int i = 0; i < num_of_birds; ++i) {
        if (birds[i] != NULL && *level > 0) {
            kill_player(window, &birds[i], level);
            kill_bird(window, &birds[i]);
        }
    }
    birds = empty(birds, level, type, window);
    return (birds);
}

birds_t **empty(birds_t **birds, int *level, int type, sfRenderWindow *window)
{
    int num_empty = 0;
    int num_of_birds = num_birds(ABS(*level), type);

    for (int i = 0; i < num_of_birds; ++i)
        if (birds[i] == NULL)
            ++num_empty;
    if (num_empty != 0 && num_empty == num_of_birds){
        between_levels(window, (*level), type);
        *level = *level + 1;
        free(birds);
        birds = NULL;
        if (*level < MAX_LEVEL)
            birds = create_birds((*level), type);
        else
            *level = *level * -1;
    }
    return (birds);
}
