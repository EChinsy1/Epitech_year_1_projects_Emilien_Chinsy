/*
** EPITECH PROJECT, 2026
** my_top
** File description:
** system info display
*/

#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include "mem_struct.h"
#include "my_top.h"
#include "struct_cpu.h"
#include "struct_tasks.h"

long display_uptime(void)
{
    int uptime[4] = {0, 0, 0, 0};
    long total_uptime = 0;

    my_getuptime(uptime);
    total_uptime = uptime[3];
    if (uptime[0] > 0){
        printw("%d day", uptime[0]);
        if (uptime[0] != 1)
            printw("s");
        printw(", ");
    }
    if (uptime[1] > 0)
        printw("%d:%02d, ", uptime[1], uptime[2]);
    else
        printw("%02d min, ", uptime[2]);
    return (total_uptime);
}

void display_tasks(tasks_t *tasks)
{
    if (tasks) {
        mvprintw(1, 0,
            "Tasks: %d total, %d running, %d sleeping, %d stopped, %d zombie"
            , tasks->total, tasks->running, tasks->sleeping,
            tasks->stopped, tasks->zombie);
        free(tasks);
    } else {
        mvprintw(1, 0,
            "Tasks: %d total, %d running, %d sleeping, %d stopped, %d zombie"
            , 0, 0, 0, 0, 0);
    }
}

static void display_cpu(cpu_stats_t *stats)
{
    my_getcpustats(stats);
    if (stats) {
        mvprintw(2, 0, "%%Cpu(s): ");
        printw("%.1f us, %.1f sy, %.1f ni, %.1f id", stats->d_us,
            stats->d_sy, stats->d_ni, stats->d_id);
        printw(", %.1f wa, %.1f hi, %.1f si, %.1f st", stats->d_wa,
            stats->d_hi, stats->d_si, stats->d_st);
    } else {
        mvprintw(2, 0, "%%Cpu(s): ");
        printw("%.1f us, %.1f sy, %.1f ni, %.1f id", 0.0,
            0.0, 0.0, 0.0);
        printw(", %.1f wa, %.1f hi, %.1f si, %.1f st", 0.0,
            0.0, 0.0, 0.0);
    }
}

static void display_users(void)
{
    int users = my_getnumusers();

    if (users > 1)
        printw("%d users, ", users);
    else
        printw("%d user, ", users);
}

static long display_mem_and_swap(int cycle, mem_struct_t *mem)
{
    long ram_size = 0;

    if (mem == NULL)
        memset(mem, 0, 8);
    if (cycle > 0){
        mvprintw(3, 0,
            "MiB Mem : %.1f total, %.1f free, %.1f used, %.1f buff/cache"
            , mem->MemTotal, mem->MemFree, mem->MemUsed, mem->buff_cache);
        mvprintw(4, 0,
            "MiB Swap: %.1f total, %.1f free, %.1f used. %.1f avail Mem",
            mem->SwapTotal, mem->SwapFree, mem->SwapUsed, mem->avail_mem);
    } else {
        mvprintw(3, 0,
            "MiB Mem : %.0f total, %.0f free, %.0f used, %.0f buff/cache"
            , mem->MemTotal, mem->MemFree, mem->MemUsed, mem->buff_cache);
        mvprintw(4, 0,
            "MiB Swap: %.0f total, %.0f free, %.0f used. %.0f avail Mem",
            mem->SwapTotal, mem->SwapFree, mem->SwapUsed, mem->avail_mem);
    }
    return (mem->MemTotal);
}

void display_sys(long val_for_cpu_and_mem_percent[2], int cycle,
    cpu_stats_t *stats)
{
    char *time = my_getsystime();
    double ldavg[3] = {0, 0, 0};
    mem_struct_t *mem = my_getmemvalues(cycle);

    mvprintw(0, 0, "top - %s up ", time);
    free(time);
    val_for_cpu_and_mem_percent[0] = display_uptime();
    display_users();
    my_getloadavg(ldavg, 3);
    printw("load average: %.2f, %.2f, %.2f", ldavg[0], ldavg[1], ldavg[2]);
    display_cpu(stats);
    val_for_cpu_and_mem_percent[1] = display_mem_and_swap(cycle, mem);
    free(mem);
}
