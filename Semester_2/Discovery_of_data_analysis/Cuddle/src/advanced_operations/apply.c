/*
** EPITECH PROJECT, 2026
** G2 - Discovery of Data Analysis - Cuddle - Alexis & Emilien
** File description:
** this file countains the df_apply function
*/

#include <stdio.h>
#include "dataframe.h"

static int set_column(dataframe_t *dfs[2], column_type_t type, int index[2],
    void *(*apply_func)(void *))
{
    dataframe_t *df = dfs[0];
    dataframe_t *df_new = dfs[1];
    int column = index[0];
    int searched = index[1];

    for (int r = 0; r < df_new->nb_rows; ++r) {
        if (column == searched)
            df_new->data[column][r] = apply_func(df->data[column][r]);
        else
            df_new->data[column][r] = cpy_data(df->data[column][r], type);
        if (df_new->data[column][r] == NULL && column != searched)
            return EPITECH_FAILURE;
    }
    return EPITECH_SUCCESS;
}

dataframe_t *df_apply(dataframe_t *dataframe, const char *column,
    void *(*apply_func)(void *))
{
    dataframe_t *df_new = NULL;
    int col_index = 0;

    if (dataframe == NULL || column == NULL || apply_func == NULL)
        return NULL;
    col_index = index_of_str_arr(dataframe->column_names, (char *)(column));
    if (col_index < 0)
        return NULL;
    df_new = init_new_df(dataframe);
    if (df_new == NULL)
        return NULL;
    for (int c = 0; c < df_new->nb_columns; ++c)
        if (set_column((dataframe_t *[2]){dataframe, df_new},
                df_new->column_types[c], (int[2]){c, col_index}, apply_func) !=
            EPITECH_SUCCESS) {
            df_free(df_new);
            return NULL;
        }
    return df_new;
}
