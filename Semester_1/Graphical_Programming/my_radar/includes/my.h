/*
** EPITECH PROJECT, 2025
** caac
** File description:
** caca
*/

#ifndef MY_H_
    #define MY_H_

    #include <SFML/Graphics.h>
    #include <SFML/Window/Export.h>
    #include <SFML/Window/Types.h>
    #include <SFML/System/Vector2.h>
    #include <SFML/Audio.h>
    #include <unistd.h>
    #include <stdio.h>
    #include <math.h>
    #include "struct.h"
    #include "quad_tree.h"

int analyse_events(sfRenderWindow *window, sfEvent event,
    game_t *game);
int intersect(int radius_one,
    sfCircleShape *circle_one,
    sfCircleShape *circle_two,
    int radius_two);
void *my_calloc(size_t length, size_t size);
char *my_strncat(char *dest, char const *src, int nb);
char **my_str_to_word_array(char const *str);
int my_getnbr(char const *str);
int get_num_of_planes_and_towers(int size, char *buffer,
    game_t **game);
void fill_arrays(char *buffer, int size, game_t **game);
char *read_full_file(char const *filepath, int *size);
void draw_sprites(sfRenderWindow *window, game_t *game, float time);
void check_collisions(game_t **game);
int check_quad_tree_collision(game_t **game, qt_t *tree,
    planes_t *plane, int j);
void init_qt(qt_t **item, float height, float width);
void qt_free(qt_t *item);
int add_node(qt_t *parent, planes_t *plane,
    int index, game_t *game);
void qt_print_tree(qt_t *parent, aab_t *box, game_t *game);
int which_quadrant(game_t **game, qt_t *tree,
    planes_t *plane, int j);
int delete_no_tree(game_t **game, float pos_plane[2], qt_t *tree, int j);
int contains(aab_t *bounds, float pos_plane[2]);
int return_n_free(char *buffer, char *line, game_t *game);
text_n_font_t *create_text(char *message, char const *font, sfVector2f *pos);
void free_text(text_n_font_t *my_text);
void combine_text(text_n_font_t *my_text, float timer,
    sfRenderWindow *window, char *normal_text);
char *my_strcat(char *dest, char const *src);
int my_strcmp(char const *s1, char const *s2);
char *my_strcpy(char *dst, char const *src);
char *my_add_nbr(int nb);
char *my_revstr(char *str);
int my_strlen(char *str);
sprite_t *create_sprite(const char *filepath, sfVector2f *scale);
char *read_full_file(char const *filepath, int *size);
char *get_string_line(char *buffer, int *start);

#endif
