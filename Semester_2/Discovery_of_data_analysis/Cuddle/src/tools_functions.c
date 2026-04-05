/*
** EPITECH PROJECT, 2026
** G2 - Discovery of Data Analysis - Cuddle - Alexis & Emilien
** File description:
** this file countains the df_filter function
*/

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "dataframe.h"

int arr_len(void **arr)
{
    int l = 0;

    if (arr == NULL)
        return -1;
    for (int i = 0; arr[i] != NULL; ++i)
        l += 1;
    return l;
}

int index_of_str_arr(char **arr, char *str)
{
    int i = 0;

    if (arr == NULL || str == NULL)
        return -1;
    for (int i = 0; arr[i] != NULL; ++i)
        if (strcmp((const char *)(arr[i]), (const char *)(str)) == 0)
            return i;
    return -1;
}

bool are_values_eq(void *value1, void *value2, column_type_t type)
{
    if (type == STRING)
        return (strcmp((const char *)(value1), (const char *)(value2)) == 0);
    return (*((void **)(value1)) == *((void **)(value2)));
}

bool is_in_arr(void *item, void **arr, column_type_t type)
{
    if (type == STRING)
        return (index_of_str_arr((char **)(arr), (char *)(item)) >= 0);
    if (type == UNDEFINED)
        return false;
    for (int i = 0; arr[i] != NULL; ++i)
        if (are_values_eq(arr[i], item, type))
            return true;
    return false;
}

void remove_trailing_newline(char *str)
{
    int l = strlen(str);

    for (int i = l - 1; i >= 0 && str[i] == '\n'; --i)
        str[i] = '\0';
}
