/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** functions to handle job args
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jobs.h"

static job_t *get_job_from_elem(job_t *jobs, char *elem)
{
    if (!jobs)
        return NULL;
    if (*strstr(jobs->name, elem) != 0)
        return jobs;
    return get_job_from_elem(jobs->next, elem);
}

static job_t *get_job_from_start(job_t *jobs, char *prefix)
{
    if (!jobs)
        return NULL;
    if (strncmp(jobs->name, prefix, strlen(prefix)) == 0)
        return jobs;
    return get_job_from_start(jobs->next, prefix);
}

static job_t *get_job_from_index(job_t *jobs, size_t index)
{
    if (!jobs)
        return NULL;
    if (jobs->id == index)
        return jobs;
    return get_job_from_index(jobs->next, index);
}

job_t *handle_contains(job_t *jobs, char *string)
{
    job_t *job = get_job_from_elem(jobs, string + 1);

    return job;
}

job_t *handle_starts(job_t *jobs, char *string)
{
    job_t *job = get_job_from_start(jobs, string);

    return job;
}

job_t *handle_default(job_t *jobs, char *string)
{
    return jobs;
}

job_t *handle_index(job_t *jobs, char *string)
{
    char *endptr = NULL;
    long nb = 0;

    nb = strtol(string, &endptr, 10);
    if (nb < 0)
        return NULL;
    return get_job_from_index(jobs, nb);
}
