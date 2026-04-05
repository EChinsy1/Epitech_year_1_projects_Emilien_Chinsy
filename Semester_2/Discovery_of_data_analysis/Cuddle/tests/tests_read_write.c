/*
** EPITECH PROJECT, 2026
** G2 - Discovery of Data Analysis - Cuddle - Alexis & Emilien
** File description:
** unit tests for the df_read_csv and df_write_csv function
*/

#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include "dataframe.h"
#include "unit_tests.h"

Test(df_read_csv, test_with_the_data_csv_file)
{
    dataframe_t *df = df_read_csv("tests/data.csv", ",");

    cr_assert(df != NULL);
    // check size
    cr_assert(df->nb_rows == 7);
    cr_assert(df->nb_columns == 3);
    // check column names
    cr_assert_str_eq(df->column_names[0], "name");
    cr_assert_str_eq(df->column_names[1], "age");
    cr_assert_str_eq(df->column_names[2], "city");
    cr_assert(df->column_names[3] == NULL);
    // check column types
    cr_assert(df->column_types[0] == STRING);
    cr_assert(df->column_types[1] == UINT);
    cr_assert(df->column_types[2] == STRING);
    // check data
    cr_assert(df->data != NULL);
    cr_assert(df->data[3] == NULL);
    //      check the name column
    cr_assert(df->data[0] != NULL);
    cr_assert_str_eq((char *)(df->data[0][0]), "Alice");
    cr_assert_str_eq((char *)(df->data[0][1]), "Bob");
    cr_assert_str_eq((char *)(df->data[0][2]), "Charlie");
    cr_assert_str_eq((char *)(df->data[0][3]), "Léo");
    cr_assert_str_eq((char *)(df->data[0][4]), "Nathan");
    cr_assert_str_eq((char *)(df->data[0][5]), "Alex");
    cr_assert_str_eq((char *)(df->data[0][6]), "Paul");
    cr_assert(df->data[0][7] == NULL);
    //      check the age column
    cr_assert(df->data[1] != NULL);
    cr_assert(*((unsigned int *)(df->data[1][0])) == 25);
    cr_assert(*((unsigned int *)(df->data[1][1])) == 30);
    cr_assert(*((unsigned int *)(df->data[1][2])) == 35);
    cr_assert(*((unsigned int *)(df->data[1][3])) == 25);
    cr_assert(*((unsigned int *)(df->data[1][4])) == 30);
    cr_assert(*((unsigned int *)(df->data[1][5])) == 35);
    cr_assert(*((unsigned int *)(df->data[1][6])) == 25);
    cr_assert(df->data[1][7] == NULL);
    //      check the city column
    cr_assert(df->data[2] != NULL);
    cr_assert_str_eq((char *)(df->data[2][0]), "Paris");
    cr_assert_str_eq((char *)(df->data[2][1]), "London");
    cr_assert_str_eq((char *)(df->data[2][2]), "Berlin");
    cr_assert_str_eq((char *)(df->data[2][3]), "Paris");
    cr_assert_str_eq((char *)(df->data[2][4]), "London");
    cr_assert_str_eq((char *)(df->data[2][5]), "Berlin");
    cr_assert_str_eq((char *)(df->data[2][6]), "Paris");
    cr_assert(df->data[2][7] == NULL);
    // check the separator
    cr_assert_str_eq(df->separator, ",");

    df_free(df);
}

Test(df_read_csv, test_with_the_data2_csv_file)
{
    dataframe_t *df = df_read_csv("tests/data2.csv", ",");

    cr_assert(df != NULL);
    // check size
    cr_assert(df->nb_rows == 3);
    cr_assert(df->nb_columns == 2);
    // check column names
    cr_assert_str_eq(df->column_names[0], "name");
    cr_assert_str_eq(df->column_names[1], "amount");
    cr_assert(df->column_names[2] == NULL);
    // check column types
    cr_assert(df->column_types[0] == STRING);
    cr_assert(df->column_types[1] == STRING);
    // check data
    cr_assert(df->data != NULL);
    cr_assert(df->data[2] == NULL);
    //      check the name column
    cr_assert(df->data[0] != NULL);
    cr_assert_str_eq(df->data[0][0], "Alice");
    cr_assert_str_eq(df->data[0][1], "Bob");
    cr_assert_str_eq(df->data[0][2], "Léo");
    cr_assert(df->data[0][3] == NULL);
    //      check the amount column
    cr_assert(df->data[1] != NULL);
    cr_assert_str_eq(df->data[1][0], "25e");
    cr_assert_str_eq(df->data[1][1], "30e");
    cr_assert_str_eq(df->data[1][2], "25e");
    cr_assert(df->data[1][3] == NULL);
    // check separator
    cr_assert_str_eq(df->separator, ",");

    df_free(df);
}

