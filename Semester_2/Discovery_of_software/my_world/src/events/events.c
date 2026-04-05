/*
** EPITECH PROJECT, 2026
** my_world
** File description:
** events
*/

#include <SFML/Graphics.h>
#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Types.h>
#include <SFML/Graphics/VertexArray.h>
#include <SFML/Window/Event.h>
#include <SFML/Window/Export.h>
#include <SFML/Window/Types.h>
#include <SFML/System/Vector2.h>
#include <SFML/Audio.h>
#include <stdio.h>
#include "game.h"
#include "macros.h"
#include "buttons.h"
#include "events.h"

static void change_terrain(sfMouseButtonEvent *event, game_t *game)
{
    int y = event->y;
    int min_y = y - game->trans->coord_y;

    if (game->trans->point[X] == -1 || game->trans->point[Y] == -1)
        return;
    game->map[game->trans->point[Y]][game->trans->point[X]] -= (min_y / 50);
    if (game->map[game->trans->point[Y]][game->trans->point[X]] > 9)
        game->map[game->trans->point[Y]][game->trans->point[X]] = 9;
    if (game->map[game->trans->point[Y]][game->trans->point[X]] < -9)
        game->map[game->trans->point[Y]][game->trans->point[X]] = -9;
    return;
}

static int is_on_point(sfCircleShape *circle, trans_t *tr)
{
    sfVector2f circ = sfCircleShape_getPosition(circle);
    int circ_x = (int)circ.x;
    int circ_y = (int)circ.y;

    if (tr->coord_x >= circ_x && tr->coord_x <= circ_x + C_SIZE * 2)
        if (tr->coord_y >= circ_y && tr->coord_y <= circ_y + C_SIZE * 2)
            return TRUE;
    return FALSE;
}

static int check_point(sfCircleShape ***circles, int y, trans_t *tr)
{
    for (int x = 0; circles[y][x] != NULL; x++){
        if (is_on_point(circles[y][x], tr) == TRUE){
            tr->point[X] = x;
            tr->point[Y] = y;
            return SUCCESS;
        }
    }
    return FAIL;
}

static void get_point(sfCircleShape ***circles, trans_t *tr)
{
    tr->point[X] = -1;
    tr->point[Y] = -1;
    if (circles == NULL)
        return;
    for (int y = 0; circles[y] != NULL; y++){
        if (check_point(circles, y, tr) == SUCCESS)
            break;
    }
    return;
}

static void store_coord(sfMouseButtonEvent *event, game_t *game)
{
    int x = event->x;
    int y = event->y;

    game->trans->coord_x = x;
    game->trans->coord_y = y;
    get_point(game->circles, game->trans);
}

static void correct_bounds(cam_t *cam)
{
    float pan_x = cam->pan_x;
    float pan_y = cam->pan_y;
    int zoom = cam->zoom;

    if (pan_x > 360.0)
        cam->pan_x = pan_x - 360.0;
    if (pan_x < 0.0)
        cam->pan_x = 360 - pan_x;
    if (pan_y > 180)
        cam->pan_y = 180;
    if (pan_y < 0)
        cam->pan_y = 0;
    if (cam->zoom < 1)
        cam->zoom = 1;
}

static void redirect_key(sfEvent *event, cam_t *cam)
{
    if (event->key.code == sfKeyUp)
        cam->cam_y -= 10;
    if (event->key.code == sfKeyDown)
        cam->cam_y += 10;
    if (event->key.code == sfKeyLeft)
        cam->cam_x -= 10;
    if (event->key.code == sfKeyRight)
        cam->cam_x += 10;
    if (event->key.code == sfKeyZ)
        cam->pan_y -= 3;
    if (event->key.code == sfKeyS)
        cam->pan_y += 3;
    if (event->key.code == sfKeyQ)
        cam->pan_x -= 3;
    if (event->key.code == sfKeyD)
        cam->pan_x += 3;
    if (event->key.code == sfKeyP)
        cam->zoom++;
    if (event->key.code == sfKeyM)
        cam->zoom--;
}

int manage_events(sfRenderWindow *window, sfEvent *event,
    game_t *game, buttons_t **buttons)
{
    while (sfRenderWindow_pollEvent(window, event)){
        if (event->type == sfEvtClosed){
            sfRenderWindow_close(window);
            return TRUE;
        }
        if (event->type == sfEvtMouseButtonPressed)
            store_coord(&event->mouseButton, game);
        if (event->type == sfEvtMouseButtonReleased)
            change_terrain(&event->mouseButton, game);
        if (event->type == sfEvtKeyPressed){
            redirect_key(event, game->cam);
            correct_bounds(game->cam);
        }
        execute_hover(window, game, buttons, &event->mouseButton);
        if (event->type == sfEvtMouseButtonPressed)
            execute_click(window, &event->mouseButton, game, buttons);
    }
    return FALSE;
}
