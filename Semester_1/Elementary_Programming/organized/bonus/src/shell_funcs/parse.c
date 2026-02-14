/*
** EPITECH PROJECT, 2025
** parse
** File description:
** this is a file that will allow you to parse files under a specific format,
** and fill up the linked_list with items from that file.
** the format is:
** TYPE name
** each line must only contain these two
** you cannot input the unique id.
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include "macros.h"
#include "my.h"
#include "shell.h"

static char *get_string_line(char *buffer, int *start)
{
    int i = *start;
    char *line;

    while (buffer[*start] != '\n' && buffer[*start] != '\0') {
        *start = *start + 1;
    }
    line = my_calloc(sizeof(char), ((*start - i) + 2));
    strncat(line, &buffer[i], (*start - i));
    *start = *start + 1;
    return (line);
}

static char *read_full_file(char const *filepath, int *size)
{
    char *buffer;
    struct stat sb;
    int fd = open(filepath, O_RDONLY);

    if (stat(filepath, &sb) != -1) {
        *size = sb.st_size;
        buffer = my_calloc(sizeof(char), (*size + 1));
        if (buffer == NULL)
            return (NULL);
        read(fd, buffer, *size);
    } else {
        return (NULL);
    }
    buffer[*size] = '\0';
    return (buffer);
}

int add_all_file(void *data, char **args, char *buffer, int size)
{
    int start = 0;
    int return_value = 0;
    char **word_array = NULL;
    char *line = NULL;

    while (start < size && return_value != 84) {
        line = get_string_line(buffer, &start);
        word_array = my_str_to_word_array(line);
        if (get_len_of_args(word_array) != 2 ||
            valid_type(word_array[0]) != 1) {
            return_value = 84;
        } else
            add(data, ((char *[3]){word_array[0], word_array[1], NULL}));
        free_word_array(word_array);
        word_array = NULL;
        free(line);
    }
    free(buffer);
    return (return_value);
}

int parse(void *data, char **args)
{
    char *buffer = NULL;
    int size = 0;
    int len = get_len_of_args(args);
    int result = 0;

    if (get_len_of_args(args) != 1)
        return (ERROR);
    buffer = read_full_file(args[0], &size);
    if (buffer == NULL)
        return (ERROR);
    return (add_all_file(data, args, buffer, size));
}
