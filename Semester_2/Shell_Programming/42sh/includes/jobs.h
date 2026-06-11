/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** job control structs
*/

#ifndef JOBS_H_
    #define JOBS_H_

    #include <time.h>
    #include "tree.h"

    #define NB_OF_STATUSES 5
    #define NB_OF_HANDLERS 4

typedef enum {
    DEFAULT,
    INDEX,
    SHORTCUT,
    CONTAINS,
    STARTS,
} arg_types_t;

typedef enum {
    RUNNING,
    STOPPED,
    SUSPENDED,
    TERMINATED,
    DONE
} statuses_t;

typedef struct {
    statuses_t status;
    char *str;
} status_str_t;

typedef struct job_s {
    pid_t pid;
    pid_t pgid;
    char *name;
    size_t status;
    size_t id;
    struct job_s *next;
} job_t;

typedef struct {
    arg_types_t type;
    job_t *(*fptr)(job_t *jobs, char *string);
} percentage_handlers_t;

size_t find_separator(char *command, size_t index);
void add_job(pid_t pid, size_t index, char *name,
    job_t **jobs);
void remove_job(job_t **jobs, size_t id);
job_t *handle_percentage(job_t *jobs, char *string);
job_t *get_infos_from_pid(pid_t pid, job_t *jobs);
job_t *handle_index(job_t *jobs, char *string);
job_t *handle_default(job_t *jobs, char *string);
job_t *handle_starts(job_t *jobs, char *string);
job_t *handle_contains(job_t *jobs, char *string);
void update_jobs(job_t **jobs);
size_t get_job_status(pid_t pid, int status);
void clear_jobs(job_t *job);

static const status_str_t STR_STATUSES[5] = {
    {RUNNING, "Running"},
    {STOPPED, "Stopped"},
    {SUSPENDED, "Suspended"},
    {TERMINATED, "Terminated"},
    {DONE, "Done"},
};

static const percentage_handlers_t PERCENTAGE_HANDLERS[4] = {
    {DEFAULT, &handle_default},
    {INDEX, &handle_index},
    {STARTS, &handle_starts},
    {CONTAINS, &handle_contains}
};

#endif
