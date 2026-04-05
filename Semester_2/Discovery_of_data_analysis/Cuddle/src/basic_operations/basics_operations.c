/*
** EPITECH PROJECT, 2026
** G2 - Discovery of Data Analysis - Cuddle - Alexis & Emilien
** File description:
** this file countains the df_info and df_shape functions
*/

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "math.h"
#include "dataframe.h"

void df_info(dataframe_t *dataframe)
{
    if (dataframe == NULL)
        return;
    printf("%i columns:\n", dataframe->nb_columns);
    for (int i = 0; i < dataframe->nb_columns; ++i)
        printf("- %s: %s\n", dataframe->column_names[i],
            TYPES_NAMES[dataframe->column_types[i]]);
}

dataframe_shape_t df_shape(dataframe_t *dataframe)
{
    dataframe_shape_t shape = {0, 0};

    if (dataframe == NULL)
        return shape;
    shape.nb_rows = dataframe->nb_rows;
    shape.nb_columns = dataframe->nb_columns;
    return shape;
}

static void *get_right_type(dataframe_t *dataframe, void *data,
    int type, double *value)
{
    if (type == 1)
        *value = *((unsigned int *)(data));
    if (type == 2)
        *value = *((int *)(data));
    if (type == 3)
        *value = *((double *)(data));
    return (NULL);
}

static double make_std(double moy, int i, dataframe_t *dataframe, int type)
{
    double std = 0;
    double value = 0;

    for (int j = 0; dataframe->data[i][j]; ++j) {
        get_right_type(dataframe, dataframe->data[i][j], type, &value);
        std += (moy - value) * (moy - value);
    }
    std = sqrt(std / dataframe->nb_rows);
    return (std);
}

static void describe_values(dataframe_t *dataframe, int i, int type)
{
    double min = INT_MAX;
    double max = 0;
    double moy = 0;
    double std = 0;
    double value = 0;

    for (int j = 0; dataframe->data[i][j]; ++j) {
        get_right_type(dataframe, dataframe->data[i][j], type, &value);
        if (min > value)
            min = value;
        if (max < value)
            max = value;
        moy += value;
    }
    moy = moy / dataframe->nb_rows;
    std = make_std(moy, i, dataframe, type);
    printf("Mean: %.2f\nStd: %.2f\nMin: %.2f\nMax: %.2f\n", moy, std, min, max);
}

void df_describe(dataframe_t *dataframe)
{
    if (dataframe == NULL)
        return;
    for (int i = 0; i < dataframe->nb_columns; ++i) {
        if (dataframe->column_types[i] < 4 && dataframe->column_types[i] > 0) {
            printf("Column: %s\n", dataframe->column_names[i]);
            printf("Count: %d\n", dataframe->nb_rows);
            describe_values(dataframe, i, dataframe->column_types[i]);
        }
    }
}
