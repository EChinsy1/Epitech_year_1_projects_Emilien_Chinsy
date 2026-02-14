/*
** EPITECH PROJECT, 2025
** text.c
** File description:
** file containing text stuff
*/

#include "my.h"
#include "struct.h"
#include "macros.h"
#include <stdlib.h>

text_n_font_t *create_text(char *message, char const *font, sfVector2f *pos)
{
    text_n_font_t *my_text = malloc(sizeof(text_n_font_t) * 1);
    sfText *text = sfText_create();
    sfFont *font_element = sfFont_createFromFile(font);

    my_text->text_value = message;
    my_text->text = text;
    my_text->font = font_element;
    sfText_setString(my_text->text, my_text->text_value);
    sfText_setCharacterSize(my_text->text, 100);
    sfText_setPosition(my_text->text, *pos);
    sfText_setFont(my_text->text, my_text->font);
    sfText_setColor(my_text->text, sfBlack);
    return (my_text);
}

void free_text(text_n_font_t *my_text)
{
    sfText_destroy(my_text->text);
    sfFont_destroy(my_text->font);
    free(my_text);
}

void combine_text(text_n_font_t *my_text, float timer,
    sfRenderWindow *window, char *normal_text)
{
    char *timer_text = my_add_nbr(timer);
    char *final_text = my_calloc(sizeof(char),
        my_strlen(normal_text) + SCORE_SIZE);

    my_strcpy(final_text, normal_text);
    my_strcat(final_text, timer_text);
    sfText_setString(my_text->text, final_text);
    sfText_setCharacterSize(my_text->text, 50);
    sfText_setFont(my_text->text, my_text->font);
    sfRenderWindow_drawText(window, my_text->text, NULL);
    free(final_text);
    free(timer_text);
}
