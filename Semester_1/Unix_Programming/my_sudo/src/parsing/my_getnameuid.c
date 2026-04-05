/*
** EPITECH PROJECT, 2025
** getnameuid
** File description:
** a file to get the user currently running the program
*/

#include "my.h"
#include <stdio.h>
#include <string.h>

int is_right_line(char *line, char *id)
{
    int i = 0;

    while (line[i] != ':')
        ++i;
    ++i;
    while (line[i] != ':')
        ++i;
    ++i;
    if (strncmp(id, &line[i], strlen(id)) == 0)
        return (1);
    return (0);
}

char *return_name(char *line)
{
    char *return_string = NULL;
    int i = 0;

    while (line[i] != ':')
        ++i;
    return_string = calloc(sizeof(char), (i + 1));
    strncat(return_string, line, i);
    return (return_string);
}

char *get_user_with_id(char *id, user_t *user)
{
    FILE *stream = NULL;
    char *line = NULL;
    char *return_string = NULL;
    size_t len = 0;
    ssize_t nread = 0;

    stream = fopen("/etc/passwd", "r");
    if (stream == NULL) {
        return (NULL);
    }
    nread = getline(&line, &len, stream);
    while (nread != -1 && return_string == NULL) {
        if (is_right_line(line, id))
            return_string = (return_name(line));
        nread = getline(&line, &len, stream);
    }
    free(line);
    fclose(stream);
    return (return_string);
}

char *get_id(user_t *user)
{
    int id = getuid();
    char *user_name = NULL;
    char *id_str = my_add_nbr(id);
    char *usable_id_str = calloc(sizeof(char), (strlen(id_str) + 2));

    strcat(usable_id_str, id_str);
    usable_id_str[strlen(id_str)] = ':';
    usable_id_str[strlen(id_str) + 1] = '\0';
    user->uid = strdup(id_str);
    free(id_str);
    user_name = get_user_with_id(usable_id_str, user);
    free(usable_id_str);
    return (user_name);
}
