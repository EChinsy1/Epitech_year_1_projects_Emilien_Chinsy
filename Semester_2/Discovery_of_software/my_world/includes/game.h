/*
** EPITECH PROJECT, 2026
** my_world
** File description:
** game
*/

#ifndef GAME_H_
    #define GAME_H_
    #include "camera.h"
    #include "transformation.h"
    #include <SFML/Graphics/RenderWindow.h>
    #include <SFML/Graphics/Types.h>
    #define F_LEN_MAP 10

typedef struct textures_s
{
    sfTexture *water;
    sfTexture *grass;
    sfTexture *mountain;
    sfTexture *mixed;
} textures_t;

typedef struct game_s
{
    struct textures_s *textures;
    trans_t *trans;
    cam_t *cam;
    sfCircleShape ***circles;
    int **map;
    int len_map;
    sfVector2f **map_2d;
    int size_x;
    int size_y;
    int old_size_x;
    int old_size_y;
    sfSprite *bg;
    sfSprite *cursor;
    sfTexture *bg_texture;
    sfTexture *cursor_texture;
    int freed;
} game_t;

game_t *create_gamestruct(void);
#endif /* !GAME_H_ */
