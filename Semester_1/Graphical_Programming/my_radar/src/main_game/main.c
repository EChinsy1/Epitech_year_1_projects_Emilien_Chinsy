/*
** EPITECH PROJECT, 2025
** main
** File description:
** main
*/

#include <stdlib.h>
#include "my.h"
#include "struct.h"
#include "macros.h"

static void free_planes(planes_t **planes, int num_of_planes)
{
    if (planes == NULL)
        return;
    for (int i = 0; i < num_of_planes; ++i) {
        if (planes[i]) {
            sfSprite_destroy(planes[i]->sprite);
            sfRectangleShape_destroy(planes[i]->hitbox);
            free(planes[i]);
        }
    }
    free(planes);
}

static void free_towers(towers_t **towers, int num_of_towers)
{
    int i = 0;

    if (towers == NULL)
        return;
    for (int i = 0; i < num_of_towers; ++i) {
        sfSprite_destroy(towers[i]->sprite);
        sfCircleShape_destroy(towers[i]->hitsphere);
        free(towers[i]);
    }
    free(towers);
}

static void free_extras(text_n_font_t *timer, text_n_font_t *crash,
    text_n_font_t *land, sprite_t *bg)
{
    sfText_destroy(timer->text);
    sfFont_destroy(timer->font);
    free(timer);
    sfText_destroy(crash->text);
    sfFont_destroy(crash->font);
    free(crash);
    sfText_destroy(land->text);
    sfFont_destroy(land->font);
    free(land);
    sfSprite_destroy(bg->sprite);
    sfTexture_destroy(bg->texture);
    free(bg);
}

void check_and_display(game_t *game, sfRenderWindow *window, sfEvent event)
{
    check_collisions(&game);
    analyse_events(window, event, game);
    sfRenderWindow_display(window);
}

static void radar(sfRenderWindow *window, game_t *game)
{
    sfEvent event;
    text_n_font_t *timer = create_text("O", FONT, TOP_RIGHT);
    text_n_font_t *crash = create_text("O", FONT, TOP_LEFT_LOW);
    text_n_font_t *land = create_text("O", FONT, TOP_LEFT);
    sprite_t *bg = create_sprite(BG_SPRITE, &((sfVector2f)SCALE_OF_BG));
    float time = 0;

    game->game_clock = sfClock_create();
    while (sfRenderWindow_isOpen(window) && NO_CRASHING < NUM) {
        sfRenderWindow_clear(window, sfWhite);
        sfRenderWindow_drawSprite(window, bg->sprite, NULL);
        time = sfTime_asSeconds(sfClock_getElapsedTime(game->game_clock));
        draw_sprites(window, game, time);
        combine_text(timer, time, window, "timer: ");
        combine_text(crash, game->num_of_crash, window, "planes crashed: ");
        combine_text(land, game->num_of_land, window, "planes landed: ");
        check_and_display(game, window, event);
    }
    free_extras(timer, crash, land, bg);
    sfClock_destroy(game->game_clock);
}

static int free_game(game_t *game,
    sfRenderWindow *window, int return_value)
{
    free_planes(game->planes, game->num_of_planes);
    free_towers(game->towers, game->num_of_towers);
    sfTexture_destroy(game->plane_t);
    sfTexture_destroy(game->tower_t);
    sfRenderWindow_destroy(window);
    free(game);
    return (return_value);
}

static void set_game(game_t **game)
{
    (*game)->tree = NULL;
    (*game)->num_of_crash = 0;
    (*game)->num_of_land = 0;
    (*game)->show_hitbox = 0;
    (*game)->show_sprites = 1;
    (*game)->planes[(*game)->num_of_planes] = NULL;
    (*game)->towers[(*game)->num_of_towers] = NULL;
}

int my_radar(int argc, char **argv)
{
    int size = 0;
    char *buffer = read_full_file(argv[1], &size);
    game_t *game = NULL;
    sfVideoMode mode = {WINDOW_X, WINDOW_Y, 32};
    sfRenderWindow *window;

    if (buffer == NULL || buffer[0] == '\0')
        return (ERROR);
    game = malloc(sizeof(game_t) * 1);
    if (get_num_of_planes_and_towers(size, buffer, &game))
        return (ERROR);
    set_game(&game);
    fill_arrays(buffer, size, &game);
    window = sfRenderWindow_create(mode, "radar", sfClose | sfResize, NULL);
    sfRenderWindow_setFramerateLimit(window, 60);
    if (!window) {
        free_game(game, window, ERROR);
    } else
        radar(window, game);
    return (free_game(game, window, SUCCESS));
}

static int show_help(void)
{
    write(1, "Air traffic simulation panel\n", 29);
    write(1, "USAGE\n", 6);
    write(1, "  ./my_radar [OPTIONS] path_to_script\n", 38);
    write(1, "    path_to_script The path to the script file.\n", 48);
    write(1, "OPTIONS\n", 8);
    write(1, "  -h\t\tprint the usage and quit.\n", 33);
    write(1, "USER INTERACTIONS\n", 18);
    write(1, "'L' key\t\tenable/disable hitboxes and areas.\n", 44);
    write(1, "'S' key\t\tenable/disable sprites.\n", 33);
    return (SUCCESS);
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        write(1, "invalid arguments\n", 18);
        write(1, "either type: ./my_radar filepath, or ", 37);
        write(1, "./my_radar -h for the instructions.", 35);
        return (ERROR);
    }
    if (my_strcmp(argv[1], "-h") == 0)
        return (show_help());
    return (my_radar(argc, argv));
}
