/*
** EPITECH PROJECT, 2025
** struct color
** File description:
** struct for color printing
*/

#ifndef STRUCT_COLOR_
    #define STRUCT_COLOR_

typedef struct color_printer {
    int (*check)(struct stat *sb);
    void (*apply)(char *name);
} color_printer_t;

const struct color_printer EACH_TYPE[] = {
    {&is_device, &print_device},
    {&is_fifo, &print_fifo},
    {&is_exec, &print_exec},
    {&is_link, &print_link},
    {&is_sock, &print_sock},
    {&is_sticky_and_ow, &print_sticky_and_ow},
    {&is_not_sticky_and_ow, &print_not_sticky_and_ow},
    {&is_sticky_and_not_ow, &print_sticky_and_not_ow},
    {&is_dir, &print_dir},
    {NULL, NULL}};

#endif
