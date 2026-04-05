/*
** EPITECH PROJECT, 2025
** text.c
** File description:
** file containing text stuff
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include "text.h"

text_n_font_t *create_text(char *message, char const *font, sfVector2f *pos)
{
    text_n_font_t *my_text = malloc(sizeof(text_n_font_t) * 1);
    sfText *text = sfText_create();
    sfFont *font_element = sfFont_createFromFile(font);

    my_text->text_value = message;
    my_text->text = text;
    my_text->font = font_element;
    sfText_setString(my_text->text, my_text->text_value);
    sfText_setCharacterSize(my_text->text, 35);
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
