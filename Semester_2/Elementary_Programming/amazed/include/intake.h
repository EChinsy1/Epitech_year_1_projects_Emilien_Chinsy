/*
** EPITECH PROJECT, 2026
** amazed
** File description:
** intake
*/

#ifndef INTAKE_H_
    #define INTAKE_H_
    #define START 0
    #define END 1
    #include <stdbool.h>
    #include "amazed.h"
rooms_t *formating(rooms_t *);
rooms_t *get_inputs(void);
int get_link(rooms_t *);
int **create_matrix(int);
bool has_room(char *name, tmp_room_t *head);
bool has_coords(int *coords, tmp_room_t *head);
rooms_t *create_graph(void);
int add_room(char *input, rooms_t *graph, int *nb_rooms);
tmp_room_t *create_room(char *input, rooms_t *graph);
int is_link(char **input, tmp_room_t *head);
void add_link(rooms_t *graph, char **links);
#endif /* !INTAKE_H_ */
