/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** Parsing file
*/

#include <stdlib.h>
#include <stdio.h>
#include "corewar.h"
#include "my.h"

static args_t init_args(void)
{
    args_t args;

    args.nb_flags = 0;
    args.nb_files = 0;
    args.nbr_cycle = -1;
    args.files = NULL;
    return args;
}

static int find_nearest_file(char **av, int i)
{
    for (; av[i]; ++i)
        if (my_strstr(av[i], ".cor"))
            return i;
    return FAIL;
}

static int find_file(args_t *args, char *filename)
{
    for (int i = 0; i < args->nb_files; ++i)
        if (my_strcmp(args->files[i].prog_name, filename) == SUCCESS)
            return i;
    return FAIL;
}

static void dump_fct(char **av, args_t *args, int i)
{
    char *endptr = NULL;

    if (av[i + 1])
        args->nbr_cycle = my_strtoi(av[i + 1], &endptr);
    if (endptr && endptr[0] != '\0') {
        my_puterr("-dump: Wrong argument.\n");
        args->nbr_cycle = FLAG_FAIL;
    } else if (args->nbr_cycle < 0) {
        my_puterr("-dump: Invalid value.\n");
        args->nbr_cycle = FLAG_FAIL;
    }
    if (endptr)
        free(endptr);
}

static void prog_number_fct(char **av, args_t *args, int i)
{
    int file_idx = find_nearest_file(av, i);
    int idx = 0;
    char *endptr = NULL;

    if (file_idx < 0)
        return;
    idx = find_file(args, av[file_idx]);
    if (idx < 0)
        return;
    if (args->files[idx].prog_name && av[i + 1])
        args->files[idx].prog_nb = my_strtoi(av[i + 1], &endptr);
    if ((endptr && endptr[0] != '\0') || args->files[idx].prog_nb < 0)
        args->files[idx].prog_nb = FLAG_FAIL;
    if (endptr)
        free(endptr);
}

static void load_address_fct(char **av, args_t *args, int i)
{
    int file_idx = find_nearest_file(av, i);
    int idx = 0;
    char *endptr = NULL;

    if (file_idx < 0)
        return;
    idx = find_file(args, av[file_idx]);
    if (idx < 0)
        return;
    if (args->files[idx].prog_name && av[i + 1])
        args->files[idx].load_address = my_strtoi(av[i + 1], &endptr);
    if ((endptr && endptr[0] != '\0') || args->files[idx].load_address < 0)
        args->files[idx].load_address = FLAG_FAIL;
    if (endptr)
        free(endptr);
}

const flags_t flags[] = {
    {"dump", &dump_fct},
    {"n", &prog_number_fct},
    {"a", &load_address_fct},
    {NULL, NULL}
};
static void fill_flags(char **av, args_t *args, int i)
{
    for (int j = 0; flags[j].flag; ++j)
        if (my_strcmp(flags[j].flag, av[i] + 1) == SUCCESS) {
            flags[j].fct(av, args, i);
            ++args->nb_flags;
            return;
        }
    my_puterr(av[i]);
    my_puterr(": Unknown option.\n");
}

static void add_files(char **av, args_t *args, int i)
{
    args->files = realloc(args->files, sizeof(files_t) * (args->nb_files + 1));
    if (!args->files)
        return;
    args->files[args->nb_files].prog_name = my_strdup(av[i]);
    if (!args->files[args->nb_files].prog_name)
        return;
    args->files[args->nb_files].prog_nb = -1;
    args->files[args->nb_files].load_address = -1;
    ++args->nb_files;
}

args_t arguments(char **av)
{
    args_t args = init_args();

    for (int i = 1; av[i]; ++i)
        if (my_strstr(av[i], ".cor"))
            add_files(av, &args, i);
    for (int i = 1; av[i]; ++i)
        if (av[i][0] == '-') {
            fill_flags(av, &args, i);
            continue;
        }
    return args;
}
