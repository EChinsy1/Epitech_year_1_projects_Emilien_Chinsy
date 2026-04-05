/*
** EPITECH PROJECT, 2025
** is_group
** File description:
** a file that contains a function to get the groups the user is part of
*/

#include "my.h"
#include "macros.h"

static FILE *open_file(char *filepath, char *flags)
{
    FILE *stream = NULL;

    stream = fopen(filepath, flags);
    if (stream == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    return (stream);
}

int one_of_the_groups(list_t *groups, char *line)
{
    list_t *current = groups;
    int return_value = 0;

    while (current && return_value == 0) {
        if (line[0] == '%' && (is_in(line, current->item) == 1 ||
                is_in(line, current->item_space) == 1))
            return_value = 1;
        if (strncmp(line, "%#", 2) == 0 &&
            (is_in(line, current->gid) == 1 ||
                is_in(line, current->gid_space) == 1))
            return_value = 1;
        current = current->next;
    }
    if (is_in(line, "ALL=") == 1 && return_value > 0)
        ++return_value;
    return (return_value);
}

int name_or_uid(char *name, char *uid, char *line, user_t *user)
{
    int return_value = 0;

    if ((is_in(line, name) == 1 || is_in(line, user->name_space) == 1)
        && is_in(line, "ALL=") == 1)
        return_value = 1;
    if (line[0] == '#' && (is_in(line, uid) == 1 ||
            is_in(line, user->uid_space) == 1) && is_in(line, "ALL=") == 1)
        return_value = 1;
    return (return_value);
}

int check_groups(user_t *user, char *name)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread = 0;
    int return_value = 0;
    FILE *stream = open_file("/etc/sudoers", "r");

    nread = getline(&line, &len, stream);
    while (nread != -1 && return_value <= 0) {
        return_value = 0;
        return_value += one_of_the_groups(user->groups, line);
        return_value += name_or_uid(user->name, user->uid, line, user);
        nread = getline(&line, &len, stream);
    }
    free(line);
    fclose(stream);
    return (return_value);
}
