/*
** EPITECH PROJECT, 2026
** G2 - Discovery of Data Analysis - Cuddle - Alexis & Emilien
** File description:
** this file countains the df_head
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "dataframe.h"

static dataframe_t *set_tail_values(dataframe_t *dataframe, dataframe_t *tail,
    int nb_rows)
{
    tail = malloc(sizeof(dataframe_t) * 1);
    if (!tail)
        return (NULL);
    tail->nb_rows = nb_rows;
    tail->separator = strdup(dataframe->separator);
    tail->nb_columns = dataframe->nb_columns;
    tail->column_types = calloc(sizeof(column_type_t), tail->nb_columns + 1);
    tail->column_names = calloc(sizeof(char *), tail->nb_columns + 1);
    for (int i = 0; i < dataframe->nb_columns; ++i) {
        tail->column_types[i] = dataframe->column_types[i];
        tail->column_names[i] = strdup(dataframe->column_names[i]);
    }
    tail->column_types[tail->nb_columns] = -1;
    tail->column_names[tail->nb_columns] = NULL;
    tail->data = calloc(sizeof(void **), tail->nb_columns + 1);
    tail->data[tail->nb_columns] = NULL;
    return (tail);
}

static int error_handling(dataframe_t *dataframe, int *nb_rows)
{
    if (dataframe == NULL) {
        dprintf(2, "error: tail_csv: dataframe is null\n");
        return (EPITECH_FAILURE);
    }
    if (*nb_rows < 0) {
        dprintf(2, "error: tail_csv: %d is negative\n", *nb_rows);
        return (EPITECH_FAILURE);
    }
    if (*nb_rows > dataframe->nb_rows)
        *nb_rows = dataframe->nb_rows;
    return (0);
}

static int get_size(void **item, void *value, column_type_t type)
{
    if (type == BOOL) {
        *item = calloc(sizeof(char *), strlen(value) + 1);
        return (strlen(value) + 1);
    }
    if (type == STRING) {
        *item = calloc(sizeof(char *), strlen(value) + 1);
        return (strlen(value) + 1);
    }
    if (type == INT || type == UINT) {
        *item = calloc(sizeof(int *), 2);
        return (4);
    }
    *item = calloc(sizeof(float), 2);
    return (8);
}

dataframe_t *df_tail(dataframe_t *df, int nb_rows)
{
    dataframe_t *tail = NULL;
    int size = 0;
    int error_handling_var = error_handling(df, &nb_rows);

    if (error_handling_var == EPITECH_FAILURE)
        return (tail);
    tail = set_tail_values(df, tail, nb_rows);
    for (int i = 0; i < tail->nb_columns; ++i) {
        tail->data[i] = calloc(sizeof(void *), (tail->nb_rows + 1));
        for (int j = 0; j < nb_rows; ++j) {
            size = get_size(&tail->data[i][j], df->data[i]
                [(df->nb_rows - (nb_rows - j))], df->column_types[i]);
            memcpy(tail->data[i][j], df->data[i][(df->nb_rows
                        - (nb_rows - j))], size);
        }
    }
    return (tail);
}
