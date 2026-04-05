/*
** EPITECH PROJECT, 2026
** my_top
** File description:
** tui refresh functions
*/

#include <ncurses.h>
#include <stdlib.h>
#include "my_top.h"
#include "key_functions.h"
#include "display_info.h"

static void display_bar(void)
{
    attron(A_STANDOUT);
    mvprintw(6, 0, "    PID USER      PR  NI    VIRT    RES    SHR S");
    printw("   %%CPU  %%MEM     TIME+ COMMAND");
    for (int i = getcurx(stdscr); i < getmaxx(stdscr); i++)
        printw(" ");
    attroff(A_STANDOUT);
}

static void key_functions(int input, procs_t *list,
    display_info_t *display_info)
{
    int index = 0;

    while (index < AMT_OF_KEYBINDS){
        if (KEY_FUNCS[index].keybind == input){
            KEY_FUNCS[index].function(list, display_info);
            return;
        }
        index++;
    }
    return;
}

static int list_len(procs_t *procs)
{
    if (procs != NULL)
        return 1 + list_len(procs->next);
    return 0;
}

static void display_all(tasks_t *tasks, procs_t **procs,
    display_info_t *display_info, cpu_stats_t *stats)
{
    long val_for_cpu_and_mem_percent[2] = {0, 0};

    sort(procs);
    display_sys(val_for_cpu_and_mem_percent, display_info->sys_unit, stats);
    display_tasks(tasks);
    display_bar();
    display_info->curr_y = 7;
    move(7, 0);
    display_procs(*procs, display_info,
        display_info->user_sort, val_for_cpu_and_mem_percent);
}

static display_info_t *init_display_info(char *user_sort)
{
    display_info_t *display_info = malloc(sizeof(display_info_t));

    display_info->scroll = 0;
    display_info->proc_unit = 0;
    display_info->sys_unit = 1;
    display_info->curr_y = 0;
    display_info->user_sort = user_sort;
    return display_info;
}

void screen_loop(int max_frames, uid_n_user_t *users, char *user_sort,
    cpu_stats_t *stats)
{
    int gotten = 0;
    procs_t *procs = NULL;
    tasks_t *tasks = NULL;
    display_info_t *display_info = init_display_info(user_sort);

    while (1){
        erase();
        tasks = my_getfrompid(&procs, users);
        if (display_info->scroll >= list_len(procs))
            display_info->scroll = list_len(procs) - 1;
        display_all(tasks, &procs, display_info, stats);
        max_frames--;
        gotten = getch();
        key_functions(gotten, procs, display_info);
        free_procs(procs);
        procs = NULL;
        if (gotten == 'q' || max_frames == 0)
            break;
    }
    free(display_info);
}
