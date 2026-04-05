/*
** EPITECH PROJECT, 2026
** myworld
** File description:
** myworld
*/

#ifndef MACROS_H_
    #define MACROS_H_
    #define SUCCESS 0
    #define FAIL 1
    #define TRUE 1
    #define FALSE 0
    #define NOPE -1
    #define WIDTH 1920
    #define HEIGHT 1080
    #define SIZE_OF_BUTTON {40, 40}
    #define SCALE_OF_BUTTON {4, 4}
    #define BACKSPACE 8
    #define TOO_FAR 127
    #define NOT_FAR_ENOUGH 32
    #define MAX_INPUT 30

static const char *const BOMB = "spritesheets/bomb_button.png";
static const char *const SAVE = "spritesheets/save_button.png";
static const char *const PLUS = "spritesheets/plus_button.png";
static const char *const MINUS = "spritesheets/minus_button.png";
static const char *const LOAD = "spritesheets/load_button.png";
static const char *const RANDOM = "spritesheets/random_button.png";
static const char *const CURSOR_SPRITE = "textures/cursor.png";
static const char *const BOMB_SPRITE = "spritesheets/bomb_button.png";
static const char *const SAVE_SPRITE = "spritesheets/save_button.png";
static const char *const PLUS_SPRITE = "spritesheets/plus_button.png";
static const char *const MINUS_SPRITE = "spritesheets/minus_button.png";
static const char *const BG_PATH = "./textures/espace.jpg";
static const char *const BTN_CLICK_SOUND = "audio/deltarune_explosion.mp3";
static const char *const BOMB_HELP_TEXT = "Reset button:\nresets the height\nof the map\nback to 0.";
static const char *const SAVE_HELP_TEXT = "Save button:\nsaves the\ncurrent state\nof your map.";
static const char *const PLUS_HELP_TEXT = "Plus button:\nadds a column\nand a line.";
static const char *const MINUS_HELP_TEXT = "Minus button:\nremoves a column\nand a line.";
static const char *const LOAD_HELP_TEXT = "Load button:\nloads the map\ncontained in a file\n";
static const char ENTER_KEY = '\r';

#endif