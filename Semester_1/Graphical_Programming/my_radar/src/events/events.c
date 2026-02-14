/*
** EPITECH PROJECT, 2025
** events
** File description:
** a file which will contain some of the event calls
*/

#include <stdlib.h>
#include "my.h"
#include "macros.h"
#include "struct.h"

int return_n_free(char *buffer, char *line, game_t *game)
{
    write(2, "Invalid format\n", 15);
    free(game);
    free(buffer);
    free(line);
    return (84);
}

int set_draw_hitboxes(sfRenderWindow *window, game_t *game)
{
    if (game->show_hitbox == INACTIVE) {
        game->show_hitbox = ACTIVE;
    } else {
        game->show_hitbox = INACTIVE;
    }
    return (SUCCESS);
}

int set_draw_sprites(sfRenderWindow *window, game_t *game)
{
    if (game->show_sprites == INACTIVE) {
        game->show_sprites = ACTIVE;
    } else {
        game->show_sprites = INACTIVE;
    }
    return (SUCCESS);
}

int analyse_events(sfRenderWindow *window, sfEvent event,
    game_t *game)
{
    while (sfRenderWindow_pollEvent(window, &event)) {
        if (event.type == sfEvtClosed || ((event.type == sfEvtKeyPressed)
                && (((sfKeyEvent *)&event)->scancode == sfScanEscape)))
            sfRenderWindow_close(window);
        if ((event.type == sfEvtKeyPressed) &&
            (((sfKeyEvent *)&event)->scancode == sfScanL)) {
            set_draw_hitboxes(window, game);
        }
        if ((event.type == sfEvtKeyPressed) &&
            (((sfKeyEvent *)&event)->scancode == sfScanS)) {
            set_draw_sprites(window, game);
        }
    }
    return (SUCCESS);
}
