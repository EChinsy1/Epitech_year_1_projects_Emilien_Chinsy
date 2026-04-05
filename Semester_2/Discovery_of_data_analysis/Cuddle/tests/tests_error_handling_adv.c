/*
** EPITECH PROJECT, 2026
** G2 - Discovery of Data Analysis - Cuddle - Alexis & Emilien
** File description:
** unit tests for the df_groupby, df_apply, df_to_type, df_filter and df_sort
** functions in error cases
*/

#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "dataframe.h"

static void compare_file_content(char *filename, char *expected[])
{
    char *buffer = NULL;
    size_t size = 0;
    int i = 0;
    FILE *file = fopen(filename, "r");

    cr_assert(file != NULL);
    for (; getline(&buffer, &size, file) > 0; ++i) {
        cr_assert(expected[i] != NULL);
        cr_assert_str_eq(buffer, expected[i]);
    }
    free(buffer);
    fclose(file);
    cr_assert(expected[i] == NULL);
}

static void *agg_func(void **values, int nb_values)
{
    unsigned int *sum = malloc(sizeof(unsigned int));

    *sum = 0;
    for (int i = 0; i < nb_values; i++)
    *sum += *(unsigned int *)values[i];
    return sum;
}

static void *apply_func1(void *value)
{
    unsigned int *new_value = malloc(sizeof(unsigned int));

    *new_value = *(unsigned int *)value * 2;
    return new_value;
}

static void *apply_func2(void *value)
{
    double *new_value = malloc(sizeof(double));

    *new_value = *((unsigned int *)(value));
    return new_value;
}

static bool filter_func(void *value) {
    return *(unsigned int *)(value) > 30;
}

static double filter_func2(void *value) {
    return (double)(*((unsigned int *)(value)));
}

static bool sort_func(void *value1, void *value2) {
    return *(unsigned int *)(value1) > *(unsigned int *)(value2);
}

static unsigned int sort_func2(void *value1, void *value2) {
    return (*((unsigned int *)(value1)) + *((unsigned int *)(value2)));
}

// unit tests

Test(df_groupby, test_groupby_in_invalid_cases)
{
    dataframe_t *df = df_read_csv("tests/data.csv", ",");

    cr_assert(df_groupby(NULL, "name", (const char *[]){"age", NULL},
        &agg_func) == NULL);
    cr_assert(df_groupby(df, NULL, (const char *[]){"age", NULL}, &agg_func) ==
        NULL);
    cr_assert(df_groupby(df, "test", (const char *[]){"age", NULL}, &agg_func)
        == NULL);
    cr_assert(df_groupby(df, "name", (const char *[]){"age", "name", "age"},
        &agg_func) == NULL);
    cr_assert(df_groupby(df, "name", NULL, NULL) == NULL);
    df_free(df);
}

Test(df_apply, test_apply_in_invalid_cases)
{
    dataframe_t *df = df_read_csv("tests/data.csv", ",");

    cr_assert(df_apply(NULL, "age", &apply_func1) == NULL);
    cr_assert(df_apply(df, NULL, &apply_func1) == NULL);
    cr_assert(df_apply(df, "test", &apply_func1) == NULL);
    cr_assert(df_apply(df, "age", NULL) == NULL);
    df_free(df);
}

Test(df_apply, test_apply_with_a_function_modifying_data_type)
{
    dataframe_t *df = df_read_csv("tests/data.csv", ",");

    cr_assert(df_apply(df, "age", &apply_func2) != NULL);
    df_free(df);
}

Test(df_to_type, test_convertion_in_invalid_cases)
{
    dataframe_t *df = df_read_csv("tests/data.csv", ",");

    cr_assert(df_to_type(NULL, "age", FLOAT) == NULL);
    cr_assert(df_to_type(df, NULL, BOOL) == NULL);
    cr_assert(df_to_type(df, "NULL", BOOL) == NULL);
    cr_assert(df_to_type(df, "age", UNDEFINED) == NULL);
    df_free(df);
}

Test(df_filter, test_filter_in_invalid_cases)
{
    dataframe_t *df = df_read_csv("tests/data.csv", ",");

    cr_assert(df_filter(NULL, "city", &filter_func) == NULL);
    cr_assert(df_filter(df, NULL, &filter_func) == NULL);
    cr_assert(df_filter(df, "NULL", &filter_func) == NULL);
    cr_assert(df_filter(df, "city", NULL) == NULL);
    cr_assert(df_filter(df, "city", (bool (*)(void *))(&filter_func2)) != NULL);
    df_free(df);
}

Test(df_filter, test_sort_in_invalid_cases)
{
    dataframe_t *df = df_read_csv("tests/data.csv", ",");

    cr_assert(df_sort(NULL, "age", &sort_func) == NULL);
    cr_assert(df_sort(df, NULL, &sort_func) == NULL);
    cr_assert(df_sort(df, "NULL", &sort_func) == NULL);
    cr_assert(df_sort(df, "age", NULL) == NULL);
    cr_assert(df_sort(df, "city", (bool (*)(void *, void *))(&sort_func2)) !=
        NULL);
    df_free(df);
}
