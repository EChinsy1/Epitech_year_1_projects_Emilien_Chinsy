/*
** EPITECH PROJECT, 2026
** my_top
** File description:
** file containing the function used to kill processes
*/

#include <signal.h>
#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "process_struct.h"
#include "display_info.h"

static int my_str_isnum(char const *str)
{
    int i = 0;

    while (str[i] != '\0'){
        if (str[i] <= 57 && str[i] >= 48){
            i++;
        } else {
            return (0);
        }
    }
    return (1);
}

static procs_t *get_proc_from_scroll(procs_t *proc, int scroll)
{
    if (scroll == 0)
        return proc;
    return get_proc_from_scroll(proc->next, scroll - 1);
}

static void input_error(char *msg)
{
    move(5, 0);
    clrtoeol();
    attron(A_STANDOUT);
    printw("%s", msg);
    attroff(A_STANDOUT);
    refresh();
    sleep(1);
}

static void get_kill_infos(char *storage, int pid_to_display, char *msg)
{
    move(5, 0);
    clrtoeol();
    attron(A_BOLD);
    printw(msg, pid_to_display);
    attroff(A_BOLD);
    echo();
    curs_set(1);
    getstr(storage);
    noecho();
    curs_set(0);
}

static int pid_part(int default_pid)
{
    char pid_to_kill[20] = {0};

    get_kill_infos(pid_to_kill, default_pid,
        "PID to signal/kill [default pid = %d] ");
    if (my_str_isnum(pid_to_kill) == 0){
        input_error("Unacceptable integer ");
        return -1;
    }
    if (strlen(pid_to_kill) == 0)
        return default_pid;
    return atoi(pid_to_kill);
}

static int signal_part(int pid_to_kill)
{
    char sig_to_send[5] = {0};

    if (pid_to_kill == -1)
        return -1;
    get_kill_infos(sig_to_send, pid_to_kill,
        "Send pid %d signal [15/sigterm] ");
    if (my_str_isnum(sig_to_send) == 0){
        input_error("Invalid signal");
        return -1;
    }
    if (strlen(sig_to_send) == 0)
        return SIGTERM;
    return atoi(sig_to_send);
}

void kill_proc(procs_t *list, display_info_t *display_info)
{
    procs_t *default_proc = get_proc_from_scroll(list, display_info->scroll);
    int pid = pid_part(default_proc->pid);
    int signal = signal_part(pid);

    if (signal == -1)
        return;
    kill(pid, signal);
}
