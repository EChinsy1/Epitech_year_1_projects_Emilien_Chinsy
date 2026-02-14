/*
** EPITECH PROJECT, 2025
** struct.h
** File description:
** contains the structure for the game elements.
** the function pointer contains the function to call when clicked on.
*/

#ifndef MACROS_H_
    #define MACROS_H_

    #include "my.h"
    #define ABS(x) ((x) < 0 ? -(x) : (x))

    #define TOP_LEFT &((sfVector2f){0, 0})
    #define MAX_TOP_MID &((sfVector2f){750, 100})
    #define TOP_LEFT_MID &((sfVector2f){700, 200})
    #define TOPPER_MID &((sfVector2f){800, 200})
    #define TOP_MID &((sfVector2f){850, 340})
    #define MID_MID &((sfVector2f){850, 500})
    #define BOT_MID &((sfVector2f){850, 660})
    #define WIN_TXT_POS &((sfVector2f){500, 100})
    #define TXT_BTW_POS &((sfVector2f){500, 100 * i})
    #define SILO_POS (sfVector2f){1500, 70}
    #define SPEECH_BUBBLE_POS (sfVector2f){450, 0}
    #define GUN_POS (sfVector2f){0, 600}
    #define SCALE_OF_BIRD {2, 2}
    #define AREA_OF_BIRD {0, 0, 110, 110}
    #define SIZE_OF_BUTTON {25, 10}
    #define SCALE_OF_BUTTON {10, 10}
    #define SCALE_OF_AIM {5, 5}
    #define SCALE_OF_SILO {1.5, 1.5}
    #define SCALE_OF_BG {6, 4.5}
    #define SIZE_OF_BIRD {110, 110}
    #define LV 1
    #define INF 0
    #define MAX_LEVEL 10
    #define MAX_SCORE 133
    #define WIND_UP_SUPERSONIC 2000000
    #define WIND_UP_NORMAL 1000000
    #define NORMAL_SPEED 1
    #define SUPERSONIC_SPEED 20
    #define NORMAL_HP 1
    #define EVIL_HP 3
    #define SUPERSONIC_HP 2
    #define LEN_BUBBLE 20
static const char *const BG_SPRITE = "sprites/background.jpeg";
static const char *const QUIT_BTN_SPRITE = "sprites/quit_button.png";
static const char *const LONG_BTN_SPRITE = "sprites/long_button.png";
static const char *const START_BTN_SPRITE = "sprites/start_button.png";
static const char *const MENU_BTN_SPRITE = "sprites/menu_button.png";
static const char *const RETRY_BTN_SPRITE = "sprites/retry_button.png";
static const char *const AIM_SPRITE = "sprites/cursor.png";
static const char *const FONT = "Ougkeh.otf";
static const char *const SILO_SPRITE = "sprites/grain_silo.png";
static const char *const SILO_DEATH_SPRITE =
    "sprites/grain_silo_death.png";
static const char *const SPEECH_BUBBLE_SPRITE =
    "sprites/speech_bubble.png";
static const char *const GUN_SPRITE = "sprites/gun.png";
static const char *const BIRD_SPRITESHEET = "sprites/bird_spritesheet.png";
static const char *const FAST_BIRD_SPRITESHEET =
    "sprites/fast_bird_spritesheet.png";
static const char *const EVIL_BIRD_SPRITESHEET =
    "sprites/evil_bird_spritesheet.png";
static const char *const DEATH_BIRD_SOUND = "sounds/quack_reverb.mp3";
static const char *const BTN_CLICK_SOUND = "sounds/button_click.mp3";
static const char *const SILO_EXPLODING_SOUND =
    "sounds/deltarune_explosion.mp3";
static const char *const NORMAL = "normal";
static const char *const EVIL = "evil";
static const char *const SUPERSONIC = "supersonic";

#endif
