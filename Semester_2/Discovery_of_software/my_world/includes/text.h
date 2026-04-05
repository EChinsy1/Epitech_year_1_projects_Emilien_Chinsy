/*
** EPITECH PROJECT, 2025
** text.h
** File description:
** contains the structure for the text element
*/


#ifndef TEXT_H_
    #define TEXT_H_

    #include <SFML/Graphics/Types.h>
    
typedef struct text_n_font {
    char *text_value;
    sfText *text;
    sfFont *font;
} text_n_font_t;

#endif