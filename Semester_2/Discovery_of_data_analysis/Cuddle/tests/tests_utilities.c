/*
** EPITECH PROJECT, 2026
** G2 - Discovery of Data Analysis - Cuddle - Alexis & Emilien
** File description:
** unit tests for the utilities functions
*/

#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include "dataframe.h"
#include "unit_tests.h"

Test(df_get_unique_values, test_of_the_subject)
{
    dataframe_t *df = df_read_csv("tests/data.csv", NULL);
    void **values = df_get_unique_values(df, "city");

    for (int i = 0; values[i] != NULL; ++i)
        printf("-> %s\n", (char *)(values[i]));
    printf("----\n");
    cr_assert(values != NULL);
    cr_assert_str_eq(values[0], "Paris");
    cr_assert_str_eq(values[1], "London");
    cr_assert_str_eq(values[2], "Berlin");
    cr_assert(values[3] == NULL);
    free_array(values);
    df_free(df);
}

Test(df_get_unique_values, error_handling)
{
    dataframe_t *df = df_read_csv("tests/data.csv", NULL);

    cr_assert(df_get_unique_values(NULL, "age") == NULL);
    cr_assert(df_get_unique_values(df, NULL) == NULL);
    cr_assert(df_get_unique_values(df, "test") == NULL);
}

Test(df_get_value, test_of_the_subject)
{
    dataframe_t *df = df_read_csv("tests/data.csv", NULL);
    void *value = df_get_value(df, 0, "age");

    df_free(df);
    cr_assert(value != NULL);
    printf("value = %u\n", *((unsigned int *)(value)));
    cr_assert(*((unsigned int *)(value)) == 25);
    free(value);
}

Test(df_get_value, error_handling)
{
    dataframe_t *df = df_read_csv("tests/data.csv", NULL);

    cr_assert(df_get_value(NULL, 0, "age") == NULL);
    cr_assert(df_get_value(df, -4, "age") == NULL);
    cr_assert(df_get_value(df, 5, NULL) == NULL);
    cr_assert(df_get_value(df, 0, "test") == NULL);
    df_free(df);
}

Test(df_get_values, test_of_the_subject)
{
    dataframe_t *df = df_read_csv("tests/data.csv", NULL);
    void **values = df_get_values(df, "age");

    cr_assert(values != NULL);
    cr_assert(*((unsigned int *)(values[0])) == 25);
    cr_assert(*((unsigned int *)(values[1])) == 30);
    cr_assert(*((unsigned int *)(values[2])) == 35);
    cr_assert(*((unsigned int *)(values[3])) == 25);
    cr_assert(*((unsigned int *)(values[4])) == 30);
    cr_assert(*((unsigned int *)(values[5])) == 35);
    cr_assert(*((unsigned int *)(values[6])) == 25);
    cr_assert(values[7] == NULL);
    df_free(df);
    free_array(values);
}

Test(df_get_values, error_handling)
{
    dataframe_t *df = df_read_csv("tests/data.csv", NULL);

    cr_assert(df_get_values(NULL, "age") == NULL);
    cr_assert(df_get_values(df, NULL) == NULL);
    cr_assert(df_get_values(df, "test") == NULL);
    df_free(df);
}
