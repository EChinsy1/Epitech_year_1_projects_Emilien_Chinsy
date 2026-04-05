/*
** EPITECH PROJECT, 2026
** myworld
** File description:
** myworld
*/

#ifndef MY_WORLD_H_
    #define MY_WORLD_H_
    #include <SFML/Graphics.h>
    #include "game.h"
    #include "buttons.h"
sfVector2f project_iso_point(int x, int y, int z, game_t *game);
sfVector2f **create_2d_map(game_t *, int **);
int draw_2d_map(sfRenderWindow *, game_t *, sfCircleShape ***);
int draw_2d_map_0(sfRenderWindow *, game_t *, sfCircleShape ***, int **);
int draw_2d_map_1(sfRenderWindow *, game_t *, sfCircleShape ***, int **);
int draw_2d_map_2(sfRenderWindow *, game_t *, sfCircleShape ***, int **);
int draw_2d_map_3(sfRenderWindow *, game_t *, sfCircleShape ***, int **);
int **make_3d_map(int size_x, int size_y);
buttons_t **make_main_menu_btns(void);
void draw_buttons(sfRenderWindow *window, buttons_t **buttons);
sfCircleShape ***draw_circles(sfVector2f **map, game_t *game,
    int **map_3d);
text_n_font_t *create_text(char *message, char const *font, sfVector2f *pos);
void create_cursor(game_t *game, const char *path);
void put_cursor(sfRenderWindow *window, game_t *game);
char *get_user_input(char *name);
int load(sfRenderWindow *window, game_t *game);
void free_after_loop(sfVector2f **map, game_t *game);
#endif
