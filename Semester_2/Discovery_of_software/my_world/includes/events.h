/*
** EPITECH PROJECT, 2026
** my_world
** File description:
** events
*/

#ifndef EVENTS_H_
    #define EVENTS_H_
    #include <SFML/Graphics.h>
    #include <SFML/Graphics/RenderWindow.h>
    #include <SFML/Graphics/Types.h>
    #include <SFML/Graphics/VertexArray.h>
    #include <SFML/Window/Export.h>
    #include <SFML/Window/Types.h>
    #include "game.h"
    #include "buttons.h"
int manage_events(sfRenderWindow *, sfEvent *, game_t *, buttons_t **);
int execute_click(sfRenderWindow *window,
    sfMouseButtonEvent *event,
    game_t *game, buttons_t **buttons);
void execute_hover(sfRenderWindow *window,
    game_t *game, buttons_t **buttons, sfMouseButtonEvent *event);
#endif /* !EVENTS_H_ */
