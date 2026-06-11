/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** functions to return the right job
*/

#include <stdlib.h>
#include <string.h>
#include "arguments.h"
#include "jobs.h"

static int get_arg_type(char *arg)
{
    char *endptr = NULL;

    if (arg[0] != '%')
        return -1;
    if (strlen(arg) == 1)
        return DEFAULT;
    strtol(arg + 1, &endptr, 10);
    if (*endptr == 0)
        return INDEX;
    if (strlen(arg) == 2)
        return SHORTCUT;
    if (arg[1] == '.')
        return CONTAINS;
    return STARTS;
}

static job_t *return_job(job_t *jobs, int arg_type, char *string)
{
    for (size_t i = 0; i < NB_OF_HANDLERS; i++)
        if (arg_type == PERCENTAGE_HANDLERS[i].type)
            return PERCENTAGE_HANDLERS[i].fptr(jobs, string);
    return NULL;
}

job_t *handle_percentage(job_t *jobs, char *string)
{
    int arg_type = get_arg_type(string);

    if (arg_type < 0)
        return NULL;
    return return_job(jobs, arg_type, string + 1);
}
