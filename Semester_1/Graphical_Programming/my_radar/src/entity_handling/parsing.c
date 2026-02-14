/*
** EPITECH PROJECT, 2025
** parsing
** File description:
** parses the file and creates the planes and towers according to the info.
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "my.h"
#include "struct.h"
#include "macros.h"

static void free_word_array(char **word_array)
{
    for (int i = 0; word_array[i]; ++i)
        free(word_array[i]);
    free(word_array);
}

static int get_len_of_word_array(char **word_array)
{
    int i = 0;

    while (word_array[i] != NULL)
        ++i;
    return (i);
}

int get_num_of_planes_and_towers(int size, char *buffer,
    game_t **game)
{
    char *line = NULL;
    int start = 0;
    int planes = 0;
    int towers = 0;

    while (start < size) {
        line = get_string_line(buffer, &start);
        if (line[0] == 'A')
            ++planes;
        if (line[0] == 'T')
            ++towers;
        if (line[0] != 'A' && line[0] != 'T')
            return (return_n_free(buffer, line, (*game)));
        free(line);
    }
    (*game)->num_of_planes = planes;
    (*game)->num_of_towers = towers;
    (*game)->planes = malloc(sizeof(planes_t *) * (planes + 1));
    (*game)->towers = malloc(sizeof(towers_t *) * (towers + 1));
    return (SUCCESS);
}

static planes_t *set_move_n_offset_plane(planes_t *plane)
{
    float angle = (atan2((plane->arrival_y - plane->departure_y),
            (plane->arrival_x - plane->departure_x)));

    sfSprite_setTexture(plane->sprite, plane->texture, sfTrue);
    sfSprite_setPosition(plane->sprite,
        ((sfVector2f){plane->departure_x, plane->departure_y}));
    plane->move_x = fabs(cos(angle));
    plane->move_y = fabs(sin(angle));
    angle = angle * CONVERT_RAD_DEG;
    sfSprite_setRotation(plane->sprite, angle);
    sfRectangleShape_setRotation(plane->hitbox, angle);
    if ((plane->arrival_x - plane->departure_x) < 0)
        plane->move_x *= -1;
    if (plane->arrival_y - plane->departure_y < 0)
        plane->move_y *= -1;
    plane->offset_x = - ((SIZE_OF_PLANE / 2) * cos(angle * (M_PI / 180.0f))
        - (SIZE_OF_PLANE / 2) * sin(angle * (M_PI / 180.0f)));
    plane->offset_y = - ((SIZE_OF_PLANE / 2) * sin(angle * (M_PI / 180.0f))
        + (SIZE_OF_PLANE / 2) * cos(angle * (M_PI / 180.0f)));
    return (plane);
}

static void set_hitbox_plane(planes_t *plane)
{
    sfRectangleShape_setPosition(plane->hitbox,
        (sfVector2f){plane->pos_x, plane->pos_y});
    sfRectangleShape_setSize(plane->hitbox, (sfVector2f)
        {SIZE_OF_PLANE, SIZE_OF_PLANE});
    sfRectangleShape_setFillColor(plane->hitbox, sfTransparent);
    sfRectangleShape_setOutlineColor(plane->hitbox, sfGreen);
    sfRectangleShape_setOutlineThickness(plane->hitbox, 1);
}

static void set_circle_tower(towers_t *tow)
{
    sfCircleShape_setPosition(tow->hitsphere,
        (sfVector2f){tow->pos_x, tow->pos_y});
    sfCircleShape_setOrigin(tow->hitsphere, ((sfVector2f)
            {((tow->radius) - (SIZE_OF_TOW / 2)),
                ((tow->radius) - (SIZE_OF_TOW / 2))}));
    sfCircleShape_setRadius(tow->hitsphere, tow->radius);
    sfCircleShape_setFillColor(tow->hitsphere, sfTransparent);
    sfCircleShape_setOutlineColor(tow->hitsphere, sfRed);
    sfCircleShape_setOutlineThickness(tow->hitsphere, 5);
}

static planes_t *set_and_compute_plane(planes_t *plane)
{
    set_hitbox_plane(plane);
    plane = set_move_n_offset_plane(plane);
    plane->pos_x = (float)plane->departure_x + plane->offset_x;
    plane->pos_y = (float)plane->departure_y + plane->offset_y;
    plane->spawned = 0;
    plane->in_tower = 0;
    return (plane);
}

planes_t *plane_fs(char const *str, game_t *game)
{
    planes_t *plane = my_calloc(sizeof(planes_t), 1);
    char **word_array = my_str_to_word_array(str);
    int len = get_len_of_word_array(word_array);

    if (len != 7) {
        write(1, "Line with invalid format\n", 25);
        game->num_of_crash++;
        return (NULL);
    }
    plane->sprite = sfSprite_create();
    plane->texture = game->plane_t;
    plane->hitbox = sfRectangleShape_create();
    plane->departure_x = my_getnbr(word_array[1]);
    plane->departure_y = my_getnbr(word_array[2]);
    plane->arrival_x = my_getnbr(word_array[3]);
    plane->arrival_y = my_getnbr(word_array[4]);
    plane->speed = my_getnbr(word_array[5]);
    plane->delay = my_getnbr(word_array[6]);
    free_word_array(word_array);
    return (set_and_compute_plane(plane));
}

towers_t *tower_fs(char const *str, game_t *game)
{
    towers_t *tow = my_calloc(sizeof(towers_t), 1);
    char **word_array = my_str_to_word_array(str);
    int len = get_len_of_word_array(word_array);

    if (len != 4) {
        write(1, "Line with invalid format\n", 25);
        return (NULL);
    }
    tow->sprite = sfSprite_create();
    tow->hitsphere = sfCircleShape_create();
    tow->texture = game->tower_t;
    tow->pos_x = my_getnbr(word_array[1]);
    tow->pos_y = my_getnbr(word_array[2]);
    tow->radius = my_getnbr(word_array[3]);
    sfSprite_setTexture(tow->sprite, tow->texture, sfTrue);
    sfSprite_setPosition(tow->sprite, ((sfVector2f){tow->pos_x, tow->pos_y}));
    set_circle_tower(tow);
    free_word_array(word_array);
    return (tow);
}

void fill_arrays(char *buffer, int size,
    game_t **game)
{
    int start = 0;
    char *line = NULL;
    int planes = 0;
    int towers = 0;

    (*game)->plane_t = sfTexture_createFromFile(PLANE_SPRITE, NULL);
    (*game)->tower_t = sfTexture_createFromFile(TOWER_SPRITE, NULL);
    while (start < size) {
        line = get_string_line(buffer, &start);
        if (line[0] == 'A') {
            (*game)->planes[planes] = plane_fs(line, (*game));
            ++planes;
        }
        if (line[0] == 'T') {
            (*game)->towers[towers] = tower_fs(line, (*game));
            ++towers;
        }
        free(line);
    }
    free(buffer);
}
