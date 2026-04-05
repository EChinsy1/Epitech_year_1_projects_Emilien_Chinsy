/*
** EPITECH PROJECT, 2026
** my_top
** File description:
** header file containing the procs_t typedef
*/

#ifndef PROCS_H
    #define PROCS_H

typedef struct procs_s {
    int pid;
    int uid;
    char *user;
    char *name;
    int priority;
    int nice_value;
    long cpu_percent;
    long virt_mem;
    long res_mem;
    long shr_mem;
    char status;
    long time;
    struct procs_s *next;
} procs_t;

#endif
