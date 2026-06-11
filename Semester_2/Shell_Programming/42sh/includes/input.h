/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Header file for the user input
*/

#ifndef INPUT_H
    #define INPUT_H

    #include <unistd.h>
    #include <string.h>
    #include "arguments.h"

    #define CURSORFORWARD write(1, "\033[C", strlen("\033[C"))
    #define CURSORBACKWARD write(1, "\033[D", strlen("\033[D"))
    #define KEYUP 'A'
    #define KEYDOWN 'B'
    #define KEYLEFT 'C'
    #define KEYRIGHT 'D'
    #define CTRL_A 1
    #define CTRL_E 5
    #define CTRL_P 16
    #define CTRL_N 14
    #define CTRL_H 8
    #define CTRL_D 4
    #define CTRL_B 2
    #define CTRL_F 6
    #define ALT_F 102
    #define ALT_B 98

void up_arrow(int *, int *, args_t *);
void down_arrow(int *, int *, args_t *);
void left_arrow(int *, int *, args_t *);
void right_arrow(int *, int *, args_t *);
void ctrl_a(int *size, int *where, args_t *args);
void ctrl_e(int *size, int *where, args_t *args);
void backspace(int *size, int *where, args_t *args);
void suppr(int *size, int *where, args_t *args);
void tab(int *size, int *where, args_t *args);
void alt_f(int *size, int *where, args_t *args);
void alt_b(int *size, int *where, args_t *args);

// parse
void parse_arrows(char c, int *size, int *where, args_t *args);
void parse_ctrl(char c, int *size, int *where, args_t *args);
void parse_alt(char c, int *size, int *where, args_t *args);

typedef struct keys_s {
    char key;
    void (*fct)(int *, int *, args_t *);
} keys_t;

static const keys_t keys[] = {
    {KEYUP, up_arrow},
    {KEYDOWN, down_arrow},
    {KEYLEFT, left_arrow},
    {KEYRIGHT, right_arrow},
    {0, NULL}
};

static const keys_t ctrl_keys[] = {
    {CTRL_A, ctrl_a},
    {CTRL_E, ctrl_e},
    {CTRL_P, up_arrow},
    {CTRL_N, down_arrow},
    {CTRL_H, backspace},
    {CTRL_D, suppr},
    {CTRL_B, right_arrow},
    {CTRL_F, left_arrow},
    {0, NULL}
};

static const keys_t alt_keys[] = {
    {ALT_F, alt_f},
    {ALT_B, alt_b},
    {0, NULL}
};

int my_getline(char **buffer, args_t *args);

#endif
