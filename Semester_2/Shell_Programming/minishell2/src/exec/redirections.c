/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** redirections
*/


#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "my.h"

int redirection_s(char *file)
{
    int fd = open(file, O_RDONLY);

    if (fd < 0 || access(file, R_OK) != 0) {
        my_putstr(2, file);
        my_putstr(2, ": ");
        my_putstr(2, strerror(errno));
        my_putstr(2, "\n");
        return (1);
    }
    dup2(fd, STDIN_FILENO);
    close(fd);
    return (0);
}

int redirection_ss_part_2(char *buffer, int fd, char *result)
{
    free(buffer);
    write(fd, result, my_strlen(result));
    close(fd);
    fd = open("temp_for_smallsmall", (O_RDONLY));
    free(result);
    dup2(fd, STDIN_FILENO);
    close(fd);
    return (0);
}

int redirection_ss(char *end)
{
    int getline_return = 0;
    int fd = open("temp_for_smallsmall", (O_WRONLY | O_CREAT | O_TRUNC), 0644);
    char *buffer = NULL;
    char *result = my_calloc(sizeof(char), 1000);
    size_t size = 0;

    if (fd < 0 || access("temp_for_smallsmall", R_OK) != 0)
        return (-1);
    while (getline_return >= 0) {
        my_putstr(STDIN_FILENO, "?>");
        getline_return = getline(&buffer, &size, stdin);
        if (my_strncmp(end, buffer, my_strlen(end) - 1) == 0)
            getline_return = -1000;
        else
            my_strcat(result, buffer);
    }
    return (redirection_ss_part_2(buffer, fd, result));
}

int redirection_b(char *file)
{
    int fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd < 0 || access(file, R_OK) != 0) {
        my_putstr(2, file);
        my_putstr(2, ": ");
        my_putstr(2, strerror(errno));
        my_putstr(2, "\n");
        return (1);
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);
    return (0);
}

int redirection_bb(char *file)
{
    int fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);

    if (fd < 0 || access(file, R_OK) != 0) {
        my_putstr(2, file);
        my_putstr(2, ": ");
        my_putstr(2, strerror(errno));
        my_putstr(2, "\n");
        return (1);
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);
    return (0);
}
