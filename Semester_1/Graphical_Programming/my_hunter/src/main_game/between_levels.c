/*
** EPITECH PROJECT, 2025
** between levels
** File description:
** a file that has the functions that show text in between levels
*/

#include "my.h"
#include "macros.h"
#include "struct_elements.h"
#include "struct_levels.h"

static int analyse_events_between(sfRenderWindow *window,
    sfEvent event)
{
    int return_value = 0;

    while (sfRenderWindow_pollEvent(window, &event) && return_value == 0) {
        if (event.type == sfEvtClosed || ((event.type == sfEvtKeyPressed)
                && (((sfKeyEvent *)&event)->scancode == sfScanEscape)))
            close_window(window, NULL, 0);
        if (event.type == sfEvtMouseButtonPressed)
            return_value = 1;
    }
    sfRenderWindow_display(window);
    return (return_value);
}

static text_n_font_t **get_level_text(int level)
{
    char *level_text = EACH_LEVEL[level].level_text;
    char *temp_text;
    int len = my_strlen(level_text);
    int max = (len / LEN_BUBBLE);
    text_n_font_t **my_texts = my_calloc(sizeof(text_n_font_t**), (max + 2));
    int i = 0;

    for (; i < max; ++i) {
        temp_text = my_calloc(sizeof(char), LEN_BUBBLE + 1);
        my_strncat(temp_text, &level_text[i * LEN_BUBBLE], LEN_BUBBLE);
        my_texts[i] = create_text(my_strdup(temp_text), FONT, TXT_BTW_POS);
        free(temp_text);
    }
    temp_text = my_calloc(sizeof(char), LEN_BUBBLE + 1);
    my_strcat(temp_text, &level_text[(i) * LEN_BUBBLE]);
    my_texts[i] = create_text(my_strdup(temp_text), FONT, TXT_BTW_POS);
    free(temp_text);
    my_texts[i + 1] = NULL;
    return (my_texts);
}

static void show_texts(text_n_font_t **my_texts, sfRenderWindow *window)
{
    int i = 0;

    while (my_texts[i] != NULL){
        sfRenderWindow_drawText(window, my_texts[i]->text, NULL);
        ++i;
    }
}

static void free_texts(text_n_font_t **my_texts)
{
    int i = 0;

    while (my_texts[i] != NULL){
        free(my_texts[i]->text_value);
        sfText_destroy(my_texts[i]->text);
        sfFont_destroy(my_texts[i]->font);
        free(my_texts[i]);
        ++i;
    }
    free(my_texts);
}

static sprite_t **make_sprites(int level)
{
    int len_of_text = my_strlen(EACH_LEVEL[level].level_text);
    int scale_height = (len_of_text / LEN_BUBBLE +
        (len_of_text % LEN_BUBBLE != 0)) / 2;
    sprite_t *bg = create_sprite(BG_SPRITE, &((sfVector2f)SCALE_OF_BG));
    sprite_t *aim = create_sprite(AIM_SPRITE, &((sfVector2f)SCALE_OF_AIM));
    sprite_t *gun = create_sprite(GUN_SPRITE, &((sfVector2f){1, 1}));
    sprite_t *bubble = create_sprite(SPEECH_BUBBLE_SPRITE,
        &((sfVector2f){2.2, 1 + (0.1 * scale_height)}));
    sprite_t **sprites = malloc(sizeof(sprite_t *) * 5);

    sfSprite_setPosition(gun->sprite, GUN_POS);
    sfSprite_setPosition(bubble->sprite, SPEECH_BUBBLE_POS);
    sprites[0] = bg;
    sprites[1] = aim;
    sprites[2] = gun;
    sprites[3] = bubble;
    sprites[4] = NULL;
    return (sprites);
}

static void draw_everything(sprite_t **sprites, text_n_font_t **my_texts,
    sfRenderWindow *window)
{
    sfRenderWindow_drawSprite(window, sprites[0]->sprite, NULL);
    draw_cursor(window, sprites[1]->sprite);
    sfRenderWindow_drawSprite(window, sprites[2]->sprite, NULL);
    sfRenderWindow_drawSprite(window, sprites[3]->sprite, NULL);
    show_texts(my_texts, window);
    draw_cursor(window, sprites[1]->sprite);
}

static void free_sprites(sprite_t **sprites)
{
    free_sprite(sprites[0]);
    free_sprite(sprites[1]);
    free_sprite(sprites[2]);
    free_sprite(sprites[3]);
    free(sprites);
}

static void text_loop(sfRenderWindow *window, int level)
{
    sfEvent event;
    sprite_t **sprites = make_sprites(level);
    text_n_font_t **my_texts = get_level_text(level);
    int out = 0;

    while (sfRenderWindow_isOpen(window) && out == 0) {
        sfRenderWindow_clear(window, sfBlack);
        draw_everything(sprites, my_texts, window);
        if (analyse_events_between(window, event) == 1)
            out = 1;
    }
    free_sprites(sprites);
    free_texts(my_texts);
}

void between_levels(sfRenderWindow *window, int level, int type)
{
    if (type == LV && level < (MAX_LEVEL - 1))
        text_loop(window, level);
}
