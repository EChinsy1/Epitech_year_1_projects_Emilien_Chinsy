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

static void print_int_arr(int *arr)
{
    if (arr[0] > 0)
        printf("%i", arr[1]);
    for (int i = 1; i < arr[0]; ++i)
        printf(", %i", arr[i + 1]);
    printf("}\n");
}

static int cut_array(int *arr_init, int **arr1, int **arr2)
{
    *arr1 = malloc(sizeof(int) * ((arr_init[0] / 2) + 1));
    *arr2 = malloc(sizeof(int) * (arr_init[0] - (arr_init[0] / 2) + 1));
    if (*arr1 == NULL || *arr2 == NULL) {
        free_two_ptrs((void *)(*arr1), (void *)(*arr2));
        return EPITECH_FAILURE;
    }
    (*arr1)[0] = arr_init[0] / 2;
    (*arr2)[0] = arr_init[0] - (*arr1)[0];
    for (int i = 0; i < (*arr1)[0]; ++i)
        (*arr1)[i + 1] = arr_init[i + 1];
    for (int i = 0; i < (*arr2)[0]; ++i)
        (*arr2)[i + 1] = arr_init[(*arr1)[0] + 1 + i];
    return EPITECH_SUCCESS;
}

static void add_trailing_values(int *arr, int *arrays[2], int *p, int i[2])
{
    for (int j = 0; (j + i[0]) < arrays[0][0]; ++j) {
        arr[*p] = arrays[0][j + i[0] + 1];
        *p += 1;
    }
    for (int j = 0; (j + i[1]) < arrays[1][0]; ++j)
        arr[*p + j] = arrays[1][j + i[1] + 1];
}

static int *join_arrays(dataframe_t *df, int column,
    bool (*sort_func)(void *, void *), int *arrays[2])
{
    int *arr = malloc(sizeof(int) * (arrays[0][0] + arrays[1][0] + 1));
    int i[2] = {0, 0};
    int p = 1;
    int n = 0;

    if (arr == NULL)
        return NULL;
    arr[0] = arrays[0][0] + arrays[1][0];
    for (; i[0] < arrays[0][0] && i[1] < arrays[1][0]; ++p) {
        n = 0;
        if (sort_func(df->data[column][arrays[0][i[0] + 1]],
                df->data[column][arrays[1][i[1] + 1]]))
            n = 1;
        arr[p] = arrays[n][i[n] + 1];
        i[n] += 1;
    }
    add_trailing_values(arr, arrays, &p, i);
    free_two_ptrs((void *)(arrays[0]), (void *)(arrays[1]));
    return arr;
}

static int *arr_dup(int *arr, dataframe_t *df, int column,
    bool (*sort_func)(void *, void *))
{
    int *arr_new = malloc(sizeof(int) * (arr[0] + 1));
    int temp = 0;

    if (arr_new == NULL)
        return NULL;
    for (int i = 0; i <= arr[0]; ++i)
        arr_new[i] = arr[i];
    if (arr_new[0] != 2)
        return arr_new;
    if (sort_func(df->data[column][arr_new[1]], df->data[column][arr_new[2]])) {
        temp = arr_new[1];
        arr_new[1] = arr_new[2];
        arr_new[2] = temp;
    }
    return arr_new;
}

int *merge_sort(dataframe_t *df, int *arr, int column,
    bool (*sort_func)(void *, void *))
{
    int *arrays[2] = {NULL, NULL};
    int *arr_news[2] = {NULL, NULL};

    if (arr[0] <= 2)
        return arr_dup(arr, df, column, sort_func);
    if (cut_array(arr, &(arrays[0]), &(arrays[1])) != EPITECH_SUCCESS)
        return NULL;
    arr_news[0] = merge_sort(df, arrays[0], column, sort_func);
    arr_news[1] = merge_sort(df, arrays[1], column, sort_func);
    free_two_ptrs((void *)(arrays[0]), (void *)(arrays[1]));
    if (arr_news[0] == NULL || arr_news[1] == NULL)
        return NULL;
    return join_arrays(df, column, sort_func, arr_news);
}

static int *init_array(dataframe_t *dataframe)
{
    int *array = malloc(sizeof(int) * (dataframe->nb_rows + 1));

    if (array == NULL)
        return NULL;
    array[0] = dataframe->nb_rows;
    for (int i = 0; i < array[0]; ++i)
        array[i + 1] = i;
    return array;
}

static dataframe_t *set_df_new(dataframe_t *df, dataframe_t *df_new, int *arr)
{
    for (int i = 0; i < arr[0]; ++i)
        if (data_dup(df, df_new, arr[i + 1], i) != EPITECH_SUCCESS) {
            df_free(df_new);
            free(arr);
            return NULL;
        }
    free(arr);
    return df_new;
}

dataframe_t *df_sort(dataframe_t *dataframe, const char *column,
    bool (*sort_func)(void *, void *))
{
    dataframe_t *df_new = NULL;
    int *arrays[2] = {NULL};
    int col = 0;

    if (dataframe == NULL || column == NULL || sort_func == NULL)
        return NULL;
    col = index_of_str_arr(dataframe->column_names, (char *)(column));
    arrays[0] = init_array(dataframe);
    if (col < 0 || arrays[0] == NULL)
        return free_two_ptrs((void *)(arrays[0]), NULL);
    df_new = init_new_df(dataframe);
    if (df_new == NULL)
        return free_two_ptrs((void *)(arrays[0]), NULL);
    arrays[1] = merge_sort(dataframe, arrays[0], col, sort_func);
    free(arrays[0]);
    if (arrays[1] == NULL) {
        df_free(df_new);
        return NULL;
    }
    return set_df_new(dataframe, df_new, arrays[1]);
}
