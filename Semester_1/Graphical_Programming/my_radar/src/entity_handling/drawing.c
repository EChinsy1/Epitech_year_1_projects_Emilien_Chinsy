/*
** EPITECH PROJECT, 2025
** drawing
** File description:
** drawing
*/

#include <stdlib.h>
#include "my.h"
#include "struct.h"
#include "macros.h"

static void check_arrival(game_t *game, int i)
{
    if ((game->planes[i]->pos_x <=
            game->planes[i]->arrival_x + game->planes[i]->speed) &&
        (game->planes[i]->pos_x >=
            game->planes[i]->arrival_x - game->planes[i]->speed) &&
        (game->planes[i]->pos_y <=
            game->planes[i]->arrival_y + game->planes[i]->speed) &&
        (game->planes[i]->pos_y >=
            game->planes[i]->arrival_y - game->planes[i]->speed)) {
        sfSprite_destroy(game->planes[i]->sprite);
        sfRectangleShape_destroy(game->planes[i]->hitbox);
        free(game->planes[i]);
        game->num_of_land += 1;
        game->planes[i] = NULL;
    }
}

static void move_sprites(sfRenderWindow *windo, game_t *game, int i)
{
    if (game->show_sprites)
        sfRenderWindow_drawSprite(windo, game->planes[i]->sprite, NULL);
    game->planes[i]->pos_x +=
        game->planes[i]->move_x * (game->planes[i]->speed / FPS);
    game->planes[i]->pos_y +=
        game->planes[i]->move_y * (game->planes[i]->speed / FPS);
    sfSprite_setPosition(game->planes[i]->sprite,
        (sfVector2f){game->planes[i]->pos_x + game->planes[i]->offset_x,
            game->planes[i]->pos_y + game->planes[i]->offset_y});
}

void check_if_draw(sfRenderWindow *window, game_t *game, int i, float time)
{
    if (!game->planes[i])
        return;
    if (game->planes[i]->spawned == INACTIVE) {
        if (time > game->planes[i]->delay)
            game->planes[i]->spawned = ACTIVE;
    } else {
        move_sprites(window, game, i);
        check_arrival(game, i);
    }
}

void check_if_draw_and_hitbox(sfRenderWindow *window,
    game_t *game, int i, float time)
{
    if (!game->planes[i]) {
        return;
    }
    if (game->planes[i]->spawned == INACTIVE) {
        if (time > game->planes[i]->delay)
            game->planes[i]->spawned = ACTIVE;
    } else {
        move_sprites(window, game, i);
        sfRectangleShape_setPosition(game->planes[i]->hitbox,
            (sfVector2f){game->planes[i]->pos_x + game->planes[i]->offset_x,
                game->planes[i]->pos_y + game->planes[i]->offset_y});
        sfRenderWindow_drawRectangleShape(window,
            game->planes[i]->hitbox, NULL);
        check_arrival(game, i);
    }
}

void check_if_draw_tow_sphere(sfRenderWindow *window, game_t *game)
{
    if (game->show_sprites) {
        for (int j = 0; j < game->num_of_towers; ++j) {
            sfRenderWindow_drawCircleShape(window, game->towers[j]->hitsphere,
                NULL);
            sfRenderWindow_drawSprite(window, game->towers[j]->sprite, NULL);
        }
    } else {
        for (int j = 0; j < game->num_of_towers; ++j) {
            sfRenderWindow_drawCircleShape(window, game->towers[j]->hitsphere,
                NULL);
        }
    }
}

void draw_sprites(sfRenderWindow *window, game_t *game, float time)
{
    if (game->show_hitbox) {
        for (int i = 0; i < game->num_of_planes; ++i)
            check_if_draw_and_hitbox(window, game, i, time);
        for (int j = 0; j < game->num_of_towers; ++j) {
            check_if_draw_tow_sphere(window, game);
        }
    } else {
        for (int i = 0; i < game->num_of_planes; ++i) {
            check_if_draw(window, game, i, time);
        }
        if (game->show_sprites == 0)
            return;
        for (int j = 0; j < game->num_of_towers; ++j)
            sfRenderWindow_drawSprite(window, game->towers[j]->sprite, NULL);
    }
}
