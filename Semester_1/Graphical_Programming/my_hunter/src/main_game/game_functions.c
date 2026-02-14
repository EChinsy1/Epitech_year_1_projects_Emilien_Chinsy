/*
** EPITECH PROJECT, 2025
** endless
** File description:
** file for the endless part of the game
*/

#include "my.h"
#include "macros.h"

void show_score(text_n_font_t *my_text, int score, sfRenderWindow *window)
{
    char *score_text = my_add_nbr(score);
    char *final_text = my_calloc(sizeof(char), 4 + 7);

    my_strcpy(final_text, "score: ");
    my_strcat(final_text, score_text);
    sfText_setString(my_text->text, final_text);
    sfText_setCharacterSize(my_text->text, 100);
    sfText_setFont(my_text->text, my_text->font);
    sfRenderWindow_drawText(window, my_text->text, NULL);
    free(final_text);
    free(score_text);
}

void free_after_game(text_n_font_t *my_text, sprite_t *background)
{
    free_text(my_text);
    free_sprite(background);
}

void draw_extras(text_n_font_t *my_text, sprite_t *bg, int score,
    sfRenderWindow *window)
{
    sfRenderWindow_drawSprite(window, bg->sprite, NULL);
    show_score(my_text, score, window);
}