Test(df_write_csv, test_with_the_data_csv_file)
{
    const char *output_name = "tests/test_write1.csv";
    dataframe_t *df = df_read_csv("tests/data.csv", ",");
    FILE *file = NULL;
    char *buffer = NULL;
    size_t size = 0;
    char *lines[9] = {"name,age,city\n", "Alice,25,Paris\n", "Bob,30,London\n",
        "Charlie,35,Berlin\n", "Léo,25,Paris\n", "Nathan,30,London\n",
        "Alex,35,Berlin\n", "Paul,25,Paris\n", NULL};
    int i = 0;

    cr_assert(df_write_csv(df, output_name) == 0);
    df_free(df);
    file = fopen(output_name, "r");
    cr_assert(file != NULL);
    for (; getline(&buffer, &size, file) > 0; ++i) {
        cr_assert(lines[i] != NULL);
        cr_assert_str_eq(buffer, lines[i]);
    }
    free(buffer);
    fclose(file);
    remove(output_name);
    cr_assert(lines[i] == NULL);
}

Test(df_write_csv, test_with_the_data2_csv_file)
{
    const char *output_name = "tests/test_write2.csv";
    dataframe_t *df = df_read_csv("tests/data2.csv", ",");
    FILE *file = NULL;
    char *buffer = NULL;
    size_t size = 0;
    char *lines[5] = {"name,amount\n", "Alice,25e\n", "Bob,30e\n", "Léo,25e\n",
        NULL};
    int i = 0;

    cr_assert(df_write_csv(df, output_name) == 0);
    df_free(df);
    file = fopen(output_name, "r");
    cr_assert(file != NULL);
    for (; getline(&buffer, &size, file) > 0; ++i) {
        cr_assert(lines[i] != NULL);
        cr_assert_str_eq(buffer, lines[i]);
    }
    free(buffer);
    fclose(file);
    remove(output_name);
    cr_assert(lines[i] == NULL);
}

Test(df_read_csv, test_error_handling)
{
    dataframe_t *df = df_read_csv("tests/data.csv", ";");
    dataframe_t *df2 = df_read_csv("tests/data.csv", NULL);

    cr_assert(df2 != NULL);
    df_free(df);
    cr_assert(df_read_csv(NULL, ";") == NULL);
    cr_assert(df_read_csv("tests/data256.csv", ":") == NULL);
    df = df_read_csv("tests/data.csv", ";");

    cr_assert(df != NULL);
    cr_assert(df->nb_columns == 1);
    cr_assert(df->nb_rows == 7);
    cr_assert_str_eq(df->column_names[0], "name,age,city");
    cr_assert(df->column_names[1] == NULL);
    cr_assert(df->column_types[0] == STRING);
    // check data content
    cr_assert_str_eq((char *)(df->data[0][0]), "Alice,25,Paris");
    cr_assert_str_eq((char *)(df->data[0][1]), "Bob,30,London");
    cr_assert_str_eq((char *)(df->data[0][2]), "Charlie,35,Berlin");
    cr_assert_str_eq((char *)(df->data[0][3]), "Léo,25,Paris");
    cr_assert_str_eq((char *)(df->data[0][4]), "Nathan,30,London");
    cr_assert_str_eq((char *)(df->data[0][5]), "Alex,35,Berlin");
    cr_assert_str_eq((char *)(df->data[0][6]), "Paul,25,Paris");
    cr_assert(df->data[0][7] == NULL);
    cr_assert(df->data[1] == NULL);
    // check the separator and free
    cr_assert_str_eq(df->separator, ";");
    df_free(df);
}

Test(df_write_csv, test_error_handling)
{
    char *filename = "tests/error_handling.csv";
    dataframe_t *df = df_read_csv("tests/data.csv", ";");
    char *lines[9] = {"name,age,city\n", "Alice,25,Paris\n", "Bob,30,London\n",
        "Charlie,35,Berlin\n", "Léo,25,Paris\n", "Nathan,30,London\n",
        "Alex,35,Berlin\n", "Paul,25,Paris\n", NULL};

    cr_assert(df_write_csv(NULL, filename) == 1);
    cr_assert(df_write_csv(df, NULL) == 1);
    cr_assert(df_write_csv(df, filename) == 0);
    compare_file_content(filename, lines);
    df_free(df);
}
