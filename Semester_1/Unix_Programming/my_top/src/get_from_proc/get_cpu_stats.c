/*
** EPITECH PROJECT, 2026
** my_top
** File description:
** a file to get the num of users
*/

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "struct_cpu.h"
#include "my_top.h"

void init_stats(cpu_stats_t *stats)
{
    stats->us = 0;
    stats->ni = 0;
    stats->sy = 0;
    stats->id = 0;
    stats->wa = 0;
    stats->hi = 0;
    stats->si = 0;
    stats->st = 0;
}

static void adjust_cpu_stats(cpu_stats_t *stats,
    cpu_stats_t *new_stats, int total)
{
    stats->d_us = ((new_stats->us - stats->us) / total) * 100;
    stats->d_ni = ((new_stats->ni - stats->ni) / total) * 100;
    stats->d_sy = ((new_stats->sy - stats->sy) / total) * 100;
    stats->d_id = ((new_stats->id - stats->id) / total) * 100;
    stats->d_wa = ((new_stats->wa - stats->wa) / total) * 100;
    stats->d_hi = ((new_stats->hi - stats->hi) / total) * 100;
    stats->d_si = ((new_stats->si - stats->si) / total) * 100;
    stats->d_st = ((new_stats->st - stats->st) / total) * 100;
    stats->us = new_stats->us;
    stats->ni = new_stats->ni;
    stats->sy = new_stats->sy;
    stats->id = new_stats->id;
    stats->wa = new_stats->wa;
    stats->hi = new_stats->hi;
    stats->si = new_stats->si;
    stats->st = new_stats->st;
}

static void delta_stats(cpu_stats_t *stats, char *buffer)
{
    char *nothing = (strsep(&buffer, " "));
    int total = 0;
    cpu_stats_t *new_stats = malloc(sizeof(cpu_stats_t));

    nothing = (strsep(&buffer, " "));
    total = stats->us + stats->ni + stats->sy + stats->id +
        stats->wa + stats->hi + stats->si + stats->st;
    new_stats->us = atof(strsep(&buffer, " "));
    new_stats->ni = atof(strsep(&buffer, " "));
    new_stats->sy = atof(strsep(&buffer, " "));
    new_stats->id = atof(strsep(&buffer, " "));
    new_stats->wa = atof(strsep(&buffer, " "));
    new_stats->hi = atof(strsep(&buffer, " "));
    new_stats->si = atof(strsep(&buffer, " "));
    new_stats->st = atof(strsep(&buffer, " "));
    total = (new_stats->us + new_stats->ni + new_stats->sy + new_stats->id +
        new_stats->wa + new_stats->hi + new_stats->si + new_stats->st) - total;
    adjust_cpu_stats(stats, new_stats, total);
    free(new_stats);
}

void my_getcpustats(cpu_stats_t *stats)
{
    int fd = open("/proc/stat", O_RDONLY, 0);
    char *buffer = NULL;
    char buff[64 * 1024 - 1];

    if (stats == NULL || fd < 0)
        return;
    read(fd, buff, 64 * 1024 - 1);
    buffer = strstr(buff, "cpu ");
    delta_stats(stats, buffer);
    close(fd);
}
