/*
** EPITECH PROJECT, 2026
** myworld
** File description:
** make_map
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
#include "my_world.h"
#include "game.h"

sfVector2f project_iso_point(int x, int y, int z, game_t *game)
{
    sfVector2f vector = {0};
    float angle_x = game->cam->pan_x * M_PI / 180.0;
    float angle_y = game->cam->pan_y * M_PI / 180.0;
    int center_x = (x - (WIDTH / 4) / 2);
    int center_y = (y - (WIDTH / 4) / 2);
    float rota_x = (cos(angle_x) * center_x - sin(angle_x) * center_y);
    float rota_y = (sin(angle_x) * center_x + cos(angle_x) * center_y);

    vector.x = ((rota_x - rota_y) * game->cam->zoom / 2) + game->cam->cam_x;
    vector.y = ((rota_x + rota_y) * game->cam->zoom * cos(angle_y) / 2 - z *
        game->cam->zoom * sin(angle_y)) + game->cam->cam_y;
    vector.x += WIDTH / 2;
    vector.y += HEIGHT / 2;
    return (vector);
}

int **make_3d_map(int size_x, int size_y)
{
    int **map_3d = calloc(sizeof(int *), size_x + 1);

    for (int i = 0; i < size_x; ++i) {
        map_3d[i] = calloc(sizeof(int), size_y + 1);
        map_3d[i][size_y] = -1;
        for (int j = 0; j < size_y; ++j) {
            map_3d[i][j] = 0;
        }
    }
    return (map_3d);
}

sfVector2f **create_2d_map(game_t *game, int **map_3d)
{
    sfVector2f **vector_array = calloc(sizeof(sfVector2f *), game->size_x + 1);

    vector_array[game->size_x] = NULL;
    for (int i = 0; i < game->size_x; ++i) {
        vector_array[i] = calloc(sizeof(sfVector2f), game->size_y + 1);
        vector_array[i][game->size_x].x = -1;
        vector_array[i][game->size_y].y = -1;
        for (int j = 0; j < game->size_y; ++j) {
            vector_array[i][j] =
                project_iso_point(i * 100, j * 100, map_3d[i][j] * 100, game);
        }
    }
    return (vector_array);
}

int draw_2d_map(sfRenderWindow *window, game_t *game,
    sfCircleShape ***circles)
{
    if (game->cam->pan_x >= 315 || game->cam->pan_x <= 44)
        draw_2d_map_0(window, game, circles, game->map);
    if (game->cam->pan_x >= 45 && game->cam->pan_x <= 134)
        draw_2d_map_1(window, game, circles, game->map);
    if (game->cam->pan_x >= 135 && game->cam->pan_x <= 224)
        draw_2d_map_2(window, game, circles, game->map);
    if (game->cam->pan_x >= 225 && game->cam->pan_x <= 314)
        draw_2d_map_3(window, game, circles, game->map);
    return (0);
}
