/*
** EPITECH PROJECT, 2025
** get_all_users
** File description:
** a file that will get every user and their uid to avoid having to reopen.
** /etc/passwd every time while parsing.
*/

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uid_and_user_struct.h"

uid_n_user_t *add_user(char *line, uid_n_user_t **users)
{
    uid_n_user_t *new_user = malloc(sizeof(uid_n_user_t) * 1);
    char *copy = NULL;
    char *temp = NULL;

    temp = strdup(strsep(&line, ":"));
    if (strlen(temp) > 8) {
        new_user->user = calloc(sizeof(char), 9);
        strncat(new_user->user, temp, 7);
        strcat(new_user->user, "+");
    } else {
        new_user->user = strdup(temp);
    }
    free(temp);
    copy = strsep(&line, ":");
    new_user->uid = strtol(strsep(&line, ":"), NULL, 10);
    new_user->next = *users;
    *users = new_user;
    return (new_user);
}

uid_n_user_t *get_all_users(void)
{
    FILE *stream = NULL;
    char *line = NULL;
    size_t len = 0;
    ssize_t nread = 0;
    uid_n_user_t *users = NULL;

    stream = fopen("/etc/passwd", "r");
    if (stream == NULL) {
        perror("fopen");
        return (NULL);
    }
    nread = getline(&line, &len, stream);
    while (nread != -1) {
        add_user(line, &users);
        nread = getline(&line, &len, stream);
    }
    free(line);
    fclose(stream);
    return (users);
}
