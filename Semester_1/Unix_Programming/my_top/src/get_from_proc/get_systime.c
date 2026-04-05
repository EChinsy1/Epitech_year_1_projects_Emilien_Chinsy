/*
** EPITECH PROJECT, 2026
** my_top
** File description:
** a file to get the systime, it goes through the /proc/driver/rtc file
** and returns the time as a string
*/

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "my_top.h"

void strrev(char *str)
{
    int i = 0;
    int j = 0;
    char c;

    if (!str) {
        return;
    }
    j = strlen(str) - 1;
    while (i < j) {
        c = str[i];
        str[i] = str[j];
        str[j] = c;
        i++;
        j--;
    }
}

char *my_getsystime(void)
{
    FILE *stream = 0;
    size_t size = 0;
    char *buffer = NULL;
    char *result = NULL;

    stream = open_file("/proc/driver/rtc");
    if (stream == NULL)
        return (NULL);
    getline(&buffer, &size, stream);
    buffer[size - 1] = ' ';
    strrev(buffer);
    if (buffer == NULL)
        return (NULL);
    result = strtok(buffer, " ");
    strrev(buffer);
    result[strlen(result) - 1] = '\0';
    fclose(stream);
    return (buffer);
}
