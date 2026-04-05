/*
** EPITECH PROJECT, 2026
** my_top
** File description:
** a file to get the uptime
*/

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "my_top.h"

int end_free(char *buffer, FILE *stream)
{
    free(buffer);
    fclose(stream);
    return (0);
}

int my_getuptime(int uptime[])
{
    FILE *file = 0;
    size_t size = 0;
    char *buffer = NULL;
    char *copy = NULL;

    file = open_file("/proc/uptime");
    if (file == NULL)
        return (84);
    getline(&buffer, &size, file);
    if (buffer == NULL)
        return (84);
    copy = buffer;
    uptime[3] = atof(strsep(&copy, " "));
    uptime[1] = uptime[3] / 3600 - ((int)uptime[1] / 24 * 24);
    uptime[2] = (uptime[3] - (int)uptime[1] * 3600) / 60;
    uptime[0] = uptime[1] / 24;
    uptime[1] -= uptime[0] * 24;
    end_free(buffer, file);
    return (0);
}
