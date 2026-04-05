/*
** EPITECH PROJECT, 2026
** struct
** File description:
** struct
*/

#ifndef STRUCT_H_
    #define STRUCT_H_

typedef struct coords {
    int x;
    int y;
} coords_t;

typedef struct ginger_stats {
    int total_tokens;
    int curr_tokens;
    int curr_movement;
    int total_movement;
    int index_chasing;
    int type_chasing;
} ginger_stats_t;

#endif
