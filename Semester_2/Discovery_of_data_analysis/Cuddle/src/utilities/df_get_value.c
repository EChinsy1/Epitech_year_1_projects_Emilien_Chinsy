/*
** EPITECH PROJECT, 2026
** G2 - Discovery of Data Analysis - Cuddle - Alexis & Emilien
** File description:
** this file countains the df_get_value
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dataframe.h"

void *df_get_value(dataframe_t *dataframe, int row, const char *column)
{
    int i = 0;
    void *value = NULL;

    if (dataframe == NULL) {
        dprintf(2, "error: get_unique_values: dataframe is NULL");
        return NULL;
    }
    if (row > dataframe->nb_rows || row < 0) {
        dprintf(2, "error: get_value: row %d is not in the dataframe", row);
        return (NULL);
    }
    i = index_of_str_arr(dataframe->column_names, (char *)(column));
    if (i < 0) {
        dprintf(2, "error: get_value: %s is not a column", column);
        return (NULL);
    }
    return cpy_data(dataframe->data[i][row], dataframe->column_types[i]);
}
