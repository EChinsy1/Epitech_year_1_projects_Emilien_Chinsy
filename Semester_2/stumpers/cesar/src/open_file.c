/*
** EPITECH PROJECT, 2026
** open
** File description:
** open
*/

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include "macro.h"

char *open_file(const char *filename)
{
    int fd = 0;
    char *buffer = NULL;
    struct stat sb = {0};

    if (filename == NULL)
        return NULL;
    fd = open(filename, O_RDONLY);
    if (fd <= ERROR)
        return NULL;
    stat(filename, &sb);
    buffer = calloc(sizeof(char), sb.st_size + 1);
    if (buffer == NULL)
        return NULL;
    read(fd, buffer, sb.st_size);
    close(fd);
    return buffer;
}
