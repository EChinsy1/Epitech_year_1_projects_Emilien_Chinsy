/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** functions to update job status
*/

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include "arguments.h"
#include "jobs.h"
#include "my.h"

size_t get_job_status(pid_t pid, int status)
{
    int new_status = 0;
    pid_t return_pid = waitpid(pid, &new_status,
        WNOHANG | WUNTRACED | WCONTINUED);

    if (!WIFEXITED(new_status) && !WIFSTOPPED(new_status))
        return RUNNING;
    if (WIFSTOPPED(new_status))
        return STOPPED;
    if (pid == return_pid)
        return DONE;
    return status;
}

static void update_statuses(job_t *jobs)
{
    size_t status = 0;

    if (!jobs)
        return;
    status = get_job_status(jobs->pid, jobs->status);
    if (status != jobs->status)
        jobs->status = status;
    update_statuses(jobs->next);
}

void update_jobs(job_t **jobs)
{
    job_t *curr_job = *jobs;
    size_t id_storage = 0;

    update_statuses(*jobs);
    while (curr_job){
        if (curr_job->status == DONE){
            printf("[%lu]\t%s\tDone\n", curr_job->id, curr_job->name);
            id_storage = curr_job->id;
            curr_job = curr_job->next;
            remove_job(jobs, id_storage);
        } else
            curr_job = curr_job->next;
    }
}
