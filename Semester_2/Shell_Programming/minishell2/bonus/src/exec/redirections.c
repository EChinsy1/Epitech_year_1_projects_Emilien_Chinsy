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

static int copy_redirection(char *call, int fd)
{
    return (dup2(fd, STDERR_FILENO));
}

static int free_n_close(char *buffer, int fd, char *call, int i)
{
    close(fd);
    if (my_strcmp(call, "<<") == 0) {
        return (0);
    }
    my_putstr(2, &call[i]);
    my_putstr(2, ": No such file or directory\n");
    if (buffer)
        free(buffer);
    return (-1);
}

int redirection_s(char *file, char *call)
{
    int fd = open(file, O_RDONLY);

    if (call[1] != '\0') {
        return (free_n_close(NULL, fd, call, 2));
    }
    if (call[2] != '\0') {
        my_putstr(2, &call[2]);
        my_putstr(2, ": No such file or directory\n");
        return (-1);
    }
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

static int redirection_ss_part_2(char *buffer, int fd, char *result, char *call)
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

int redirection_ss(char *end, char *call)
{
    int getline_return = 0;
    int fd = open("temp_for_smallsmall", (O_WRONLY | O_CREAT | O_TRUNC), 0644);
    char *buffer = NULL;
    char *result = my_calloc(sizeof(char), 1000);
    size_t size = 0;

    if (fd < 0 || access("temp_for_smallsmall", R_OK) != 0)
        return (-1);
    while (getline_return >= 0) {
        my_putstr(STDIN_FILENO, "?> ");
        getline_return = getline(&buffer, &size, stdin);
        if (my_strncmp(end, buffer, my_strlen(end) - 1) == 0)
            getline_return = -1000;
        else
            my_strcat(result, buffer);
    }
    return (redirection_ss_part_2(buffer, fd, result, call));
}

int redirection_b(char *file, char *call)
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
    for (int i = 0; call[i]; ++i) {
        if (call[i] == '&')
            copy_redirection(call, fd);
    }
    close(fd);
    return (0);
}

int redirection_b_n_err(char *file, char *call)
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
    dup2(fd, STDERR_FILENO);
    close(fd);
    return (0);
}

int redirection_bb(char *file, char *call)
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
    for (int i = 0; call[i]; ++i) {
        if (call[i] == '&')
            copy_redirection(call, fd);
    }
    close(fd);
    return (0);
}
