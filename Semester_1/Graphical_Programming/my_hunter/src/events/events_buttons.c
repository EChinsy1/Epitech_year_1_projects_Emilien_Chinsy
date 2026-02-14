/*
** EPITECH PROJECT, 2025
** events
** File description:
** a file which will contain some of the event calls
*/

#include "my.h"

int go_to_main_game(sfRenderWindow *window, sfSprite *cursor, int type)
{
    return (main_loop(window, cursor, type));
}

int close_window(sfRenderWindow *window, sfSprite *cursor, int type)
{
    sfRenderWindow_close(window);
    return (0);
}

static int hover(sfRenderWindow *window,
    element_t *element,
    sfSprite *cursor)
{
    sfVector2f pos_btn = sfSprite_getPosition(element->sprite);
    sfVector2f pos_cursor = sfSprite_getPosition(cursor);
    int x_btn = pos_btn.x - 100;
    int y_btn = pos_btn.y - 50;
    int x_cur = pos_cursor.x;
    int y_cur = pos_cursor.y;
    int size_x = element->size.x;
    int size_y = element->size.y;
    int scale_x = element->scale.x;
    int scale_y = element->scale.y;

    if (x_cur >= x_btn && x_cur <= (x_btn + (size_x * scale_x))){
        if (y_cur >= y_btn && y_cur <= (y_btn + (size_y * scale_y))){
            return (1);
        }
    }
    return (0);
}

static int mouse_click(sfRenderWindow *window,
    sfMouseButtonEvent *event,
    element_t *element,
    sfSprite *cursor)
{
    sfVector2f pos = sfSprite_getPosition(element->sprite);
    int x = pos.x;
    int y = pos.y;
    int size_x = element->size.x;
    int size_y = element->size.y;
    int scale_x = element->scale.x;
    int scale_y = element->scale.y;

    if (event->x >= x && event->x <= (x + (size_x * scale_x))){
        if (event->y >= y && event->y <= (y + (size_y * scale_y))){
            sfMusic_play(element->sound);
            return (element->fptr(window, cursor, element->type));
        }
    }
    return (-1);
}

static void execute_hover(sfRenderWindow *window,
    element_t **elements,
    sfSprite *cursor)
{
    int i = 0;
    sfIntRect area;

    while (elements[i]){
        area = sfSprite_getTextureRect(elements[i]->sprite);
        if (hover(window, elements[i], cursor) == 1)
            area.left = 26;
        else
            area.left = 0;
        sfSprite_setTextureRect(elements[i]->sprite, area);
        ++i;
    }
}

static int execute_click(sfRenderWindow *window,
    sfEvent event,
    element_t **elements,
    sfSprite *cursor)
{
    int i = 0;
    int rtrn_val = -1;

    while (elements[i]){
        rtrn_val = mouse_click(window, &event.mouseButton, elements[i], cursor);
        if (rtrn_val != -1)
            return (rtrn_val);
        ++i;
    }
    return (rtrn_val);
}

int analyse_events(sfRenderWindow *window,
    sfEvent event,
    element_t **elements,
    sfSprite *cursor)
{
    int return_value = -1;

    while (sfRenderWindow_pollEvent(window, &event)) {
        if (event.type == sfEvtClosed || ((event.type == sfEvtKeyPressed)
                && (((sfKeyEvent *)&event)->scancode == sfScanEscape)))
            close_window(window, NULL, 0);
        execute_hover(window, elements, cursor);
        if (event.type == sfEvtMouseButtonPressed){
            return_value = execute_click(window, event, elements, cursor);
        }
    }
    sfRenderWindow_display(window);
    return (return_value);
}
