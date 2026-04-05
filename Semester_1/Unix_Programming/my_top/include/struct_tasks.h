/*
** EPITECH PROJECT, 2026
** struct_cpu
** File description:
** file for my_top containing the cpu stats
*/

#ifndef STRUCT_TASKS_H
    #define STRUCT_TASKS_H

typedef struct tasks {
    int total;
    int running;
    int sleeping;
    int stopped;
    int zombie;
} tasks_t;

#endif
