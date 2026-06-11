/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** job related builtins
*/

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include "arguments.h"
#include "jobs.h"
#include "my.h"

static char *status_to_str(int status)
{
    for (size_t i = 0; i < NB_OF_STATUSES; i++)
        if (status == STR_STATUSES[i].status)
            return STR_STATUSES[i].str;
    return "Unknown";
}

static void display_jobs(job_t *jobs)
{
    if (!jobs)
        return;
    printf("[%lu]\t%s\t\t%s\n", jobs->id, status_to_str(jobs->status),
        jobs->name);
    display_jobs(jobs->next);
}

static void remove_done_jobs(job_t *curr_job, job_t **head)
{
    if (!curr_job)
        return;
    remove_done_jobs(curr_job->next, head);
    if (curr_job->status == DONE)
        remove_job(head, curr_job->id);
}

int jobs(args_t *args, char **command_array)
{
    update_jobs(&args->jobs);
    display_jobs(args->jobs);
    remove_done_jobs(args->jobs, &args->jobs);
    return 0;
}

static void handle_kills(args_t *args, char *to_kill)
{
    job_t *job = handle_percentage(args->jobs, to_kill);

    if (!job)
        return;
    kill(job->pid, SIGTERM);
    remove_job(&args->jobs, job->id);
}

int kill_job(args_t *args, char **command_array)
{
    int len = array_len(command_array);

    if (len < 2){
        dprintf(2, "kill: Too few arguments.\n");
        return 1;
    }
    for (size_t i = 1; i < len; i++)
        handle_kills(args, command_array[i]);
    return 0;
}

static int handle_bg_proc(job_t *job)
{
    int status = 0;

    signal(SIGTTOU, SIG_IGN);
    tcsetpgrp(STDIN_FILENO, job->pgid);
    kill(-job->pgid, SIGCONT);
    waitpid(-job->pgid, &status, WUNTRACED);
    tcsetpgrp(STDIN_FILENO, getpgid(0));
    signal(SIGTTOU, SIG_DFL);
    return status;
}

int put_to_fg(args_t *args, char **command_array)
{
    job_t *job = NULL;
    int status = 0;

    if (array_len(command_array) != 2)
        return 1;
    job = handle_percentage(args->jobs, command_array[1]);
    if (!job){
        dprintf(2, "No such job.\n");
        return 1;
    }
    if (job->status == DONE){
        printf("%s: job is done\n", job->name);
        remove_job(&args->jobs, job->id);
        return 0;
    }
    status = handle_bg_proc(job);
    remove_job(&args->jobs, job->id);
    return 0;
}

int run_in_bg(args_t *args, char **command_array)
{
    job_t *job = NULL;

    if (array_len(command_array) != 2)
        return 1;
    job = handle_percentage(args->jobs, command_array[1]);
    if (!job){
        dprintf(2, "No such job.\n");
        return 1;
    }
    if (job->status == DONE){
        printf("%s: job is done\n", job->name);
        remove_job(&args->jobs, job->id);
        return 0;
    }
    kill(job->pid, SIGCONT);
    job->status = RUNNING;
    return 0;
}

int stop(args_t *args, char **command_array)
{
    job_t *job = NULL;

    if (array_len(command_array) != 2)
        return 1;
    job = handle_percentage(args->jobs, command_array[1]);
    if (!job){
        dprintf(2, "No such job.\n");
        return 1;
    }
    if (job->status == DONE){
        printf("%s: job is done\n", job->name);
        remove_job(&args->jobs, job->id);
        return 0;
    }
    kill(job->pid, SIGSTOP);
    job->status = STOPPED;
    return 0;
}
