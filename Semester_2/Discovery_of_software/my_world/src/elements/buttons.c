/*
** EPITECH PROJECT, 2026
** myworld
** File description:
** buttons
*/

#include <SFML/Audio.h>
#include <SFML/Graphics/CircleShape.h>
#include <SFML/Graphics/Color.h>
#include <SFML/Graphics/RectangleShape.h>
#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Text.h>
#include <SFML/Graphics/Texture.h>
#include <SFML/Graphics/Types.h>
#include <SFML/System/Vector2.h>
#include <SFML/Graphics/Sprite.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include "buttons.h"
#include "macros.h"
#include "game.h"
#include "my_world.h"

static int map_rand(sfRenderWindow *window, game_t *game)
{
    for (int i = 0; i < game->size_x; ++i) {
        for (int j = 0; j < game->size_y; ++j) {
            game->map[i][j] = (rand() % 3) - 1;
        }
    }
    return (0);
}

static int reset(sfRenderWindow *window, game_t *game)
{
    for (int i = 0; i < game->size_x; ++i) {
        for (int j = 0; j < game->size_y; ++j) {
            game->map[i][j] = 0;
        }
    }
    return (0);
}

static int plus(sfRenderWindow *window, game_t *game)
{
    int **new_map = calloc(sizeof(int *), game->size_x + 2);

    game->size_x += 1;
    game->size_y += 1;
    for (int i = 0; i < game->size_x - 1; ++i) {
        new_map[i] = calloc(sizeof(int), game->size_y + 2);
        for (int j = 0; j < game->size_y - 2; ++j) {
            new_map[i][j] = game->map[i][j];
        }
        free(game->map[i]);
        new_map[i][game->size_y - 1] = 0;
        new_map[i][game->size_y] = -1;
    }
    new_map[game->size_x - 1] = calloc(sizeof(int), game->size_y + 2);
    new_map[game->size_x - 1][game->size_y - 1] = 0;
    new_map[game->size_x - 1][game->size_y] = -1;
    free(game->map);
    game->map = new_map;
    return (0);
}

static int minus(sfRenderWindow *window, game_t *game)
{
    int **new_map = NULL;

    if (game->size_x <= 0 || game->size_y <= 0)
        return (84);
    new_map = calloc(sizeof(int *), game->size_x);
    game->size_x -= 1;
    game->size_y -= 1;
    for (int i = 0; i < game->size_x; ++i) {
        new_map[i] = calloc(sizeof(int), game->size_y + 1);
        for (int j = 0; j < game->size_y; ++j) {
            new_map[i][j] = game->map[i][j];
        }
        new_map[i][game->size_y] = -1;
        free(game->map[i]);
    }
    free(game->map[game->size_x]);
    free(game->map);
    game->map = new_map;
    return (0);
}

static int save(sfRenderWindow *window, game_t *game)
{
    char *value = get_user_input("please enter the name you want to save as.");
    int fd = 0;
    char to_write[20];

    if (value == NULL)
        return (-1);
    strcat(value, ".legend");
    fd = open(value, (O_CREAT | O_APPEND | O_RDWR), 00664);
    if (fd < 0)
        return (-1);
    for (int i = 0; i < game->size_x; ++i) {
        for (int j = 0; j < game->size_y; ++j) {
            sprintf(to_write, "%d", game->map[i][j]);
            write(fd, to_write, strlen(to_write));
        }
        write(fd, "\n", 1);
    }
    write(fd, "\0", 1);
    free(value);
    return (close(fd));
}

static buttons_t *apply_global(void)
{
    buttons_t *button = malloc(sizeof(buttons_t) * 1);
    sfSprite *sprite = sfSprite_create();
    sfMusic *music = sfMusic_createFromFile(BTN_CLICK_SOUND);
    sfRectangleShape *help_box = sfRectangleShape_create();
    sfVector2f size = {300, 200};

    button->size = (sfVector2i)SIZE_OF_BUTTON;
    button->scale = (sfVector2f)SCALE_OF_BUTTON;
    button->sound = music;
    button->sprite = sprite;
    button->helpbox = help_box;
    button->hovered = FALSE;
    sfSprite_setScale(button->sprite, (sfVector2f)SCALE_OF_BUTTON);
    sfRectangleShape_setFillColor(button->helpbox,
        sfColor_fromRGB(242, 198, 75));
    sfRectangleShape_setSize(button->helpbox, size);
    return (button);
}

static buttons_t *create_button(char const *filepath, sfVector2f *pos,
    int (*fptr)(sfRenderWindow *window, game_t *game), char *helpbox_text)
{
    buttons_t *button = apply_global();
    sfTexture *texture = sfTexture_createFromFile(filepath, NULL);
    sfIntRect area = {0, 0, 30, 30};

    button->fptr = fptr;
    button->texture = texture;
    sfSprite_setPosition(button->sprite, *pos);
    sfSprite_setTexture(button->sprite, button->texture, sfTrue);
    sfSprite_setTextureRect(button->sprite, area);
    (*pos).y += 120;
    button->help_text = create_text(helpbox_text, "Ougkeh.otf", pos);
    sfText_setString(button->help_text->text, helpbox_text);
    sfRectangleShape_setPosition(button->helpbox, *pos);
    return button;
}

void draw_buttons(sfRenderWindow *window, buttons_t **buttons)
{
    int i = 0;

    while (buttons[i]) {
        sfRenderWindow_drawSprite(window, buttons[i]->sprite, NULL);
        if (buttons[i]->hovered == TRUE) {
            sfRenderWindow_drawRectangleShape(window,
                buttons[i]->helpbox, NULL);
            sfRenderWindow_drawText(window, buttons[i]->help_text->text, NULL);
        }
        ++i;
    }
}

void make_button_2(buttons_t **btns)
{
    buttons_t *rand_bt = create_button(RANDOM, &((sfVector2f){175 * 4, 0}),
        &map_rand, "random button:\nrands the map\n");

    btns[5] = rand_bt;
    btns[6] = NULL;
}

buttons_t **make_main_menu_btns(void)
{
    buttons_t *reset_btn = create_button(BOMB, &((sfVector2f){0, 0}),
        &reset, "Reset button:\nresets the height\nof the map\nback to 0.");
    buttons_t *save_btn = create_button(SAVE, &((sfVector2f){35 * 4, 0}),
        &save, "Save button:\nsaves the\ncurrent state\nof your map.");
    buttons_t *plus_btn = create_button(PLUS, &((sfVector2f){70 * 4, 0}),
        &plus, "Plus button:\nadds a column\nand a line.");
    buttons_t *minus_btn = create_button(MINUS, &((sfVector2f){105 * 4, 0}),
        &minus, "Minus button:\nremoves a column\nand a line.");
    buttons_t *load_btn = create_button(LOAD, &((sfVector2f){140 * 4, 0}),
        &load, "Load button:\nloads the map\ncontained in a file\n");
    buttons_t **btns = malloc(sizeof(buttons_t *) * 7);

    btns[0] = reset_btn;
    btns[1] = save_btn;
    btns[2] = plus_btn;
    btns[3] = minus_btn;
    btns[4] = load_btn;
    make_button_2(btns);
    return (btns);
}
