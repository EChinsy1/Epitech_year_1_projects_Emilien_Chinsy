/*
** EPITECH PROJECT, 2026
** G2 - Discovery of Data Analysis - Cuddle - Alexis & Emilien
** File description:
** this file countains the free_array and the df_free functions
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "dataframe.h"

void *free_two_ptrs(void *ptr1, void *ptr2)
{
    if (ptr1 != NULL)
        free(ptr1);
    if (ptr2 != NULL)
        free(ptr2);
    return NULL;
}

void free_and_reset(void **ptr)
{
    if (ptr == NULL)
        return;
    if (*ptr == NULL)
        return;
    free(*ptr);
    *ptr = NULL;
}

void free_array(void **arr)
{
    if (arr == NULL)
        return;
    for (int i = 0; arr[i] != NULL; ++i)
        free(arr[i]);
    free(arr);
}

void df_free(dataframe_t *df)
{
    if (df == NULL)
        return;
    if (df->column_names != NULL)
        free_array((void **)(df->column_names));
    if (df->column_types != NULL)
        free(df->column_types);
    if (df->separator != NULL)
        free(df->separator);
    if (df->data != NULL) {
        for (int i = 0; i < df->nb_columns; ++i)
            free_array(df->data[i]);
        free(df->data);
    }
    free(df);
}
