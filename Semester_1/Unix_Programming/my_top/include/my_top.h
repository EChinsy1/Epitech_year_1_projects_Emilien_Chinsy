/*
** EPITECH PROJECT, 2026
** my_top
** File description:
** header file for my_top
*/

#ifndef MY_TOP_H
    #define MY_TOP_H

    #include <stdio.h>
    #include <time.h>
    #include "struct_cpu.h"
    #include "struct_tasks.h"
    #include "process_struct.h"
    #include "mem_struct.h"
    #include "uid_and_user_struct.h"
    #include "display_info.h"

int my_top(int, char **);
int my_str_isnum(char const *str);
int end_free(char *buffer, FILE *stream);
uid_n_user_t *get_all_users(void);
int my_getloadavg(double loadavg[], int nelem);
int my_getuptime(int uptime[]);
int my_getnumusers(void);
mem_struct_t *my_getmemvalues(int);
void free_procs(procs_t *procs);
tasks_t *my_getfrompid(procs_t **procs, uid_n_user_t *users);
void my_getcpustats(cpu_stats_t *);
char *my_getsystime(void);
FILE *open_file(char *name);
void screen_loop(int max_frames, uid_n_user_t *users, char *, cpu_stats_t *);
void init_screen(int);
void terminate_screen(void);
void display_sys(long val_for_cpu_and_mem_percent[2], int, cpu_stats_t *);
void display_procs(procs_t *, display_info_t *, char *, long[2]);
void display_tasks(tasks_t *);
int sort(procs_t **);
void init_stats(cpu_stats_t *);

static const struct timespec td = {
    .tv_nsec = 200000000
};

#endif
