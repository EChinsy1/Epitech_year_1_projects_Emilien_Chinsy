/*
** EPITECH PROJECT, 2026
** history
** File description:
** history
*/

#ifndef HISTORY_H
    #define HISTORY_H


typedef struct history_node_s {

    int id;
    char *command;
    struct history_node_s *next;
    struct history_node_s *prev;
} history_node_t;

typedef struct history_list_s {

    history_node_t *head;
    history_node_t *tail;
    int total_command;
} history_list_t;

#endif
