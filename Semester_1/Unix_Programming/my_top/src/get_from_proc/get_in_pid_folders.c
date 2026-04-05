/*
** EPITECH PROJECT, 2026
** gettasks
** File description:
** a file to get the tasks and their status
** I parse through every folder in the /proc/ folder
** and if they are a process, I check the status in:
** /proc/"pid"/status, on the third line
** "sleeping" and "idle" are the same
** and "zombie" is not written in the file
** there is a pid instead.
*/

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "struct_tasks.h"
#include "process_struct.h"
#include "my_top.h"
#include "uid_and_user_struct.h"

static char *get_proc_file(FILE **stream, struct dirent *dir, char *name)
{
    size_t size = 0;
    char *new_path = NULL;
    char *buffer = NULL;

    new_path = calloc(sizeof(char), (6 + 7 + strlen(dir->d_name) + 1));
    strcat(new_path, "/proc/");
    strcat(new_path, dir->d_name);
    strcat(new_path, name);
    *stream = open_file(new_path);
    if (*stream) {
        getline(&buffer, &size, *stream);
    } else {
        buffer = NULL;
    }
    free(new_path);
    return (buffer);
}

static char *get_user_name_from_uid(int uid, uid_n_user_t *users)
{
    uid_n_user_t *current = users;
    char *name_not_found = NULL;

    while (current) {
        if (current->uid == uid)
            return (strdup(current->user));
        current = current->next;
    }
    name_not_found = malloc(sizeof(char) * 15);
    name_not_found = "user_not_found\0";
    return (name_not_found);
}

static procs_t *get_uid_from_status(procs_t **procs,
    procs_t *new_proc, struct dirent *dir, uid_n_user_t *users)
{
    char *buffer = NULL;
    char *copy = NULL;
    char *file_name = calloc(sizeof(char), (6 + 7 + strlen(dir->d_name) + 1));
    FILE *stream = NULL;
    size_t size = 0;

    snprintf(file_name, (6 + strlen(dir->d_name) + 8),
        "/proc/%s/status", dir->d_name);
    stream = open_file(file_name);
    for (int i = 0; i < 9; ++i)
        getline(&buffer, &size, stream);
    copy = (strsep(&buffer, ":"));
    new_proc->uid = atol(strsep(&buffer, " "));
    new_proc->user = get_user_name_from_uid(new_proc->uid, users);
    free(file_name);
    free(copy);
    fclose(stream);
    free(buffer);
    return (new_proc);
}

static procs_t *get_proc_info_from_statm(procs_t **procs,
    procs_t *new_proc, struct dirent *dir)
{
    char *buffer = NULL;
    char *copy = NULL;
    char *file_name = calloc(sizeof(char), (6 + 7 + strlen(dir->d_name) + 1));
    FILE *stream = NULL;
    size_t size = 0;

    snprintf(file_name, (6 + strlen(dir->d_name) + 8),
        "/proc/%s/statm", dir->d_name);
    stream = open_file(file_name);
    getline(&buffer, &size, stream);
    copy = (strsep(&buffer, " "));
    new_proc->shr_mem = atol(strsep(&buffer, " ")) *
        sysconf(_SC_PAGE_SIZE) / 1024;
    new_proc->res_mem = atol(strsep(&buffer, " ")) *
        sysconf(_SC_PAGE_SIZE) / 1024;
    free(file_name);
    free(copy);
    fclose(stream);
    return (new_proc);
}

static procs_t *get_proc_info_from_stat_part_two(char *buffer, procs_t **procs,
    procs_t *new_proc, struct dirent *dir)
{
    char *copy = NULL;

    for (int i = 0; i < 11; ++i)
        copy = (strsep(&buffer, " "));
    new_proc->time = atol(copy);
    copy = (strsep(&buffer, " "));
    new_proc->time += atol(copy);
    for (int i = 0; i < 3; ++i)
        copy = (strsep(&buffer, " "));
    new_proc->priority = atoi(copy);
    copy = (strsep(&buffer, " "));
    new_proc->nice_value = atoi(copy);
    for (int i = 0; i < 3; ++i)
        copy = (strsep(&buffer, " "));
    new_proc->cpu_percent = atol(copy);
    copy = (strsep(&buffer, " "));
    new_proc->virt_mem = atol(copy) / 1024;
    new_proc->next = *procs;
    return (get_proc_info_from_statm(procs, new_proc, dir));
}

static procs_t *get_proc_info_from_stat_part_one(char *real_buffer,
    procs_t **procs, struct dirent *dir, uid_n_user_t *users)
{
    char *buffer = real_buffer;
    char *copy = NULL;
    procs_t *new_proc = malloc(sizeof(procs_t) * 1);

    new_proc->pid = atoi(buffer);
    copy = (strsep(&buffer, " "));
    copy = (strsep(&buffer, ")"));
    new_proc->name = strdup(&copy[1]);
    copy = (strsep(&buffer, " "));
    copy = (strsep(&buffer, " "));
    new_proc->status = copy[0];
    new_proc = get_proc_info_from_stat_part_two(buffer, procs, new_proc, dir);
    return (get_uid_from_status(procs, new_proc, dir, users));
}

static tasks_t *get_task_status(tasks_t *tasks, char *buffer)
{
    size_t size = 0;
    char *copy = buffer;
    char *result = NULL;

    result = (strsep(&copy, " "));
    result = (strsep(&copy, ")"));
    if (copy[1] == 'S' || copy[1] == 'I' || copy[1] == 'D' || copy[1] == ' ') {
        tasks->sleeping = tasks->sleeping + 1;
        return (tasks);
    }
    if (copy[1] == 'R') {
        tasks->running = tasks->running + 1;
        return (tasks);
    }
    if (copy[1] == 't' || copy[1] == 'X') {
        tasks->stopped = tasks->stopped + 1;
        return (tasks);
    }
    tasks->zombie = tasks->zombie + 1;
    return (tasks);
}

static tasks_t *fill_tasks(struct dirent *dir,
    procs_t **proc, uid_n_user_t *users, tasks_t *tasks)
{
    FILE *stream = NULL;
    char *buffer = NULL;
    char *buffer_cpy = NULL;

    buffer = get_proc_file(&stream, dir, "/stat");
    if (buffer != NULL) {
        tasks->total = tasks->total + 1;
        buffer_cpy = strdup(buffer);
        get_task_status(tasks, buffer);
        *proc = get_proc_info_from_stat_part_one(
            buffer_cpy, proc, dir, users);
        free(buffer);
        free(buffer_cpy);
        fclose(stream);
    }
    return (tasks);
}

tasks_t *my_getfrompid(procs_t **procs, uid_n_user_t *users)
{
    DIR *open = opendir("/proc/");
    struct dirent *dir = NULL;
    char *b = NULL;
    tasks_t *tasks = calloc(sizeof(tasks_t), 1);

    if (open == NULL)
        return (NULL);
    dir = readdir(open);
    while (dir != NULL) {
        if (my_str_isnum(dir->d_name) == 1)
            tasks = fill_tasks(dir, procs, users, tasks);
        dir = readdir(open);
    }
    closedir(open);
    return (tasks);
}
