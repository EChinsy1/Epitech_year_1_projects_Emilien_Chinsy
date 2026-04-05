/*
** EPITECH PROJECT, 2025
** is_group
** File description:
** a file that contains a function to get the groups the user is part of
*/

#include "my.h"
#include "macros.h"

static char *get_groups_id(char *line, int i, char final_char)
{
    char *gid = NULL;
    int j = 0;
    int len = 0;

    ++i;
    while (line[i] != ':')
        ++i;
    ++i;
    j = i;
    while (line[j] != ':')
        ++j;
    len = j - i;
    gid = calloc(sizeof(char), len + 2);
    if (gid == NULL)
        return (NULL);
    strncat(gid, &line[i], len);
    gid[len] = '\t';
    return (gid);
}

char *get_group_name(char *line, list_t **groups)
{
    list_t *new_group = calloc(sizeof(list_t), 1);
    char *return_value = NULL;
    int len = 0;

    if (!new_group)
        return (NULL);
    while (line[len] != ':')
        ++len;
    return_value = calloc(sizeof(char), len + 2);
    strncat(return_value, line, len);
    return_value[len] = '\t';
    new_group->item = strdup(return_value);
    return_value[len] = ' ';
    new_group->item_space = strdup(return_value);
    new_group->gid = get_groups_id(line, len, '\t');
    new_group->gid_space = get_groups_id(line, len, ' ');
    new_group->next = *groups;
    *groups = new_group;
    free(return_value);
    return ("");
}

int is_in(char *line, char *to_check)
{
    if (line == NULL || to_check == NULL)
        return (0);
    if (strstr(line, to_check) != NULL) {
        return (1);
    }
    return (0);
}

void print_list(list_t *list)
{
    list_t *current = list;

    while (current){
        current = current->next;
    }
}

list_t *get_all_groups(char *name)
{
    FILE *stream = NULL;
    char *line = NULL;
    size_t len = 0;
    ssize_t nread = 0;
    list_t *groups = NULL;

    stream = fopen("/etc/group", "r");
    if (stream == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    nread = getline(&line, &len, stream);
    while (nread != -1) {
        if (is_in(line, name) == 1)
            get_group_name(line, &groups);
        nread = getline(&line, &len, stream);
    }
    free(line);
    fclose(stream);
    return (groups);
}
