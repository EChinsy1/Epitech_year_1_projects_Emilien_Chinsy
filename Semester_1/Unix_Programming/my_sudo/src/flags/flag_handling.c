/*
** EPITECH PROJECT, 2025
** flag_handling
** File description:
** a file to handle the flags
*/

#include <grp.h>
#include <errno.h>
#include "my.h"
#include "macros.h"

int size_of_list_t(list_t *list)
{
    list_t *current = list;
    int size = 0;

    if (current == NULL) {
        return (0);
    }
    while (current) {
        ++size;
        current = current->next;
    }
    return (size);
}

static char *get_only_id(char *line)
{
    int i = 0;
    int j = 0;
    char *result = NULL;

    while (line[i] != ':')
        ++i;
    ++i;
    while (line[i] != ':')
        ++i;
    ++i;
    j = i;
    while (line[j] != ':')
        ++j;
    result = calloc(sizeof(char), (j - i) + 1);
    if (result == NULL)
        return (NULL);
    strncat(result, &line[i], (j - i));
    return (result);
}

static char *get_id_from_file(char *name, char *filepath)
{
    FILE *stream = NULL;
    char *line = NULL;
    char *return_string = NULL;
    size_t len = 0;
    ssize_t nread = 0;

    stream = fopen(filepath, "r");
    if (stream == NULL)
        return (NULL);
    nread = getline(&line, &len, stream);
    while (nread != -1 && return_string == NULL) {
        if (strstr(line, name) != NULL)
            return_string = (get_only_id(line));
        nread = getline(&line, &len, stream);
    }
    free(line);
    fclose(stream);
    return (return_string);
}

static int make_id(char *name, char *filepath)
{
    int user_id = -1;
    char *usable_name = NULL;
    char *id_from_file = NULL;

    if (name[0] == '#')
        return (atoi(&name[1]));
    usable_name = calloc(sizeof(char), (strlen(name) + 2));
    if (usable_name == NULL)
        return (ERROR);
    strcat(usable_name, name);
    usable_name[strlen(name)] = ':';
    usable_name[strlen(name) + 1] = '\0';
    id_from_file = get_id_from_file(usable_name, filepath);
    if (id_from_file != NULL)
        user_id = atoi(id_from_file);
    free(usable_name);
    free(id_from_file);
    return (user_id);
}

static fnf_t *make_flag(char flag, fnf_t **flags, char *arg)
{
    int i = 0;
    fnf_t *item = malloc(sizeof(fnf_t) * 1);

    if (item == NULL)
        return (NULL);
    while (FLAGSNFUNCS[i].flag) {
        if (FLAGSNFUNCS[i].flag == flag) {
            item->flag = flag;
            item->arg = arg;
            item->fptr = FLAGSNFUNCS[i].fptr;
            return (item);
        }
        ++i;
    }
    free(item);
    free_flags(flags);
    exit(print_help(EXIT_ERROR));
}

static int get_num_of_flags(char **argv)
{
    int i = 1;
    int num = 0;

    while (argv[i] != NULL && argv[i][0] == '-') {
        ++num;
        i = i + 2;
    }
    return (num);
}

fnf_t **parse(int argc, char **argv)
{
    int i = 1;
    int j = 0;
    fnf_t **flags = NULL;
    int num = get_num_of_flags(argv);

    if (argv[i][0] != '-')
        return (NULL);
    flags = calloc(sizeof(fnf_t *), (num + 1));
    if (flags == NULL)
        return (NULL);
    while (i < (1 + 2 * num) && argv[i] != NULL && argv[i][0] == '-') {
        if (argv[i][1] != 'u') {
            flags[j] = make_flag(argv[i][1], flags, argv[i + 1]);
            ++j;
        } else
            flags[num - 1] = make_flag(argv[i][1], flags, argv[i + 1]);
        i = i + 2;
    }
    flags[num] = NULL;
    return (flags);
}

int get_group_id(char *name, int num_of_flags)
{
    int id = make_id(name, "/etc/group");

    if (setgid(id) == -1) {
        fprintf(stderr, "my_sudo: unknown group %s\n", name);
        return (ERROR);
    }
    return (id);
}

static void set_and_free_both(int size, list_t *groups, unsigned int *groupsint)
{
    setgroups(size, groupsint);
    free_list(groups);
    free(groupsint);
}

int get_user_id(char *name, int num_of_flags)
{
    int id = make_id(name, "/etc/passwd");
    list_t *groups = get_all_groups(name);
    list_t *current = groups;
    int size = size_of_list_t(groups);
    unsigned int *groups_int = malloc(sizeof(int) * size + 1);

    if (groups_int == NULL)
        return (ERROR);
    for (int i = 0; i < size; ++i) {
        groups_int[i] = atoi(current->gid);
        current = current->next;
    }
    if (num_of_flags == 1)
        setgid(make_id(name, "/etc/group"));
    set_and_free_both(size, groups, groups_int);
    if (setuid(id) == -1) {
        fprintf(stderr, "my_sudo: unknown user %s\n", name);
        return (ERROR);
    }
    return (id);
}
