/*
** EPITECH PROJECT, 2026
** my_top
** File description:
** process info display
*/

#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "process_struct.h"
#include "display_info.h"

static int int_len(int nbr)
{
    int local_nbr = nbr;
    int len = 0;

    if (nbr == 0)
        return (1);
    else if (local_nbr < 0) {
        ++len;
        local_nbr = local_nbr * -1;
    }
    while (local_nbr > 0){
        local_nbr /= 10;
        len++;
    }
    return len;
}

static void make_time_str(procs_t *procs, int y)
{
    int cent = procs->time % 100;
    int min = ((procs->time) / 100) / 60;
    int sec = ((procs->time - min) / 100) % 60;
    char *placeholder = malloc(sizeof(char) *
        (int_len(cent) + 2 + 2 + 3));

    snprintf(placeholder, (int_len(cent) + 2 + 2 + 3),
        "%d:%.2d.%.2d", min, sec, cent);
    mvprintw(y, 64, "%s", placeholder);
    free(placeholder);
}

static void print_memory(long value, int x, int y, display_info_t *display_info)
{
    int len = int_len(value);
    float converted_usage = 0;

    if (len > 7 && display_info->proc_unit < 3){
        converted_usage = (float)value / pow(1024, 2);
        mvprintw(y, x - (int_len((int)converted_usage) + 3)
            , "%.1fg", converted_usage);
        return;
    } else if (display_info->proc_unit == 0) {
        mvprintw(y, x - int_len(value), "%ld", value);
        return;
    }
    converted_usage = (float)value / pow(1024, display_info->proc_unit);
    mvprintw(y, x - (int_len((int)converted_usage) + 3)
        , "%.1f%c", converted_usage, NOTATION[display_info->proc_unit]);
}

void print_proc_info(procs_t *procs, int y, display_info_t *display_info,
    long ram_size_n_uptime[2])
{
    if (procs->status == 'R')
        attron(A_BOLD);
    mvprintw(y, 7 - int_len(procs->pid), "%d", procs->pid);
    mvprintw(y, 8, "%s", procs->user);
    mvprintw(y, 20 - int_len(procs->priority), "%d", procs->priority);
    mvprintw(y, 24 - int_len(procs->nice_value), "%d", procs->nice_value);
    print_memory(procs->virt_mem, 32, y, display_info);
    print_memory(procs->shr_mem, 39, y, display_info);
    print_memory(procs->res_mem, 46, y, display_info);
    mvprintw(y, 47, "%c", procs->status);
    mvprintw(y, 52, "%.1f", (
            100 * ((double)procs->time / sysconf(_SC_CLK_TCK)) /
            (ram_size_n_uptime[0] -
                (procs->cpu_percent / sysconf(_SC_CLK_TCK)))));
    mvprintw(y, 58, "%.1f", ((double)procs->shr_mem /
            (ram_size_n_uptime[1] * 10)));
    make_time_str(procs, y);
    mvprintw(y, 72, "%s", procs->name);
    attroff(A_BOLD);
}

void display_procs(procs_t *procs, display_info_t *display_info,
    char *user_sort, long ram_size_n_uptime[2])
{
    int max_y = getmaxy(stdscr) - 1;
    int offset = 0;

    if ((display_info->scroll > 0 && procs != NULL) ||
        (user_sort != NULL && procs != NULL &&
            strcmp(user_sort, procs->user) != 0)){
        offset = ((user_sort != NULL &&
                strcmp(user_sort, procs->user) == 0) || !user_sort);
        display_info->scroll -= offset;
        display_procs(procs->next, display_info, user_sort, ram_size_n_uptime);
        display_info->scroll += offset;
    } else if (display_info->curr_y <= max_y && procs != NULL){
        print_proc_info(procs, display_info->curr_y, display_info,
            ram_size_n_uptime);
        move(display_info->curr_y + 1, 0);
        display_info->curr_y += 1;
        display_procs(procs->next, display_info, user_sort, ram_size_n_uptime);
    }
}
