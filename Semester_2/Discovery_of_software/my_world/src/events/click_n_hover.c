/*
** EPITECH PROJECT, 2026
** my_world
** File description:
** events
*/

#include <SFML/Graphics.h>
#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Sprite.h>
#include <SFML/Graphics/Types.h>
#include <SFML/Graphics/VertexArray.h>
#include <SFML/Window/Event.h>
#include <SFML/Window/Export.h>
#include <SFML/Window/Types.h>
#include <SFML/System/Vector2.h>
#include <SFML/Audio.h>
#include <stdio.h>
#include "game.h"
#include "macros.h"
#include "buttons.h"

static int hover(sfRenderWindow *window,
    buttons_t *button, sfMouseButtonEvent *event)
{
    sfVector2f pos_btn = sfSprite_getPosition(button->sprite);
    sfVector2i pos_cursor = sfMouse_getPositionRenderWindow(window);
    int x_btn = pos_btn.x;
    int y_btn = pos_btn.y;
    int x_cur = pos_cursor.x;
    int y_cur = pos_cursor.y;
    int size_x = button->size.x;
    int size_y = button->size.y;
    int scale_x = button->scale.x;
    int scale_y = button->scale.y;

    if (x_cur >= x_btn && x_cur <= (x_btn + (size_x * scale_x))){
        if (y_cur >= y_btn && y_cur <= (y_btn + (size_y * scale_y))){
            button->hovered = TRUE;
            return (1);
        }
    }
    button->hovered = FALSE;
    return (0);
}

static int mouse_click(sfRenderWindow *window,
    sfMouseButtonEvent *event,
    buttons_t *button, game_t *game)
{
    sfVector2f pos = sfSprite_getPosition(button->sprite);
    int x = pos.x;
    int y = pos.y;
    int size_x = button->size.x;
    int size_y = button->size.y;
    int scale_x = button->scale.x;
    int scale_y = button->scale.y;
    sfIntRect area = sfSprite_getTextureRect(button->sprite);

    if (event->x >= x && event->x <= (x + (size_x * scale_x))){
        if (event->y >= y && event->y <= (y + (size_y * scale_y))){
            area.left = 70;
            sfSprite_setTextureRect(button->sprite, area);
            sfMusic_play(button->sound);
            return (button->fptr(window, game));
        }
    }
    return (-1);
}

void execute_hover(sfRenderWindow *window,
    game_t *game, buttons_t **buttons, sfMouseButtonEvent *event)
{
    int i = 0;
    sfIntRect area;
    int hovering = 0;

    while (buttons[i]){
        area = sfSprite_getTextureRect(buttons[i]->sprite);
        hovering = hover(window, buttons[i], event);
        if (hovering == 1 && area.left != 70)
            area.left = 35;
        if (hovering == 0)
            area.left = 0;
        sfSprite_setTextureRect(buttons[i]->sprite, area);
        ++i;
    }
}

int execute_click(sfRenderWindow *window,
    sfMouseButtonEvent *event,
    game_t *game, buttons_t **buttons)
{
    int i = 0;
    int rtrn_val = -1;

    while (buttons[i]){
        rtrn_val = mouse_click(window, event, buttons[i], game);
        if (rtrn_val != -1)
            return (rtrn_val);
        ++i;
    }
    return (rtrn_val);
}
