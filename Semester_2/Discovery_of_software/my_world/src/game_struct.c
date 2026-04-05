/*
** EPITECH PROJECT, 2026
** my_world
** File description:
** game_struct
*/

#include <SFML/Graphics.h>
#include <SFML/Graphics/BlendMode.h>
#include <SFML/Graphics/CircleShape.h>
#include <SFML/Graphics/Color.h>
#include <SFML/Graphics/PrimitiveType.h>
#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/RenderStates.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Transform.h>
#include <SFML/Graphics/Types.h>
#include <SFML/Graphics/VertexArray.h>
#include <SFML/Window/Export.h>
#include <SFML/Window/Types.h>
#include <SFML/System/Vector2.h>
#include <SFML/Audio.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "macros.h"
#include "game.h"

static void free_other(cam_t *cam, trans_t *trans, game_t *game)
{
    if (cam == NULL){
        free(trans);
        free(game);
    }
    if (trans == NULL){
        free(cam);
        free(game);
    }
    if (game == NULL){
        free(trans);
        free(cam);
    }
}

static textures_t *make_textures(void)
{
    textures_t *my_textures = calloc(sizeof(textures_t), 1);
    sfTexture *grass = sfTexture_createFromFile("textures/grass.png", NULL);
    sfTexture *water = sfTexture_createFromFile(
        "textures/water.png", NULL);
    sfTexture *mountain = sfTexture_createFromFile(
        "textures/cobblestone.png", NULL);
    sfTexture *mixed = sfTexture_createFromFile(
        "textures/cobble_o_water.png", NULL);

    my_textures->grass = grass;
    my_textures->water = water;
    my_textures->mountain = mountain;
    my_textures->mixed = mixed;
    return (my_textures);
}

static game_t *set_to_null(game_t *game_struct)
{
    game_struct->bg = NULL;
    game_struct->cursor = NULL;
    game_struct->map_2d = NULL;
    game_struct->circles = NULL;
    game_struct->map = NULL;
    return (game_struct);
}

game_t *create_gamestruct(void)
{
    cam_t *cam = create_cam();
    trans_t *trans = create_trans();
    game_t *game_struct = malloc(sizeof(game_t));

    if (cam == NULL || trans == NULL || game_struct == NULL)
        free_other(cam, trans, game_struct);
    game_struct->cam = cam;
    game_struct->trans = trans;
    game_struct->len_map = F_LEN_MAP;
    game_struct->textures = make_textures();
    game_struct->size_x = F_LEN_MAP;
    game_struct->size_y = F_LEN_MAP;
    game_struct->old_size_x = F_LEN_MAP;
    game_struct->old_size_y = F_LEN_MAP;
    game_struct->freed = 0;
    game_struct = set_to_null(game_struct);
    return game_struct;
}

static sfIntRect set_area(int left, int top, int width, int height)
{
    sfIntRect area;

    area.left = left;
    area.top = top;
    area.width = width;
    area.height = height;
    return area;
}

void create_cursor(game_t *game, const char *path)
{
    sfIntRect rect = set_area(0, 0, 60, 60);
    sfTexture *cursor_text = sfTexture_createFromFile(path, NULL);
    sfSprite *cursor = sfSprite_create();

    sfSprite_setTexture(cursor, cursor_text, sfTrue);
    sfSprite_setTextureRect(cursor, rect);
    game->cursor = cursor;
    game->cursor_texture = cursor_text;
}

void put_cursor(sfRenderWindow *window, game_t *game)
{
    sfVector2i vect = sfMouse_getPositionRenderWindow(window);
    sfVector2f vectf = {vect.x, vect.y};

    sfSprite_setPosition(game->cursor, vectf);
    sfRenderWindow_drawSprite(window, game->cursor, NULL);
}
