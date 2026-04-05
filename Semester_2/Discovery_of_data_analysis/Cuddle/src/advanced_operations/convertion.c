/*
** EPITECH PROJECT, 2026
** G2 - Discovery of Data Analysis - Cuddle - Alexis & Emilien
** File description:
** this file countains the df_to_type function
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "dataframe.h"

static void *convert_to_bool(void *data, column_type_t type)
{
    bool value = false;
    char *tmp = NULL;

    if (type == UNDEFINED)
        return NULL;
    if (type == BOOL)
        return cpy_data(data, BOOL);
    if (type == UINT || type == INT || type == FLOAT)
        value = (*((void **)(data)) != 0);
    if (type == STRING) {
        tmp = to_lower((char *)(data));
        if (tmp == NULL)
            return NULL;
        if (strcmp((const char *)(tmp), STRUE) == 0)
            value = true;
        if (strcmp((const char *)(tmp), SFALSE) != 0 && !value)
            return NULL;
        free(tmp);
    }
    return cpy_data(&value, BOOL);
}

static void *convert_to_uint(void *data, column_type_t type)
{
    unsigned int value = 0;

    if (type == UNDEFINED)
        return NULL;
    if (type == BOOL)
        value = BOOL_TO_NBR(*((bool *)(data)));
    if (type == UINT)
        return cpy_data(data, UINT);
    if ((type == INT && *((int *)(data)) < 0 ||
            (type == FLOAT && *((double *)(data)) < 0)))
        return NULL;
    if (type == INT)
        value = *((int *)(data));
    if (type == FLOAT)
        value = iround(*((double *)(data)));
    if (type == STRING)
        return convert_nbr_from_str((char *)(data), UINT);
    return cpy_data(&value, UINT);
}

static void *convert_to_int(void *data, column_type_t type)
{
    int value = 0;

    if (type == UNDEFINED)
        return NULL;
    if (type == BOOL)
        value = BOOL_TO_NBR(*((bool *)(data)));
    if (type == UINT)
        value = *((unsigned int *)(data));
    if (type == INT)
        return cpy_data(data, INT);
    if (type == FLOAT)
        value = iround(*((double *)(data)));
    if (type == STRING) {
        return convert_nbr_from_str((char *)(data), INT);
    }
    return cpy_data(&value, INT);
}

static void *convert_to_float(void *data, column_type_t type)
{
    double value = 0;

    if (type == UNDEFINED)
        return NULL;
    if (type == BOOL)
        value = BOOL_TO_NBR(*((bool *)(data)));
    if (type == UINT)
        value = *((unsigned int *)(data));
    if (type == INT)
        value = *((int *)(data));
    if (type == FLOAT)
        return cpy_data(data, FLOAT);
    if (type == STRING)
        return convert_nbr_from_str((char *)(data), FLOAT);
    return cpy_data(&value, FLOAT);
}

static void *simple_duplications(void *data, column_type_t type)
{
    char *buffer = NULL;
    int size = 0;

    if (type == FLOAT)
        size = get_nbr_digits(iround(*((double *)(data)))) + 7;
    else if (type == UINT)
        size = get_nbr_digits(*((unsigned int *)(data)));
    else
        size = get_nbr_digits(*((int *)(data))) + 1;
    size += 1;
    buffer = malloc(sizeof(char) * (size + 1));
    for (int i = 0; i <= size; ++i)
        buffer[i] = '\0';
    if (type == UINT)
        sprintf(buffer, TYPES_FLAGS[type], *((unsigned int *)(data)));
    if (type == INT)
        sprintf(buffer, TYPES_FLAGS[type], *((int *)(data)));
    if (type == FLOAT)
        sprintf(buffer, TYPES_FLAGS[type], *((double *)(data)));
    return buffer;
}

static void *convert_to_string(void *data, column_type_t type)
{
    char *buffer = NULL;
    int size = 0;

    if (type == UNDEFINED)
        return NULL;
    if (type == BOOL)
        return strdup(BOOL_TO_STR(*((bool *)(data))));
    if (type == STRING)
        return strdup((const char *)(data));
    return simple_duplications(data, type);
}

void *cpy_to_type(void *data, column_type_t type_from, column_type_t type_to)
{
    if (type_to == UNDEFINED || type_from == UNDEFINED)
        return NULL;
    if (type_to == BOOL)
        return convert_to_bool(data, type_from);
    if (type_to == UINT)
        return convert_to_uint(data, type_from);
    if (type_to == INT)
        return convert_to_int(data, type_from);
    if (type_to == FLOAT)
        return convert_to_float(data, type_from);
    if (type_to == STRING)
        return convert_to_string(data, type_from);
    return NULL;
}

static int set_column(dataframe_t *dfs[2], column_type_t type_from,
    int index[2], column_type_t type_to)
{
    dataframe_t *df = dfs[0];
    dataframe_t *df_new = dfs[1];
    int column = index[0];
    int searched = index[1];

    for (int r = 0; r < df_new->nb_rows; ++r) {
        if (column == searched) {
            df_new->data[column][r] = cpy_to_type(df->data[column][r],
                type_from, type_to);
        } else
            df_new->data[column][r] = cpy_data(df->data[column][r], type_from);
        if (df_new->data[column][r] == NULL)
            return EPITECH_FAILURE;
    }
    return EPITECH_SUCCESS;
}

dataframe_t *df_to_type(dataframe_t *dataframe, const char *column,
    column_type_t downcast)
{
    dataframe_t *df_new = NULL;
    int col_index = 0;

    if (dataframe == NULL || column == NULL)
        return NULL;
    col_index = index_of_str_arr(dataframe->column_names, (char *)(column));
    if (col_index < 0)
        return NULL;
    df_new = init_new_df(dataframe);
    if (df_new == NULL)
        return NULL;
    df_new->column_types[col_index] = downcast;
    for (int c = 0; c < df_new->nb_columns; ++c)
        if (set_column((dataframe_t *[2]){dataframe, df_new},
                dataframe->column_types[c], (int[2]){c, col_index}, downcast) !=
            EPITECH_SUCCESS) {
            df_free(df_new);
            return NULL;
        }
    return df_new;
}
