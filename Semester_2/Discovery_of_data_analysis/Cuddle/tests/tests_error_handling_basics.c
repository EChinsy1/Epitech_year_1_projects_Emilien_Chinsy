/*
** EPITECH PROJECT, 2026
** G2 - Discovery of Data Analysis - Cuddle - Alexis & Emilien
** File description:
** unit tests for the df_info, df_shape, df_describe, df_head and df_tail
** functions in invalid cases
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "dataframe.h"
#include "unit_tests.h"

Test(df_head, tests_for_error_handling)
{
    dataframe_t *df = df_read_csv("tests/data.csv", ",");
    dataframe_shape_t shape = df_shape(df);
    dataframe_t *df2 = NULL;
    char *filename = "error_handling_basic.csv";
    char *lines[9] = {"name,age,city\n", "Alice,25,Paris\n", "Bob,30,London\n",
        "Charlie,35,Berlin\n", "Léo,25,Paris\n", "Nathan,30,London\n",
        "Alex,35,Berlin\n", "Paul,25,Paris\n", NULL};

    df_info(NULL);
    df_describe(NULL);
    cr_assert(df_head(NULL, 10) == NULL);
    cr_assert(df_head(df, -42) == NULL);
    df2 = df_head(df, 100);
    cr_assert(df2 != NULL);
    cr_assert(df_write_csv(df2, filename) == 0);
    compare_file_content(filename, lines);
    remove(filename);
    df_free(df2);
    df2 = df_tail(df, 10);
    cr_assert(df2 != NULL);
    cr_assert(df_write_csv(df2, filename) == 0);
    compare_file_content(filename, lines);
    remove(filename);
    df_free(df2);
    df_free(df);
}
