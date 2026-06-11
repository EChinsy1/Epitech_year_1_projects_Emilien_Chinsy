/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** file to handle the job struct
*/

#include <glob.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "jobs.h"
#include "my.h"

void remove_job(job_t **jobs, size_t id)
{
    job_t *temp = *jobs;
    job_t *prev = NULL;

    if (temp != NULL && temp->id == id) {
        *jobs = temp->next;
        free(temp->name);
        free(temp);
        return;
    }
    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL)
        return;
    prev->next = temp->next;
    free(temp->name);
    free(temp);
}

void clear_jobs(job_t *job)
{
    if (!job)
        return;
    clear_jobs(job->next);
    free(job->name);
    free(job);
}

static void remove_elem(char *str, size_t index)
{
    while (str[index] != 0){
        str[index] = str[index + 1];
        index++;
    }
}

static char *clean_line(char *line)
{
    size_t index = 0;

    while (line[0] == ' ')
        remove_elem(line, 0);
    index = strlen(line) - 1;
    while (line[index] == ' '){
        line[index] = 0;
        index--;
    }
    return line;
}

static size_t get_id(job_t *job, size_t largest)
{
    if (!job)
        return largest;
    if (job->id > largest)
        return get_id(job->next, job->id);
    return get_id(job->next, largest);
}

void add_job(pid_t pid, size_t index, char *name,
    job_t **jobs)
{
    size_t id = get_id(*jobs, 0) + 1;
    job_t *new_job = calloc(sizeof(job_t), 1);
    char **name_array = my_backtick_str_to_word_array(name, 2, ';', '&');

    if (!new_job)
        return;
    new_job->id = id;
    new_job->name = clean_line(strdup(name_array[index]));
    new_job->pid = pid;
    setpgid(pid, pid);
    new_job->pgid = getpgid(pid);
    new_job->status = RUNNING;
    new_job->next = *jobs;
    *jobs = new_job;
    free_word_array(name_array);
}

job_t *get_infos_from_pid(pid_t pid, job_t *jobs)
{
    if (!jobs)
        return NULL;
    if (jobs->pid == pid)
        return jobs;
    return get_infos_from_pid(pid, jobs->next);
}
