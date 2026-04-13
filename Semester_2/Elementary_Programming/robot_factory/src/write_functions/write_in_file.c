/*
** EPITECH PROJECT, 2026
** write in file
** File description:
** writes in a file
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "my.h"
#include "macro.h"

int write_in_file(FILE *file, char *text, size_t size)
{
    char *buffer = NULL;

    if (file == NULL || text == NULL)
        return ERROR;
    buffer = my_calloc(1, sizeof(char) * size);
    if (buffer == NULL)
        return ERROR;
    my_strncat(buffer, text, size);
    free(buffer);
    return SUCCESS;
}
