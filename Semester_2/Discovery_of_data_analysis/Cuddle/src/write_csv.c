/*
** EPITECH PROJECT, 2026
** G2 - Discovery of Data Analysis - Cuddle - Alexis & Emilien
** File description:
** this file countains the df_write_csv function
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "dataframe.h"

static int print_bool(FILE *file, bool b)
{
    if (b)
        return fprintf(file, "true");
    return fprintf(file, "false");
}

static int print_typed_variable(FILE *file, void *var, column_type_t type)
{
    if (var == NULL)
        return 0;
    if (type == BOOL)
        return print_bool(file, *((bool *)(var)));
    if (type == STRING)
        return fprintf(file, TYPES_FLAGS[type], (char *)(var));
    if (type == INT)
        return fprintf(file, TYPES_FLAGS[type], *(int *)(var));
    if (type == UINT)
        return fprintf(file, TYPES_FLAGS[type], *(unsigned int *)(var));
    if (type == FLOAT)
        return fprintf(file, TYPES_FLAGS[type], *((double *)(var)));
    return fprintf(file, TYPES_FLAGS[type], *((void **)(var)));
}

static void print_line(dataframe_t *df, FILE *file, int j, char *sep)
{
    for (int i = 0; i < df->nb_columns; ++i) {
        print_typed_variable(file, df->data[i][j], df->column_types[i]);
        if (i + 1 < df->nb_columns)
            fprintf(file, "%s", sep);
    }
}

static FILE *error_handling(dataframe_t *data, const char *filename)
{
    FILE *file = NULL;

    if (data == NULL) {
        dprintf(2, "error: write_csv: dataframe is null\n");
        return (NULL);
    }
    if (filename == NULL) {
        dprintf(2, "error: write_csv: filename is null\n");
        return (NULL);
    }
    if (data->nb_columns < 1) {
        dprintf(2, "error: write_csv: dataframe is too small\n");
        return (NULL);
    }
    file = fopen(filename, "w");
    if (file == NULL) {
        dprintf(2, "error: write_csv: issue creating %s\n", filename);
        return (NULL);
    }
    return (file);
}

int df_write_csv(dataframe_t *data, const char *filename)
{
    FILE *file = error_handling(data, filename);

    if (file == NULL)
        return (EPITECH_FAILURE);
    fprintf(file, "%s", data->column_names[0]);
    for (int i = 1; i < data->nb_columns; ++i)
        fprintf(file, "%s%s", data->separator, data->column_names[i]);
    for (int i = 0; i < data->nb_rows; ++i) {
        fprintf(file, "\n");
        print_line(data, file, i, data->separator);
    }
    fprintf(file, "\n");
    fclose(file);
    return EPITECH_SUCCESS;
}
