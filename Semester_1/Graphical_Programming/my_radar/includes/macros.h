/*
** EPITECH PROJECT, 2025
** macros_h
** File description:
** a file containing the general macros
*/

#ifndef MACROS_H_
    #define MACROS_H_

    #define ABS(x) ((x) < 0 ? -(x) : (x))

    #define SIZE_OF_PLANE 20
    #define PLANE_POSES (float[2]){plane->pos_x, plane->pos_y}
    #define ERROR 84
    #define SUCCESS 0
    #define FPS 60
    #define SIZE_OF_TOW 23
    #define CONVERT_RAD_DEG (180 / M_PI)
    #define INACTIVE 0
    #define WINDOW_X 1920.0
    #define WINDOW_Y 1080.0
    #define ACTIVE 1
    #define SCORE_SIZE 6
    #define NO_CRASHING game->num_of_crash + game->num_of_land
    #define NUM game->num_of_planes
    #define TOP_RIGHT &((sfVector2f){1660, 0})
    #define TOP_LEFT &((sfVector2f){0, 0})
    #define TOP_LEFT_LOW &((sfVector2f){0, 100})
    #define SCALE_OF_BG {1, 1}

static const char *const PLANE_SPRITE = "sprites/plane.png";
static const char *const TOWER_SPRITE = "sprites/cursor.png";
static const char *const FONT = "Ougkeh.otf";
static const char *const BG_SPRITE = "sprites/mapcrop.jpg";

#endif
