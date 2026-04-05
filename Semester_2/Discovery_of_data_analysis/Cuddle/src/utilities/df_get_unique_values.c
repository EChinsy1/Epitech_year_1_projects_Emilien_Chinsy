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

int check_if_contains(void **array, void *value, int type)
{
    int valid = 0;

    for (int i = 0; array[i]; ++i) {
        if ((type == STRING || type == BOOL)
            && strcmp((char *)array[i], value) == 0)
            return (1);
        if ((type == INT || type == UINT)
            && (*(int *)array[i] == (*(int *)value)))
            return (1);
        if (type == FLOAT && (*(double *)array[i] == (*(double *)value)))
            return (1);
    }
    return (0);
}

int get_column_index(dataframe_t *dataframe, const char *column)
{
    int i = 0;

    if (dataframe == NULL) {
        dprintf(2, "error: get_unique_values: dataframe is NULL");
        return -1;
    }
    return index_of_str_arr(dataframe->column_names, (char *)(column));
}

void **df_get_unique_values(dataframe_t *dataframe, const char *column)
{
    int i = get_column_index(dataframe, column);
    void **array = NULL;
    int num = 0;

    if (i == - 1)
        return NULL;
    array = calloc(sizeof(void *), (dataframe->nb_rows + 1));
    array[dataframe->nb_rows] = NULL;
    for (int j = 0; j < dataframe->nb_rows; ++j) {
        if (check_if_contains(array,
                dataframe->data[i][j], dataframe->column_types[i]) == 0) {
            array[num] = calloc(sizeof(void *), 1);
            memcpy(array[num], dataframe->data[i][j], sizeof(void *));
            ++num;
        }
    }
    return (array);
}
