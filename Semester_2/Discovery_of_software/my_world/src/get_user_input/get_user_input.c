/*
** EPITECH PROJECT, 2019
** my_world
** File description:
** Pops and prompts text in a window
*/

#include <SFML/Graphics.h>
#include <SFML/Graphics/BlendMode.h>
#include <SFML/Graphics/CircleShape.h>
#include <SFML/Graphics/Color.h>
#include <SFML/Graphics/Font.h>
#include <SFML/Graphics/PrimitiveType.h>
#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/RenderStates.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Text.h>
#include <SFML/Graphics/Transform.h>
#include <SFML/Graphics/Types.h>
#include <SFML/Graphics/VertexArray.h>
#include <SFML/Window/Event.h>
#include <SFML/Window/Export.h>
#include <SFML/Window/Types.h>
#include <SFML/System/Vector2.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "my_world.h"
#include "macros.h"
#include "text.h"

static int backspace_exec(char *prompt)
{
    int len = strlen(prompt);

    if (len == 0)
        return (0);
    prompt[len - 1] = '\0';
    return (0);
}

static int check_return(char *prompt)
{
    int len = strlen(prompt);

    if (len == 0)
        return (0);
    else
        return (1);
    return (0);
}

static int add_char(char *prompt, char c)
{
    int len = strlen(prompt);

    if (len >= MAX_INPUT)
        return (0);
    prompt[len] = c;
    prompt[len + 1] = '\0';
    return (0);
}

int update_text(sfEvent event, char *prompt)
{
    char input = event.text.unicode;

    if (input == ENTER_KEY)
        return (check_return(prompt));
    if (input == BACKSPACE)
        return (backspace_exec(prompt));
    if (input >= TOO_FAR || input < NOT_FAR_ENOUGH)
        return (-1);
    add_char(prompt, event.text.unicode);
    return (0);
}

static int analyse_text_events(sfRenderWindow *win, sfEvent event, char *input)
{
    if (event.type == sfEvtClosed)
        sfRenderWindow_close(win);
    if (event.type == sfEvtTextEntered)
        return (update_text(event, input));
    return (0);
}

static char *free_and_return(int event_return, char *input, text_n_font_t *text,
    sfRenderWindow *window)
{
    char *return_string = NULL;
    int i = 0;

    sfText_destroy(text->text);
    sfFont_destroy(text->font);
    free(text);
    sfRenderWindow_destroy(window);
    if (event_return == 0)
        return (NULL);
    return_string = malloc(sizeof(char) * strlen(input) + 8);
    while (input[i] != '\0') {
        return_string[i] = input[i];
        ++i;
    }
    return_string[i] = '\0';
    free(input);
    return (return_string);
}

static void get_the_input(text_n_font_t *text, char input[MAX_INPUT],
    sfRenderWindow *window)
{
    sfText_setString(text->text, input);
    sfRenderWindow_clear(window, sfBlack);
    sfRenderWindow_drawText(window, text->text, NULL);
    sfRenderWindow_display(window);
}

char *get_user_input(char *name_of_window)
{
    sfVideoMode mode = {WIDTH, 100, 32};
    sfVector2i pos = {500, 500};
    sfRenderWindow *window = sfRenderWindow_create(mode, name_of_window,
        sfClose | sfResize, NULL);
    sfEvent event;
    int event_return = 0;
    text_n_font_t *text = create_text("", "Ougkeh.otf", &(sfVector2f){0, 0});
    char *input = calloc(sizeof(char), MAX_INPUT);

    sfText_setColor(text->text, sfWhite);
    while (sfRenderWindow_isOpen(window)) {
        while (sfRenderWindow_pollEvent(window, &event))
            event_return = analyse_text_events(window, event, input);
        get_the_input(text, input, window);
        if (event_return == 1)
            sfRenderWindow_close(window);
    }
    return (free_and_return(event_return, input, text, window));
}
