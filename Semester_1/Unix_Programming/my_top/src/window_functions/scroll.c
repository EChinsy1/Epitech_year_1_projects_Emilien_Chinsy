/*
** EPITECH PROJECT, 2026
** my_top
** File description:
** file containing scroll functions for my_top
*/

#include <ncurses.h>
#include "my_top.h"
#include "display_info.h"

void scroll_up(procs_t *list, display_info_t *display_info)
{
    if (display_info->scroll > 0)
        display_info->scroll -= 1;
}

void scroll_down(procs_t *list, display_info_t *display_info)
{
    display_info->scroll += 1;
}
