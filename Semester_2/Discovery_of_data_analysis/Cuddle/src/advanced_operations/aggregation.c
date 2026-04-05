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

static bool check_column_names(dataframe_t *df, char *name, char **name_list)
{
    if (df == NULL || name == NULL || name_list == NULL)
        return false;
    if (index_of_str_arr(df->column_names, name) < 0)
        return false;
    for (int i = 0; name_list[i] != NULL; ++i)
        if (index_of_str_arr(df->column_names, name_list[i]) < 0 ||
            index_of_str_arr(&(name_list[i + 1]), name_list[i]) >= 0)
            return false;
    if (index_of_str_arr(name_list, name) >= 0)
        return false;
    return true;
}

static int init_column_names_and_types(dataframe_t *df, dataframe_t *df_new,
    char *name, char **name_list)
{
    int index = 0;

    for (int i = 0; df_new->column_names[i] != NULL; ++i) {
        df_new->column_types[i] = UNDEFINED;
        free(df_new->column_names[i]);
    }
    index = index_of_str_arr(df->column_names, name);
    df_new->column_names[0] = strdup(df->column_names[index]);
    if (df_new->column_names[0] == NULL)
        return EPITECH_FAILURE;
    df_new->column_types[0] = df->column_types[index];
    for (int i = 0; name_list[i] != NULL; ++i) {
        index = index_of_str_arr(df->column_names, name_list[i]);
        df_new->column_names[i + 1] = strdup(df->column_names[index]);
        if (df_new->column_names[i + 1] == NULL)
            return EPITECH_FAILURE;
        df_new->column_types[i + 1] = df->column_types[index];
    }
    return EPITECH_SUCCESS;
}

static void **rm_doubles(void **data, column_type_t type)
{
    int p = 0;
    int l = arr_len(data);
    void **data_new = malloc(sizeof(void *) * (l + 1));

    if (data_new == NULL)
        return NULL;
    data_new[0] = NULL;
    for (int i = 0; i < l; ++i) {
        if (!is_in_arr(data[i], data_new, type)) {
            data_new[p] = data[i];
            p += 1;
            data_new[p] = NULL;
        }
    }
    return data_new;
}

static void **select_values(dataframe_t *df, int col1, int col2, void *value)
{
    void **arr = malloc(sizeof(void *) * (df->nb_rows + 1));
    int p = 0;

    if (arr == NULL) {
        free(value);
        return NULL;
    }
    for (int i = 0; i < df->nb_rows; ++i)
        if (are_values_eq(df->data[col1][i], value, df->column_types[col1])) {
            arr[p] = cpy_data(df->data[col2][i], df->column_types[col2]);
            p += 1;
        }
    arr[p] = NULL;
    return arr;
}

static int set_first_col_content(dataframe_t *df, void **values)
{
    if (values == NULL)
        return EPITECH_FAILURE;
    for (int i = 0; i < df->nb_rows; ++i) {
        df->data[0][i] = cpy_data(values[i], df->column_types[0]);
        if (df->data[0][i] == NULL) {
            free(values);
            return EPITECH_FAILURE;
        }
    }
    return EPITECH_SUCCESS;
}

static int set_col_values(dataframe_t *dfs[2], int index[2], void *data[2],
    void *(*agg_func)(void **, int))
{
    int *to_agg = data[0];
    char *row_val = data[1];
    void **temp = NULL;
    int agg_by = index[0];
    int i = index[1];

    for (int j = 0; to_agg[j] >= 0; ++j) {
        temp = select_values(dfs[0], agg_by, to_agg[j], row_val);
        if (temp == NULL)
            return EPITECH_FAILURE;
        dfs[1]->data[j + 1][i] = agg_func(temp, arr_len(temp));
        free_array(temp);
    }
    return EPITECH_SUCCESS;
}

static int set_data(dataframe_t *dfs[2], int agg_by, int *to_agg,
    void *(*agg_func)(void **, int))
{
    void **row_list = rm_doubles(dfs[0]->data[agg_by],
        dfs[0]->column_types[agg_by]);
    void **temp = NULL;

    if (row_list == NULL)
        return EPITECH_FAILURE;
    dfs[1]->nb_rows = arr_len((void **)(row_list));
    if (set_first_col_content(dfs[1], row_list) !=
        EPITECH_SUCCESS)
        return EPITECH_FAILURE;
    for (int i = 0; i < dfs[1]->nb_rows; ++i)
        if (set_col_values(dfs, (int[2]){agg_by, i},
                (void *[2]){to_agg, row_list[i]}, agg_func) !=
            EPITECH_SUCCESS) {
            free(row_list);
            return EPITECH_FAILURE;
        }
    free(row_list);
    return EPITECH_SUCCESS;
}

static void get_columns_index(char **names, char **cols[2], int **index[2],
    int nb_columns)
{
    int *agg_by = (int *)(index[0]);
    int **to_agg = index[1];

    *agg_by = index_of_str_arr(names, (char *)(cols[0]));
    *to_agg = malloc(sizeof(int) * (nb_columns + 1));
    if (to_agg == NULL)
        return;
    for (int i = 0; i < nb_columns; ++i)
        (*to_agg)[i] = index_of_str_arr(names, cols[1][i]);
    (*to_agg)[nb_columns] = -1;
}

static int initialization(dataframe_t *dataframe, int *nb_columns,
    dataframe_t **df_new, const char **col_names[2])
{
    const char *aggregate_by = (const char *)(col_names[0]);
    const char **to_aggregate = col_names[1];

    *nb_columns = arr_len((void **)(to_aggregate)) + 1;
    if (*nb_columns > dataframe->nb_columns)
        return EPITECH_FAILURE;
    *df_new = init_new_df(dataframe);
    if (*df_new == NULL)
        return EPITECH_FAILURE;
    for (int i = *nb_columns; i < (*df_new)->nb_columns; ++i) {
        free_and_reset((void **)(&((*df_new)->column_names[i])));
        free_and_reset((void **)(&((*df_new)->data[i])));
    }
    (*df_new)->nb_columns = *nb_columns;
    if (init_column_names_and_types(dataframe, *df_new, (char *)(aggregate_by),
            (char **)(to_aggregate)) != EPITECH_SUCCESS) {
        df_free(*df_new);
        return EPITECH_FAILURE;
    }
    return EPITECH_SUCCESS;
}

dataframe_t *df_groupby(dataframe_t *dataframe, const char *aggregate_by,
    const char **to_aggregate, void *(*agg_func)(void **, int))
{
    int nb_columns = 0;
    dataframe_t *df_new = NULL;
    int agg_by = 0;
    int *to_agg = NULL;

    if (!check_column_names(dataframe, (char *)(aggregate_by),
            (char **)(to_aggregate)))
        return NULL;
    if (initialization(dataframe, &nb_columns, &df_new,
            (const char **[2]){(const char **)(aggregate_by), to_aggregate}) !=
        EPITECH_SUCCESS)
        return NULL;
    get_columns_index(dataframe->column_names,
        (char **[2]){(char **)(aggregate_by), (char **)(to_aggregate)},
        (int **[2]){(int **)(&agg_by), &to_agg}, nb_columns);
    if (set_data((dataframe_t *[2]){dataframe, df_new}, agg_by, to_agg,
            agg_func) != EPITECH_SUCCESS)
        return NULL;
    free(to_agg);
    return df_new;
}
