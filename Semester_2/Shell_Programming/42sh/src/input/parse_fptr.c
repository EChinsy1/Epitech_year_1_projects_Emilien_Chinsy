/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** ez en fait
*/

#include "arguments.h"
#include "input.h"

void parse_arrows(char c, int *size, int *where, args_t *args)
{
    for (int i = 0; keys[i].key; ++i)
        if (keys[i].key == c) {
            keys[i].fct(size, where, args);
            return;
        }
}

void parse_ctrl(char c, int *size, int *where, args_t *args)
{
    for (int i = 0; ctrl_keys[i].key; ++i)
        if (ctrl_keys[i].key == c) {
            ctrl_keys[i].fct(size, where, args);
            return;
        }
}

void parse_alt(char c, int *size, int *where, args_t *args)
{
    for (int i = 0; alt_keys[i].key; ++i)
        if (alt_keys[i].key == c) {
            alt_keys[i].fct(size, where, args);
            return;
        }
}
