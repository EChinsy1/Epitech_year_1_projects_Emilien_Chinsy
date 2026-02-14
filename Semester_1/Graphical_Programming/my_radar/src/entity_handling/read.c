/*
** EPITECH PROJECT, 2025
** text.c
** File description:
** file containing sprites stuff
*/

#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include "my.h"
#include "struct.h"
#include "macros.h"

static char *error_and_return(char *message, int len)
{
    write(2, message, len);
    return (NULL);
}

char *get_string_line(char *buffer, int *start)
{
    int i = *start;
    char *line;

    while (buffer[*start] != '\n' && buffer[*start] != '\0') {
        *start = *start + 1;
    }
    line = my_calloc(sizeof(char), ((*start - i) + 2));
    my_strncat(line, &buffer[i], (*start - i));
    *start = *start + 1;
    return (line);
}

char *read_full_file(char const *filepath, int *size)
{
    char *buffer;
    struct stat sb;
    int fd = open(filepath, O_RDONLY);

    if (fd == -1)
        return (error_and_return("File not found\n", 15));
    if (stat(filepath, &sb) != -1) {
        if ((sb.st_mode & S_IFMT) != S_IFREG) {
            write(2, "The inputed file is not a text file\n", 36);
            return (NULL);
        }
        *size = sb.st_size;
        buffer = my_calloc(sizeof(char), (*size + 1));
        read(fd, buffer, *size);
        buffer[*size] = '\0';
    }
    if (buffer[0] == '\0')
        write(2, "The inputed file is empty\n", 26);
    return (buffer);
}
