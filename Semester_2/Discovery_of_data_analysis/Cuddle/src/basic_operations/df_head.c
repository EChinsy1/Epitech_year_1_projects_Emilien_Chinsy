/*
** EPITECH PROJECT, 2026
** G2 - Discovery of Data Analysis - Cuddle - Alexis & Emilien
** File description:
** this file countains the df_head
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "dataframe.h"

dataframe_t *set_head_values(dataframe_t *dataframe, dataframe_t *head,
    int nb_rows)
{
    head = malloc(sizeof(dataframe_t) * 1);
    if (!head)
        return (NULL);
    head->nb_rows = nb_rows;
    head->separator = strdup(dataframe->separator);
    head->nb_columns = dataframe->nb_columns;
    head->column_types = calloc(sizeof(column_type_t), head->nb_columns + 1);
    head->column_names = calloc(sizeof(char *), head->nb_columns + 1);
    for (int i = 0; i < dataframe->nb_columns; ++i) {
        head->column_types[i] = dataframe->column_types[i];
        head->column_names[i] = strdup(dataframe->column_names[i]);
    }
    head->column_types[head->nb_columns] = -1;
    head->column_names[head->nb_columns] = NULL;
    head->data = calloc(sizeof(void **), head->nb_columns + 1);
    head->data[head->nb_columns] = NULL;
    return (head);
}

static int error_handling(dataframe_t *dataframe, int *nb_rows)
{
    if (dataframe == NULL) {
        dprintf(2, "error: head_csv: dataframe is null\n");
        return (EPITECH_FAILURE);
    }
    if (*nb_rows < 0) {
        dprintf(2, "error: head_csv: %d is negative\n", *nb_rows);
        return (EPITECH_FAILURE);
    }
    if (*nb_rows > dataframe->nb_rows)
        *nb_rows = dataframe->nb_rows;
    return (0);
}

static int get_size(void **item, void *value, column_type_t type)
{
    if (type == BOOL) {
        *item = calloc(sizeof(char *), strlen(value) + 1);
        return (strlen(value) + 1);
    }
    if (type == STRING) {
        *item = calloc(sizeof(char *), strlen(value) + 1);
        return (strlen(value) + 1);
    }
    if (type == INT || type == UINT) {
        *item = calloc(sizeof(int), 2);
        return (4);
    }
    *item = calloc(sizeof(float), 2);
    return (8);
}

dataframe_t *df_head(dataframe_t *dataframe, int nb_rows)
{
    dataframe_t *head = NULL;
    int size = 0;
    int error_handling_var = error_handling(dataframe, &nb_rows);

    if (error_handling_var == EPITECH_FAILURE)
        return (head);
    head = set_head_values(dataframe, head, nb_rows);
    for (int i = 0; i < head->nb_columns; ++i) {
        head->data[i] = calloc(sizeof(void *), (head->nb_rows + 1));
        for (int j = 0; j < nb_rows; ++j) {
            size = get_size(&head->data[i][j], dataframe->data[i][j],
                dataframe->column_types[i]);
            memcpy(head->data[i][j], dataframe->data[i][j], size);
        }
        head->data[i][head->nb_rows] = NULL;
    }
    return (head);
}
