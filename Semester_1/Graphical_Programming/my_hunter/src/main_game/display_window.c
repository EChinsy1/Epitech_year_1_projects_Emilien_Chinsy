/*
** EPITECH PROJECT, 2025
** first task
** File description:
** first task
*/

#include <unistd.h>
#include "my.h"
#include "macros.h"
#include "struct_elements.h"

int main_loop(sfRenderWindow *window, sfSprite *cursor, int type)
{
    sfEvent event;
    int level = 1;
    int score = 0;
    text_n_font_t *my_text = create_text("0", FONT, TOP_LEFT);
    sprite_t *bg = create_sprite(BG_SPRITE, &((sfVector2f)SCALE_OF_BG));
    birds_t **birds = create_birds(level, type);

    between_levels(window, level - 1, type);
    while (sfRenderWindow_isOpen(window) && level >= 1) {
        sfRenderWindow_clear(window, sfWhite);
        draw_extras(my_text, bg, score, window);
        draw_birds_cursor(window, birds, num_birds(level, type), cursor);
        score += analyse_events_b(window, event, birds, num_birds(level, type));
        birds = kill_bird_or_player(window, birds, &(level), type);
    }
    level = ABS(level);
    free_after_game(my_text, bg);
    destroy_birds(birds, level, type);
    game_over(window, cursor, type, score);
    return (0);
}

static sfMusic *create_main_music(void)
{
    sfMusic *main_music = sfMusic_createFromFile("sounds/game_music.mp3");

    sfMusic_setLoop(main_music, sfTrue);
    sfMusic_play(main_music);
    return (main_music);
}

static element_t **make_main_menu_btns(void)
{
    element_t *longg = create_button(LONG_BTN_SPRITE, TOP_MID, INF, &main_loop);
    element_t *start = create_button(START_BTN_SPRITE, MID_MID, LV, &main_loop);
    element_t *qt = create_button(QUIT_BTN_SPRITE, BOT_MID, INF, &close_window);
    element_t **btns = malloc(sizeof(element_t *) * 4);

    btns[0] = start;
    btns[1] = qt;
    btns[2] = longg;
    btns[3] = NULL;
    return (btns);
}

static text_n_font_t *set_high_score_text(void)
{
    int len = 0;
    int score = get_high_score(&len);
    text_n_font_t *high_txt = create_text(" ", FONT, TOP_LEFT_MID);
    char *final_text = "Highscore: ";
    char *score_text = my_add_nbr(score);

    final_text = my_calloc(sizeof(char), len + my_strlen(final_text) + 1);
    my_strcat(final_text, "Highscore: ");
    my_strcat(final_text, score_text);
    free(score_text);
    high_txt->text_value = my_strdup(final_text);
    free(final_text);
    sfText_setString(high_txt->text, high_txt->text_value);
    return (high_txt);
}

static void free_main_menu(sfMusic *main_music, text_n_font_t *high_score,
    element_t **sprites)
{
    sfMusic_destroy(main_music);
    free(high_score->text_value);
    free_text(high_score);
    destroy_elements(sprites);
    free(sprites);
}

static void main_menu(sfRenderWindow *window, sfSprite *cursor)
{
    sfEvent event;
    sprite_t *bg = create_sprite(BG_SPRITE, &((sfVector2f)SCALE_OF_BG));
    text_n_font_t *my_text = create_text("My_Hunter", FONT, MAX_TOP_MID);
    text_n_font_t *high_score = set_high_score_text();
    element_t **sprites = make_main_menu_btns();
    sfMusic *main_music = create_main_music();

    while (sfRenderWindow_isOpen(window)) {
        sfRenderWindow_clear(window, sfBlack);
        sfRenderWindow_drawSprite(window, bg->sprite, NULL);
        draw_elements_cursor(window, sprites, cursor);
        sfRenderWindow_drawText(window, my_text->text, NULL);
        sfRenderWindow_drawText(window, high_score->text, NULL);
        analyse_events(window, event, sprites, cursor);
    }
    free_main_menu(main_music, high_score, sprites);
    free_after_game(my_text, bg);
}

int game(void)
{
    sfVideoMode mode = {1920, 1080, 32};
    sfRenderWindow *window;
    sprite_t *aim = create_sprite(AIM_SPRITE, &((sfVector2f)SCALE_OF_AIM));

    sfListener_setGlobalVolume(100);
    srand(time(NULL));
    window = sfRenderWindow_create(mode, "My_Hunter", sfClose | sfResize, NULL);
    sfRenderWindow_setMouseCursorVisible(window, sfFalse);
    sfRenderWindow_setFramerateLimit(window, 60);
    if (!window)
        return (84);
    main_menu(window, aim->sprite);
    free_sprite(aim);
    sfRenderWindow_destroy(window);
    return (0);
}

int main(int argc, char **argv)
{
    if (argc == 2 && my_strcmp(argv[1], "-h") == 0)
        return (show_help());
    else if (argc == 1)
        return (game());
    else {
        write(1, "invalid arguments\n", 18);
        write(1, "either type: ./my_hunter, or ", 30);
        write(1, "./my_hunter -h for the instructions.", 37);
        return (84);
    }
}
