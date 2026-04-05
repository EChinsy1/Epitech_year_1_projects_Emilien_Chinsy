/*
** EPITECH PROJECT, 2026
** my_world
** File description:
** painter_algo
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
#include "my_world.h"
#include "macros.h"
#include "game.h"

static sfVertexArray *create_line(sfRenderWindow *window,
    sfVector2f *point1, sfVector2f *point2)
{
    sfVertexArray *vertex_array = sfVertexArray_create();
    sfVertex vertex1 = {.position = *point1, .color = sfBlack};
    sfVertex vertex2 = {.position = *point2, .color = sfBlack};

    vertex1.position.x += 10;
    vertex1.position.y += 10;
    vertex2.position.x += 10;
    vertex2.position.y += 10;
    sfVertexArray_append(vertex_array, vertex1);
    sfVertexArray_append(vertex_array, vertex2);
    sfVertexArray_setPrimitiveType(vertex_array, sfLineStrip);
    sfRenderWindow_drawVertexArray(window, vertex_array, NULL);
    sfVertexArray_destroy(vertex_array);
    return (NULL);
}

static sfVertexArray *make_the_array(sfRenderWindow *window,
    sfVector2f *p[3], int coords[4], sfVertexArray *vertex_array)
{
    sfVertex v1 = {.position = *p[0], .color = sfWhite, .texCoords = {0, 0}};
    sfVertex v2 = {.position = *p[1], .color = sfWhite, .texCoords = {800, 0}};
    sfVertex v3 = {.position = *p[2], .color = sfWhite, .texCoords = {0, 600}};
    sfVertex v4 = {.position = *p[3], .color = sfWhite,
        .texCoords = {800, 600}};

    v1.position.x += 10;
    v1.position.y += 10;
    v2.position.x += 10;
    v2.position.y += 10;
    v3.position.x += 10;
    v3.position.y += 10;
    v4.position.x += 10;
    v4.position.y += 10;
    sfVertexArray_append(vertex_array, v1);
    sfVertexArray_append(vertex_array, v2);
    sfVertexArray_append(vertex_array, v4);
    sfVertexArray_append(vertex_array, v3);
    create_line(window, p[0], p[1]);
    return (vertex_array);
}

static int get_elev(game_t *game, int coords[4])
{
    int result = 0;

    if (game->map[coords[0]][coords[1]] < 0 || game->map[coords[2]][coords[1]]
        < 0 || game->map[coords[0]][coords[3]] < 0 ||
        game->map[coords[2]][coords[3]] < 0)
        result--;
    if (game->map[coords[0]][coords[1]] > 0 ||
        game->map[coords[2]][coords[1]]
        > 0 || game->map[coords[0]][coords[3]] > 0 ||
        game->map[coords[2]][coords[3]] > 0)
        result = result + 2;
    return result;
}

static sfVertexArray *draw_world(sfRenderWindow *window, sfVector2f *points[3],
    game_t *game, int coords[4])
{
    int result = 0;
    sfVertexArray *vertex_array = sfVertexArray_create();
    sfRenderStates states = {sfBlendAlpha,
        sfTransform_Identity, game->textures->grass, NULL};

    vertex_array = make_the_array(window, points, coords, vertex_array);
    sfVertexArray_setPrimitiveType(vertex_array, sfQuads);
    result = get_elev(game, coords);
    if (result == -1)
        states.texture = game->textures->water;
    if (result == 2)
        states.texture = game->textures->mountain;
    if (result == 1)
        states.texture = game->textures->mixed;
    sfRenderWindow_drawVertexArray(window, vertex_array, &states);
    sfVertexArray_destroy(vertex_array);
    create_line(window, points[0], points[2]);
    return (NULL);
}

static int make_and_draw_vertex(sfRenderWindow *window,
    game_t *game, int x, int y)
{
    sfVector2f *vectors[4] = {&(game->map_2d)[x][y],
        &(game->map_2d)[x + 1][y], &(game->map_2d)[x][y + 1],
        &(game->map_2d[x + 1][y + 1])};
    int points[4] = {x, y, x + 1, y + 1};

    if (x < game->size_x - 1 && y < game->size_y - 1)
        draw_world(window, vectors, game, points);
    return (0);
}

int draw_2d_map_0(sfRenderWindow *window, game_t *game,
    sfCircleShape ***circles, int **map_3d)
{
    for (int i = 0; i < game->size_x; ++i) {
        for (int j = 0; j < game->size_y; ++j) {
            make_and_draw_vertex(window, game, i, j);
            sfCircleShape_setPosition(circles[i][j],
                project_iso_point(i * 100, j * 100, map_3d[i][j] * 100, game));
            sfRenderWindow_drawCircleShape(window, circles[i][j], NULL);
        }
    }
    return (0);
}

int draw_2d_map_1(sfRenderWindow *window, game_t *game,
    sfCircleShape ***circles, int **map_3d)
{
    for (int j = game->size_y - 1; j >= 0; --j) {
        for (int i = 0; i < game->size_x; ++i) {
            make_and_draw_vertex(window, game, i, j);
            sfCircleShape_setPosition(circles[i][j],
                project_iso_point(i * 100, j * 100, map_3d[i][j] * 100, game));
            sfRenderWindow_drawCircleShape(window, circles[i][j], NULL);
        }
    }
    return (0);
}

int draw_2d_map_2(sfRenderWindow *window, game_t *game,
    sfCircleShape ***circles, int **map_3d)
{
    for (int i = game->size_x - 1; i >= 0; --i) {
        for (int j = game->size_y - 1; j >= 0; --j) {
            make_and_draw_vertex(window, game, i, j);
            sfCircleShape_setPosition(circles[i][j],
                project_iso_point(i * 100, j * 100, map_3d[i][j] * 100, game));
            sfRenderWindow_drawCircleShape(window, circles[i][j], NULL);
        }
    }
    return (0);
}

int draw_2d_map_3(sfRenderWindow *window, game_t *game,
    sfCircleShape ***circles, int **map_3d)
{
    for (int j = 0; j < game->size_y; ++j) {
        for (int i = game->size_x - 1; i >= 0; --i) {
            make_and_draw_vertex(window, game, i, j);
            sfCircleShape_setPosition(circles[i][j],
                project_iso_point(i * 100, j * 100, map_3d[i][j] * 100, game));
            sfRenderWindow_drawCircleShape(window, circles[i][j], NULL);
        }
    }
    return (0);
}
