/*
** EPITECH PROJECT, 2025
** game_over
** File description:
** a file that handles game overs
*/

#include "my.h"
#include "macros.h"
#include "struct_elements.h"

static int quit(sfRenderWindow *window, sfSprite *cursor, int type)
{
    sfRenderWindow_close(window);
    return (0);
}

static int menu(sfRenderWindow *window, sfSprite *cursor, int type)
{
    return (0);
}

static int retry(sfRenderWindow *window, sfSprite *cursor, int type)
{
    return (1);
}

static void clear_and_draw_bg(sfRenderWindow *window, sprite_t **bg_and_silo)
{
    sfRenderWindow_clear(window, sfBlack);
    sfRenderWindow_drawSprite(window, bg_and_silo[0]->sprite, NULL);
    sfRenderWindow_drawSprite(window, bg_and_silo[1]->sprite, NULL);
}

static void free_after_game_over(sprite_t **bg_and_silo, text_n_font_t *text_1,
    text_n_font_t *text_2, element_t **btns)
{
    free_text(text_1);
    free_text(text_2);
    free_sprite(bg_and_silo[0]);
    free_sprite(bg_and_silo[1]);
    free(bg_and_silo);
    destroy_elements(btns);
    free(btns);
}

static sfMusic *play_explosion(int type, int score)
{
    sfMusic *death_sound = sfMusic_createFromFile(SILO_EXPLODING_SOUND);

    if (type != LV || score != MAX_SCORE)
        sfMusic_play(death_sound);
    return (death_sound);
}

static void draw_end_text(sfRenderWindow *window, text_n_font_t *my_text,
    int score, int type)
{
    if (type == LV && score == MAX_SCORE){
        sfText_setString(my_text->text, "Congratulations, you win!");
        sfText_setPosition(my_text->text, (sfVector2f){450, 100});
    } else {
        sfText_setString(my_text->text, "You lost, try again?");
    }
    store_high_score(score, type);
    sfText_setCharacterSize(my_text->text, 100);
    sfText_setFont(my_text->text, my_text->font);
    sfRenderWindow_drawText(window, my_text->text, NULL);
}

static sprite_t **create_bg_and_silo(int type, int score)
{
    sprite_t *bg = create_sprite(BG_SPRITE, &((sfVector2f)SCALE_OF_BG));
    sprite_t *silo;
    sprite_t **bg_and_silo = malloc(sizeof(sprite_t *) * 3);

    if (type == LV && score == MAX_SCORE)
        silo = create_sprite(SILO_SPRITE, &((sfVector2f)SCALE_OF_SILO));
    else {
        silo = create_sprite(SILO_DEATH_SPRITE, &((sfVector2f)SCALE_OF_SILO));
    }
    sfSprite_setPosition(silo->sprite, SILO_POS);
    bg_and_silo[0] = bg;
    bg_and_silo[1] = silo;
    bg_and_silo[2] = NULL;
    return (bg_and_silo);
}

static element_t **make_buttons(void)
{
    element_t *try_btn = create_button(RETRY_BTN_SPRITE, TOP_MID, INF, &retry);
    element_t *menu_btn = create_button(MENU_BTN_SPRITE, MID_MID, LV, &menu);
    element_t *quit_btn = create_button(QUIT_BTN_SPRITE, BOT_MID, INF, &quit);
    element_t **btns = malloc(sizeof(element_t *) * 4);

    btns[0] = try_btn;
    btns[1] = menu_btn;
    btns[2] = quit_btn;
    btns[3] = NULL;
    return (btns);
}

void game_over(sfRenderWindow *window, sfSprite *cursor, int type, int score)
{
    sfEvent event;
    sprite_t **bg_and_silo = create_bg_and_silo(type, score);
    text_n_font_t *my_text = create_text("", FONT, WIN_TXT_POS);
    text_n_font_t *my_score = create_text("0", FONT, TOPPER_MID);
    element_t **btns = make_buttons();
    int btn_clicked = -1;
    sfMusic *death_sound = play_explosion(type, score);

    store_high_score(score, type);
    while (sfRenderWindow_isOpen(window) && btn_clicked == -1) {
        clear_and_draw_bg(window, bg_and_silo);
        draw_end_text(window, my_text, score, type);
        show_score(my_score, score, window);
        draw_elements_cursor(window, btns, cursor);
        btn_clicked = analyse_events(window, event, btns, cursor);
    }
    free_after_game_over(bg_and_silo, my_text, my_score, btns);
    sfMusic_destroy(death_sound);
    if (btn_clicked > 0)
        main_loop(window, cursor, type);
}
