/*
** EPITECH PROJECT, 2025
** buttons.h
** File description:
** contains the structure for the game buttons.
** the function pointer contains the function to call when clicked on.
*/

#ifndef BUTTONS_H_
    #define BUTTONS_H_

    #include <SFML/Audio.h>
    #include <SFML/Graphics/Types.h>
    #include "game.h"
    #include "text.h"

typedef struct buttons {
    sfTexture *texture;
    sfSprite *sprite;
    sfVector2i size;
    sfVector2f scale;
    sfMusic *sound;
    sfRectangleShape *helpbox;
    text_n_font_t *help_text;
    int (*fptr)(sfRenderWindow *window, game_t *game);
    int hovered;
} buttons_t;

#endif
