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

void **df_get_values(dataframe_t *dataframe, const char *column)
{
    int i = 0;
    void **array = NULL;

    if (dataframe == NULL) {
        dprintf(2, "error: get_unique_values: dataframe is NULL");
        return NULL;
    }
    i = index_of_str_arr(dataframe->column_names, (char *)(column));
    if (i < 0) {
        dprintf(2, "error: get_values: %s is not a column", column);
        return (NULL);
    }
    array = calloc(sizeof(void *), (dataframe->nb_rows + 1));
    array[dataframe->nb_rows] = NULL;
    for (int j = 0; j < dataframe->nb_rows; ++j) {
        array[j] = calloc(sizeof(void *), 1);
        memcpy(array[j], dataframe->data[i][j], sizeof(void *));
    }
    return (array);
}
