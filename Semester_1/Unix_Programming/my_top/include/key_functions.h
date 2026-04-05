/*
** EPITECH PROJECT, 2026
** my_top
** File description:
** header file containing key bound functions for top
*/

#ifndef KEY_FUNCS_H
    #define KEY_FUNCS_H

    #include <ncurses.h>
    #include "process_struct.h"
    #include "display_info.h"

    #define AMT_OF_KEYBINDS 5

struct key_functions_s {
    int keybind;
    void (*function)(procs_t *, display_info_t *);
};

void scroll_up(procs_t *, display_info_t *);
void scroll_down(procs_t *, display_info_t *);
void kill_proc(procs_t *, display_info_t *);
void cycle_proc_units(procs_t *, display_info_t *);
void cycle_sys_units(procs_t *, display_info_t *);

static const struct key_functions_s KEY_FUNCS[] = {
    {KEY_UP, &scroll_up},
    {KEY_DOWN, &scroll_down},
    {'k', &kill_proc},
    {'e', &cycle_proc_units},
    {'E', &cycle_sys_units}
};

#endif
