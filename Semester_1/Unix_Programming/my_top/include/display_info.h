/*
** EPITECH PROJECT, 2026
** my_top
** File description:
** file containing the struct for scroll and unit parameters
*/

#ifndef DISPLAY_INFO_H
    #define DISPLAY_INFO_H

typedef struct display_info_s {
    int scroll;
    int proc_unit;
    int sys_unit;
    int curr_y;
    char *user_sort;
} display_info_t;

static const char NOTATION[] = {
    '\0',
    'm',
    'g',
    't',
    'p'
};

#endif
