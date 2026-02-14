/*
** EPITECH PROJECT, 2025
** my.h
** File description:
** header file
*/

#ifndef MY_H_
    #define MY_H_

    #include <SFML/Graphics.h>
    #include <SFML/Window/Export.h>
    #include <SFML/Window/Types.h>
    #include <SFML/System/Vector2.h>
    #include <SFML/Audio.h>
    #include <stdlib.h>
    #include <stddef.h>
    #include <time.h>
    #include "struct_elements.h"
int close_window(sfRenderWindow *window, sfSprite *cursor, int type);
void animate_sprite(sfSprite *sprite, int offset, int frame_count);
void move_sprite(sfSprite *sprite, float up, float left);
birds_t *create_bird(int speed, char *type);
element_t *create_button(char const *filepath, sfVector2f *pos, int type,
    int (*fptr)(sfRenderWindow *window, sfSprite *cursor, int type));
void animation_handling(int frames, sfSprite *sprite);
int analyse_events(sfRenderWindow *window,
    sfEvent event,
    element_t **sprites,
    sfSprite *cursor);
int go_to_main_game(sfRenderWindow *window, sfSprite *cursor, int type);
int main_loop(sfRenderWindow *window, sfSprite *cursor, int type);
void destroy_elements(element_t **elements);
int analyse_events_b(sfRenderWindow *window,
    sfEvent event,
    birds_t **birds,
    int level);
sfSprite *create_background(char const *filepath);
void move_rect(sfIntRect *rect, int offset, int max_value);
void death_handling(birds_t **bird, sfTime *time, sfClock *clock);
birds_t **kill_bird_or_player(sfRenderWindow *window, birds_t **birds,
    int *level, int type);
void destroy_birds(birds_t **birds, int level, int type);
void draw_birds_cursor(sfRenderWindow *window, birds_t **sprites, int level,
    sfSprite *cursor);
void draw_elements_cursor(sfRenderWindow *window, element_t **sprites,
    sfSprite *cursor);
int endless(sfRenderWindow *window, sfSprite *cursor, int type);
birds_t **create_birds(int level, int type);
birds_t **empty(birds_t **birds, int *level, int type, sfRenderWindow *window);
sprite_t *create_sprite(char const *filepath, sfVector2f *scale_str);
void draw_cursor(sfRenderWindow *window, sfSprite *cursor);
char *my_add_nbr(int nb);
void update_bird_pos(sfTime *time, birds_t **bird, sfClock *clock);
void update_normal_bird_pos(sfTime *time, birds_t **bird, sfClock *clock);
void update_evil_bird_pos(sfTime *time, birds_t **bird, sfClock *clock);
void update_supersonic_bird_pos(sfTime *time, birds_t **bird, sfClock *clock);
void draw_supersonic_bird(sfRenderWindow *window, birds_t **bird);
void draw_evil_bird(sfRenderWindow *window, birds_t **bird);
void draw_normal_bird(sfRenderWindow *window, birds_t **bird);
void choose_right_draw_func(sfRenderWindow *window, birds_t **bird, int level);
int my_strcmp(char const *s1, char const *s2);
text_n_font_t *create_text(char *message, char const *font, sfVector2f *pos);
void free_text(text_n_font_t *text);
void free_sprite(sprite_t *sprite);
int num_birds(int level, int type);
void show_score(text_n_font_t *my_text, int score, sfRenderWindow *window);
void free_after_game(text_n_font_t *my_text, sprite_t *background);
void draw_extras(text_n_font_t *my_text, sprite_t *bg, int score,
    sfRenderWindow *window);
void game_over(sfRenderWindow *window, sfSprite *cursor, int type, int score);
char *my_strcat(char *dest, char const *src);
char *my_strncat(char *dest, char const *src, int n);
char *my_strcpy(char *dst, char const *src);
char *my_strdup(char const *src);
int my_strlen(char const *str);
void *my_calloc(size_t length, size_t size);
char *my_revstr(char *str);
int my_getnbr(char *nb);
int show_help(void);
void between_levels(sfRenderWindow *window, int level, int type);
void store_high_score(int score, int type);
int get_high_score(int *len);

#endif
