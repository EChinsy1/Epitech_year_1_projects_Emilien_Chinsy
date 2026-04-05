/*
** EPITECH PROJECT, 2026
** amazed
** File description:
** header file for amazed
*/

#ifndef AMAZED_H
    #define AMAZED_H

typedef struct robot_s {
    int id;
    int room;
    int path_index;
    int path_step;
    struct robot_s *next;
} robot_t;

typedef struct temp_room_s {
    char *name;
    int coords[2];
    struct temp_room_s *next;
}tmp_room_t;

typedef struct rooms_s {
    int *occupied;
    int **matrix;
    char **names;
    robot_t *robots;
    tmp_room_t *head;
    int len_mat;
    int nb_robi;
    int start;
    int end;
    char **liens;
    int ind_lien;
} rooms_t;

int amazed(void);
void free_int_array(int **);
void display_input(rooms_t *);
int get_room(char *, rooms_t *, int *);
int start_handler(char *, rooms_t *, int *);
int free_and_return(char *, int);
void free_graph(rooms_t *);

#endif /* AMAZED_H */
