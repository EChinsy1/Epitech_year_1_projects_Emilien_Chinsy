/*
** EPITECH PROJECT, 2026
** my_top
** File description:
** a file to get the load average
*/

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "my_top.h"

int my_getloadavg(double loadavg[], int nelem)
{
    FILE *stream = 0;
    size_t size = 0;
    char *buffer = NULL;
    char *copy = NULL;

    if (nelem > 3)
        return (0);
    stream = open_file("/proc/loadavg");
    if (stream == NULL)
        return (84);
    getline(&buffer, &size, stream);
    if (buffer == NULL)
        return (84);
    copy = buffer;
    for (int i = 0; i < nelem; ++i)
        loadavg[i] = atof(strsep(&copy, " "));
    end_free(buffer, stream);
    return (0);
}
