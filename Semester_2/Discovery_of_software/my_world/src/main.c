/*
** EPITECH PROJECT, 2026
** myworld
** File description:
** myworld
*/

#include <SFML/Audio/Music.h>
#include <SFML/Graphics.h>
#include <SFML/Graphics/BlendMode.h>
#include <SFML/Graphics/CircleShape.h>
#include <SFML/Graphics/Color.h>
#include <SFML/Graphics/Font.h>
#include <SFML/Graphics/PrimitiveType.h>
#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Texture.h>
#include <SFML/Graphics/Types.h>
#include <SFML/Graphics/VertexArray.h>
#include <SFML/Window/Export.h>
#include <SFML/Window/Types.h>
#include <SFML/System/Vector2.h>
#include <SFML/Audio.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include "events.h"
#include "game.h"
#include "macros.h"
#include "my_world.h"
#include "buttons.h"

sfCircleShape ***draw_circles(sfVector2f **map, game_t *game,
    int **map_3d)
{
    sfCircleShape ***circle_array = calloc(sizeof(sfCircleShape **),
        game->size_x + 1);

    circle_array[game->size_x] = NULL;
    for (int i = 0; i < game->size_x; ++i) {
        circle_array[i] = calloc(sizeof(sfCircleShape *), game->size_y + 1);
        circle_array[i][game->size_y] = NULL;
        for (int j = 0; j < game->size_y; ++j) {
            circle_array[i][j] = sfCircleShape_create();
            sfCircleShape_setFillColor(circle_array[i][j], sfRed);
            sfCircleShape_setRadius(circle_array[i][j], C_SIZE);
            sfCircleShape_setPosition(circle_array[i][j],
                project_iso_point(i * 50, j * 50, map_3d[i][j] * 50, game));
        }
    }
    return (circle_array);
}

void free_after_loop(sfVector2f **map, game_t *game)
{
    if (game->freed == 1) {
        game->freed = 0;
        return;
    }
    for (int i = 0; i < game->old_size_x; ++i) {
        free(map[i]);
        for (int j = 0; j < game->old_size_y; ++j)
            sfCircleShape_destroy(game->circles[i][j]);
        free(game->circles[i]);
    }
    free(game->circles);
    game->circles = NULL;
    free(map);
    game->old_size_x = game->size_x;
    game->old_size_y = game->size_y;
}

static void free_after_world(game_t *game)
{
    for (int i = 0; i < game->size_x; ++i)
        free(game->map[i]);
    free(game->cam);
    free(game->map);
    sfSprite_destroy(game->bg);
    sfTexture_destroy(game->textures->grass);
    sfTexture_destroy(game->textures->water);
    sfTexture_destroy(game->textures->mountain);
    sfTexture_destroy(game->textures->mixed);
    sfTexture_destroy(game->cursor_texture);
    sfTexture_destroy(game->bg_texture);
    sfSprite_destroy(game->cursor);
    free(game->textures);
    free(game->trans->point);
    free(game->trans);
    free(game);
}

static void free_buttons(buttons_t **buttons)
{
    int i = 0;

    while (buttons[i]) {
        sfMusic_destroy(buttons[i]->sound);
        sfSprite_destroy(buttons[i]->sprite);
        sfTexture_destroy(buttons[i]->texture);
        sfText_destroy(buttons[i]->help_text->text);
        sfFont_destroy(buttons[i]->help_text->font);
        free(buttons[i]->help_text);
        sfRectangleShape_destroy(buttons[i]->helpbox);
        free(buttons[i]);
        ++i;
    }
    free(buttons);
}

static void create_bg(game_t *game, char const *path)
{
    sfVector2f vect = {1, 1};
    sfSprite *sprite = sfSprite_create();
    sfTexture *texture = sfTexture_createFromFile(path, NULL);

    sfSprite_setScale(sprite, vect);
    sfSprite_setTexture(sprite, texture, sfTrue);
    game->bg = sprite;
    game->bg_texture = texture;
}

static void render(sfRenderWindow *window, game_t *game, buttons_t **buttons)
{
    sfRenderWindow_drawSprite(window, game->bg, NULL);
    game->circles = draw_circles(game->map_2d, game, game->map);
    draw_2d_map(window, game, game->circles);
    draw_buttons(window, buttons);
    put_cursor(window, game);
}

static void main_menu(sfRenderWindow *window)
{
    sfEvent event;
    game_t *game = create_gamestruct();
    buttons_t **buttons = make_main_menu_btns();

    create_bg(game, BG_PATH);
    create_cursor(game, CURSOR_SPRITE);
    game->map = make_3d_map(game->size_x, game->size_y);
    while (sfRenderWindow_isOpen(window)) {
        sfRenderWindow_clear(window, sfBlack);
        game->map_2d = create_2d_map(game, game->map);
        render(window, game, buttons);
        if (manage_events(window, &event, game, buttons))
            sfRenderWindow_close(window);
        free_after_loop(game->map_2d, game);
        sfRenderWindow_display(window);
    }
    free_buttons(buttons);
    free_after_world(game);
}

int game(void)
{
    sfVideoMode mode = {WIDTH, HEIGHT, 32};
    sfRenderWindow *window;
    sfEvent event = {0};

    srand(time(NULL));
    sfListener_setGlobalVolume(100);
    window = sfRenderWindow_create(mode, "my_world", sfClose | sfResize, NULL);
    if (!window)
        return (84);
    sfRenderWindow_setFramerateLimit(window, 60);
    sfRenderWindow_setMouseCursorVisible(window, sfFalse);
    main_menu(window);
    sfRenderWindow_destroy(window);
    return (0);
}

int main(void)
{
    game();
}
