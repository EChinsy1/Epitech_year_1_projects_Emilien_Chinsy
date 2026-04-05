/*
** EPITECH PROJECT, 2026
** G2 - Discovery of Data Analysis - Cuddle - Alexis & Emilien
** File description:
** this file countains the df_filter function
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dataframe.h"

void *cpy_data(void *data, column_type_t type)
{
    void *data_new = NULL;

    if (type == STRING)
        return (void *)(strdup((const char *)(data)));
    if (type == UNDEFINED)
        return NULL;
    data_new = malloc(TYPES_SIZE[type]);
    if (data_new == NULL)
        return NULL;
    if (type == UINT)
        *((unsigned int *)(data_new)) = *((unsigned int *)(data));
    if (type == INT)
        *((int *)(data_new)) = *((int *)(data));
    if (type == FLOAT)
        *((double *)(data_new)) = *((double *)(data));
    if (type == BOOL)
        *((bool *)(data_new)) = *((bool *)(data));
    return data_new;
}

int data_dup(dataframe_t *df, dataframe_t *df_new, int row_init, int row_new)
{
    for (int i = 0; i < df->nb_columns; ++i) {
        df_new->data[i][row_new] =
            cpy_data(df->data[i][row_init], df->column_types[i]);
        if (df_new->data[i][row_new] == NULL) {
            df_free(df_new);
            return EPITECH_FAILURE;
        }
    }
    return EPITECH_SUCCESS;
}

static int dup_df_content(dataframe_t *dataframe, dataframe_t *df_new)
{
    for (int i = 0; i < df_new->nb_columns; ++i) {
        df_new->column_names[i] = strdup(dataframe->column_names[i]);
        df_new->column_types[i] = dataframe->column_types[i];
    }
    df_new->column_names[df_new->nb_columns] = NULL;
    df_new->column_types[df_new->nb_columns] = UNDEFINED;
    for (int i = 0; i < df_new->nb_columns; ++i) {
        df_new->data[i] = malloc(sizeof(void *) * (dataframe->nb_rows + 1));
        if (df_new->data[i] == NULL) {
            df_free(df_new);
            return EPITECH_FAILURE;
        }
        for (int j = 0; j <= dataframe->nb_rows; ++j)
            df_new->data[i][j] = NULL;
    }
    df_new->data[df_new->nb_columns] = NULL;
    return EPITECH_SUCCESS;
}

dataframe_t *init_new_df(dataframe_t *dataframe)
{
    dataframe_t *df_new = malloc(sizeof(dataframe_t));

    if (df_new == NULL)
        return NULL;
    *df_new = *dataframe;
    df_new->column_names = malloc(sizeof(char *) * (dataframe->nb_columns + 1));
    df_new->column_types =
        malloc(sizeof(column_type_t) * (dataframe->nb_columns + 1));
    df_new->data = malloc(sizeof(void **) * (dataframe->nb_columns + 1));
    df_new->nb_columns = dataframe->nb_columns;
    df_new->nb_rows = dataframe->nb_rows;
    df_new->separator = strdup(dataframe->separator);
    if (df_new->column_names == NULL || df_new->column_types == NULL ||
        df_new->data == NULL || df_new->separator == NULL) {
        free(df_new);
        return NULL;
    }
    if (dup_df_content(dataframe, df_new) != EPITECH_SUCCESS)
        return NULL;
    return df_new;
}

dataframe_t *df_filter(dataframe_t *dataframe, const char *column,
    bool (*filter_func)(void *))
{
    dataframe_t *df_new = NULL;
    int i = 0;

    if (dataframe == NULL || column == NULL || filter_func == NULL)
        return NULL;
    i = index_of_str_arr(dataframe->column_names, (char *)(column));
    if (i < 0)
        return NULL;
    df_new = init_new_df(dataframe);
    if (df_new == NULL)
        return NULL;
    df_new->nb_rows = 0;
    for (int j = 0; j < dataframe->nb_rows; ++j) {
        if (filter_func(dataframe->data[i][j])) {
            data_dup(dataframe, df_new, j, df_new->nb_rows);
            df_new->nb_rows += 1;
        }
    }
    return df_new;
}
