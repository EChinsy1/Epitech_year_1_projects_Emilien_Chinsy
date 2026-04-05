/*
** EPITECH PROJECT, 2026
** G2 - Discovery of Data Analysis - Cuddle - Alexis & Emilien
** File description:
** this file countains the df_read_csv function
*/

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dataframe.h"

column_type_t get_type(char *b)
{
    int num_of_points = 0;

    if (b == NULL)
        return (UNDEFINED);
    if (is_a_bool(b))
        return (BOOL);
    for (int i = 0; b[i] != '\0'; ++i) {
        if (b[i] == '.')
            ++num_of_points;
        if ((b[i] > '9' || b[i] < '0') && (b[i] != '-' && b[i] != '.'))
            return (STRING);
    }
    if (num_of_points >= 2 || b[0] == '.')
        return (STRING);
    if (num_of_points == 1)
        return (FLOAT);
    if (b[0] == '-')
        return (INT);
    return (UINT);
}

static dataframe_t *set_values(dataframe_t *dataframe, int count)
{
    dataframe->nb_columns = count;
    dataframe->column_names = calloc(sizeof(char *), (count + 1));
    dataframe->data = calloc(sizeof(void **), count + 1);
    dataframe->column_types = calloc(sizeof(void **), count + 1);
    dataframe->data[count] = NULL;
    dataframe->column_types[count] = -1;
    return (dataframe);
}

static dataframe_t *get_num_of_columns(char *buffer,
    dataframe_t *dataframe)
{
    int count = 1;
    char *value = NULL;

    for (int i = 0; buffer[i] != '\0'; ++i) {
        if (strncmp(&buffer[i], dataframe->separator,
                strlen(dataframe->separator)) == 0)
            ++count;
    }
    if (count == 1)
        dprintf(2, "error: read_csv: %s not in file\n", dataframe->separator);
    dataframe = set_values(dataframe, count);
    for (int i = 0; i < count; ++i) {
        dataframe->data[i] = calloc(sizeof(void **), 2);
        dataframe->data[i][1] = NULL;
        value = strsep(&buffer, dataframe->separator);
        dataframe->column_names[i] = strdup(value);
        dataframe->column_types[i] = 0;
    }
    dataframe->column_names[count] = NULL;
    return (dataframe);
}

static void *cast_the_right_int(void *value, column_type_t type)
{
    int *value_int = NULL;
    unsigned int *value_uint = NULL;

    if (type == UINT) {
        value_uint = calloc(sizeof(unsigned int), 2);
        *value_uint = atoi((char *)value);
        return (value_uint);
    }
    if (type == INT) {
        value_int = calloc(sizeof(int), 2);
        *value_int = atoi((char *)value);
        return (value_int);
    }
    return (NULL);
}

static void *cast_to_bool(char *str)
{
    char *tmp = to_lower(str);
    bool *b = NULL;

    if (tmp == NULL)
        return NULL;
    b = malloc(sizeof(bool));
    if (b == NULL) {
        free(tmp);
        return NULL;
    }
    *b = (strcmp(tmp, STRUE) == 0);
    free(tmp);
    return b;
}

void *cast_the_right_type(char *fake_value, column_type_t type)
{
    double *value_float = NULL;

    if (type == BOOL)
        return cast_to_bool(fake_value);
    if (type == STRING)
        return (char **)(strdup(fake_value));
    if (type == FLOAT) {
        value_float = calloc(sizeof(double), 2);
        *value_float = atof((char *)(fake_value));
        return (value_float);
    }
    return (cast_the_right_int(fake_value, type));
}

dataframe_t *get_line_values(dataframe_t *dataframe,
    char *buffer, const char *separator)
{
    char *value = NULL;
    column_type_t type = 0;

    for (int i = 0; i < dataframe->nb_columns; ++i) {
        value = strsep(&buffer, separator);
        type = get_type(value);
        if (type > dataframe->column_types[i])
            dataframe->column_types[i] = type;
        dataframe->data[i] = realloc(dataframe->data[i],
            sizeof(void *) * ((dataframe->nb_rows - 1) + 1));
        dataframe->data[i][dataframe->nb_rows - 1] = NULL;
        dataframe->data[i][(dataframe->nb_rows - 1) - 1] =
            cast_the_right_type(value, type);
    }
    return (dataframe);
}

static void *free_pointers(FILE *file, dataframe_t *df, char *buffer)
{
    if (file != NULL)
        fclose(file);
    if (df != NULL)
        free(df);
    if (buffer != NULL)
        free(buffer);
    return NULL;
}

static char *get_separator(const char *separator)
{
    if (!separator)
        return (strdup(","));
    return (strdup(separator));
}

dataframe_t *df_read_csv(const char *filename, const char *separator)
{
    FILE *fd = fopen(filename, "r");
    dataframe_t *dataframe = malloc(sizeof(dataframe_t) * 1);
    char *buffer = NULL;
    size_t size = 0;

    if (fd == NULL || dataframe == NULL)
        return free_pointers(fd, dataframe, NULL);
    dataframe->separator = get_separator(separator);
    dataframe->nb_rows = 0;
    while (getline(&buffer, &size, fd) > 0) {
        remove_trailing_newline(buffer);
        dataframe->nb_rows += 1;
        if (dataframe->nb_rows == 1)
            dataframe = get_num_of_columns(buffer, dataframe);
        if (dataframe->nb_rows > 1)
            get_line_values(dataframe, buffer, dataframe->separator);
    }
    free_pointers(fd, NULL, buffer);
    dataframe->nb_rows -= 1;
    return (dataframe);
}
