/*
** EPITECH PROJECT, 2025
** struct.h
** File description:
** contains the structure for the game elements.
** the function pointer contains the function to call when clicked on.
*/

#ifndef STRUCT_H_
    #define STRUCT_H_

typedef struct element{
    sfTexture *texture;
    sfSprite *sprite;
    sfVector2i size;
    sfVector2f scale;
    sfMusic *sound;
    int type;
    int (*fptr)(sfRenderWindow *window, sfSprite *cursor, int type);
} element_t;

typedef struct birds{
    sfTexture *texture;
    sfSprite *sprite;
    sfVector2i size;
    sfVector2f scale;
    sfMusic *sound;
    sfClock *clock;
    int hp;
    int64_t wind_up_time;
    int spawned;
    int speed;
    int height;
    char *type;
} birds_t;

typedef struct sprite_n_texture{
    sfTexture *texture;
    sfSprite *sprite;
} sprite_t;

typedef struct text_n_font{
    char *text_value;
    sfText *text;
    sfFont *font;
} text_n_font_t;

#endif
