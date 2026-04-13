/*
** EPITECH PROJECT, 2025
** struct
** File description:
** a file that will hold a struct called square_components
** that will hold the necessary characters to differentiate each square
*/

#ifndef STRUCT_H_
    #define STRUCT_H_

typedef struct square_components{
    char top_left;
    char top_right;
    char bot_left;
    char bot_right;
    char line_char;
    char col_char;
    int exists;
} square_components_t;

const struct square_components COMPONENTS[] = {
    {'o', 'o', 'o', 'o', '-', '|', 1},
    {'/', '\\', '\\', '/', '*', '*', 1},
    {'A', 'A', 'C', 'C', 'B', 'B', 1},
    {'A', 'C', 'A', 'C', 'B', 'B', 1},
    {'A', 'C', 'C', 'A', 'B', 'B', 1},
    {' ', ' ', ' ', ' ', ' ', ' ', 0}};

#endif
