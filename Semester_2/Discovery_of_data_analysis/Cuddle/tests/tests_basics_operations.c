/*
** EPITECH PROJECT, 2026
** G2 - Discovery of Data Analysis - Cuddle - Alexis & Emilien
** File description:
** unit tests for the df_info, df_shape, df_describe, df_head and df_tail
** functions
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include "dataframe.h"
#include "unit_tests.h"

Test(df_info, test_with_the_subject_example)
{
    dataframe_t *df = df_read_csv("tests/data.csv", ",");
    char *file_name = "tests/tests_output1";
    int fd = 0;
    char *lines[5] = {"3 columns:\n", "- name: string\n",
        "- age: unsigned int\n", "- city: string\n", NULL};

    cr_assert(df != NULL);
    fd = open(file_name, (O_WRONLY | O_CREAT), 0666);
    cr_assert(fd >= 0);
    cr_assert(dup2(fd, 1) >= 0);
    df_info(df);
    close(fd);
    df_free(df);
    compare_file_content(file_name, lines);
    remove(file_name);
}

Test(df_info, test_with_the_data2_csv_file, .init = cr_redirect_stdout)
{
    dataframe_t *df = df_read_csv("tests/data2.csv", ",");
    char *file_name = "tests/tests_output2";
    int fd = 0;
    char *lines[4] = {"2 columns:\n", "- name: string\n", "- amount: string\n",
        NULL};

    cr_assert(df != NULL);
    fd = open(file_name, (O_WRONLY | O_CREAT), 0666);
    cr_assert(fd >= 0);
    cr_assert(dup2(fd, 1) >= 0);
    df_info(df);
    close(fd);
    df_free(df);
    compare_file_content(file_name, lines);
    remove(file_name);
}

Test(df_info, test_with_the_data3_csv_file, .init = cr_redirect_stdout)
{
    dataframe_t *df = df_read_csv("tests/data3.csv", ",");
    char *file_name = "tests/tests_output3";
    int fd = 0;
    char *lines[9] = {"7 columns:\n", "- name: string\n",
        "- r: unsigned int\n", "- g: unsigned int\n", "- b: unsigned int\n",
        "- percent: float\n", "- is_hot: bool\n", "- coef: int\n", NULL};

    cr_assert(df != NULL);
    fd = open(file_name, (O_WRONLY | O_CREAT), 0666);
    cr_assert(fd >= 0);
    cr_assert(dup2(fd, 1) >= 0);
    df_info(df);
    close(fd);
    df_free(df);
    compare_file_content(file_name, lines);
    remove(file_name);
}

Test(df_shape, test_with_the_subject_example)
{
    dataframe_t *df = df_read_csv("tests/data.csv", ",");
    dataframe_shape_t shape;

    cr_assert(df != NULL);
    shape = df_shape(df);
    df_free(df);
    cr_assert(shape.nb_rows == 7);
    cr_assert(shape.nb_columns == 3);
}

Test(df_shape, test_with_the_data2_csv_file)
{
    dataframe_t *df = df_read_csv("tests/data2.csv", ",");
    dataframe_shape_t shape;

    cr_assert(df != NULL);
    shape = df_shape(df);
    df_free(df);
    cr_assert(shape.nb_rows == 3);
    cr_assert(shape.nb_columns == 2);
}

Test(df_describe, test_with_the_subject_example, .init = cr_redirect_stdout)
{
    dataframe_t *df = df_read_csv("tests/data.csv", ",");
    char *file_name = "tests/tests_output4";
    int fd = 0;
    char *lines[7] = {"Column: age\n", "Count: 7\n", "Mean: 29.29\n",
        "Std: 4.16\n", "Min: 25.00\n", "Max: 35.00\n", NULL};

    cr_assert(df != NULL);
    fd = open(file_name, (O_WRONLY | O_CREAT), 0666);
    cr_assert(fd >= 0);
    cr_assert(dup2(fd, 1) >= 0);
    df_describe(df);
    close(fd);
    df_free(df);
    compare_file_content(file_name, lines);
    remove(file_name);
}

Test(df_describe, test_with_the_data2_csv_file, .init = cr_redirect_stdout)
{
    dataframe_t *df = df_read_csv("tests/data2.csv", ",");
    char *file_name = "tests/tests_output5";
    int fd = 0;
    char *lines[1] = {NULL};

    cr_assert(df != NULL);
    fd = open(file_name, (O_CREAT | O_WRONLY), 0666);
    cr_assert(fd >= 0);
    cr_assert(dup2(fd, 1) >= 0);
    df_describe(df);
    close(fd);
    df_free(df);
    compare_file_content(file_name, lines);
    remove(file_name);
}

Test(df_head, test_with_the_subject_example)
{
    dataframe_t *df1 = df_read_csv("tests/data.csv", ",");
    dataframe_t *df2 = NULL;

    cr_assert(df1 != NULL);
    df2 = df_head(df1, 3);
    df_free(df1);
    cr_assert(df2 != NULL);
    // check size
    cr_assert(df2->nb_rows == 3);
    cr_assert(df2->nb_columns == 3);
    // check column names
    cr_assert_str_eq(df2->column_names[0], "name");
    cr_assert_str_eq(df2->column_names[1], "age");
    cr_assert_str_eq(df2->column_names[2], "city");
    cr_assert(df2->column_names[3] == NULL);
    // check column types
    cr_assert(df2->column_types[0] == STRING);
    cr_assert(df2->column_types[1] == UINT);
    cr_assert(df2->column_types[2] == STRING);
    // check data
    cr_assert(df2->data != NULL);
    cr_assert(df2->data[3] == NULL);
    //      check the name column
    cr_assert(df2->data[0] != NULL);
    cr_assert_str_eq(df2->data[0][0], "Alice");
    cr_assert_str_eq(df2->data[0][1], "Bob");
    cr_assert_str_eq(df2->data[0][2], "Charlie");
    cr_assert(df2->data[0][3] == NULL);
    //      check the age column
    cr_assert(df2->data[1] != NULL);
    cr_assert(*((unsigned int *)(df2->data[1][0])) == 25);
    cr_assert(*((unsigned int *)(df2->data[1][1])) == 30);
    cr_assert(*((unsigned int *)(df2->data[1][2])) == 35);
    cr_assert(df2->data[1][3] == NULL);
    //      check the city column
    cr_assert(df2->data[2] != NULL);
    cr_assert_str_eq(df2->data[2][0], "Paris");
    cr_assert_str_eq(df2->data[2][1], "London");
    cr_assert_str_eq(df2->data[2][2], "Berlin");
    cr_assert(df2->data[2][3] == NULL);
    // check the separator
    cr_assert_str_eq(df2->separator, ",");

    df_free(df2);
}

Test(df_head, head_with_five_lines)
{
    dataframe_t *df1 = df_read_csv("tests/data.csv", ",");
    dataframe_t *df2 = NULL;

    cr_assert(df1 != NULL);
    df2 = df_head(df1, 5);
    df_free(df1);
    cr_assert(df2 != NULL);
    // check size
    cr_assert(df2->nb_rows == 5);
    cr_assert(df2->nb_columns == 3);
    // check column names
    cr_assert_str_eq(df2->column_names[0], "name");
    cr_assert_str_eq(df2->column_names[1], "age");
    cr_assert_str_eq(df2->column_names[2], "city");
    cr_assert(df2->column_names[3] == NULL);
    // check column types
    cr_assert(df2->column_types[0] == STRING);
    cr_assert(df2->column_types[1] == UINT);
    cr_assert(df2->column_types[2] == STRING);
    // check data
    cr_assert(df2->data != NULL);
    cr_assert(df2->data[3] == NULL);
    //      check the name column
    cr_assert(df2->data[0] != NULL);
    cr_assert_str_eq(df2->data[0][0], "Alice");
    cr_assert_str_eq(df2->data[0][1], "Bob");
    cr_assert_str_eq(df2->data[0][2], "Charlie");
    cr_assert_str_eq(df2->data[0][3], "Léo");
    cr_assert_str_eq(df2->data[0][4], "Nathan");
    cr_assert(df2->data[0][5] == NULL);
    //      check the age column
    cr_assert(df2->data[1] != NULL);
    cr_assert(*((unsigned int *)(df2->data[1][0])) == 25);
    cr_assert(*((unsigned int *)(df2->data[1][1])) == 30);
    cr_assert(*((unsigned int *)(df2->data[1][2])) == 35);
    cr_assert(*((unsigned int *)(df2->data[1][3])) == 25);
    cr_assert(*((unsigned int *)(df2->data[1][4])) == 30);
    cr_assert(df2->data[1][5] == NULL);
    //      check the city column
    cr_assert(df2->data[2] != NULL);
    cr_assert_str_eq(df2->data[2][0], "Paris");
    cr_assert_str_eq(df2->data[2][1], "London");
    cr_assert_str_eq(df2->data[2][2], "Berlin");
    cr_assert_str_eq(df2->data[2][3], "Paris");
    cr_assert_str_eq(df2->data[2][4], "London");
    cr_assert(df2->data[2][5] == NULL);
    // check the separator
    cr_assert_str_eq(df2->separator, ",");

    df_free(df2);
}

Test(df_head, test_with_the_data2_csv_file)
{
    dataframe_t *df1 = df_read_csv("tests/data2.csv", ",");
    dataframe_t *df2 = NULL;

    cr_assert(df1 != NULL);
    df2 = df_head(df1, 2);
    df_free(df1);
    cr_assert(df2 != NULL);
    // check size
    cr_assert(df2->nb_rows == 2);
    cr_assert(df2->nb_columns == 2);
    // check column names
    cr_assert_str_eq(df2->column_names[0], "name");
    cr_assert_str_eq(df2->column_names[1], "amount");
    cr_assert(df2->column_names[2] == NULL);
    // check column types
    cr_assert(df2->column_types[0] == STRING);
    cr_assert(df2->column_types[1] == STRING);
    // check data
    cr_assert(df2->data != NULL);
    cr_assert(df2->data[2] == NULL);
    //      check the name column
    cr_assert(df2->data[0] != NULL);
    cr_assert_str_eq(df2->data[0][0], "Alice");
    cr_assert_str_eq(df2->data[0][1], "Bob");
    cr_assert(df2->data[0][2] == NULL);
    //      check the amount column
    cr_assert(df2->data[1] != NULL);
    cr_assert_str_eq(df2->data[1][0], "25e");
    cr_assert_str_eq(df2->data[1][1], "30e");
    cr_assert(df2->data[1][2] == NULL);
    // check the separator
    cr_assert_str_eq(df2->separator, ",");
}

Test(df_tail, test_with_the_subject_example)
{
    dataframe_t *df1 = df_read_csv("tests/data.csv", ",");
    dataframe_t *df2 = NULL;

    cr_assert(df1 != NULL);
    df2 = df_tail(df1, 3);
    df_free(df1);
    cr_assert(df2 != NULL);
    // check size
    cr_assert(df2->nb_rows == 3);
    cr_assert(df2->nb_columns == 3);
    // check column names
    cr_assert_str_eq(df2->column_names[0], "name");
    cr_assert_str_eq(df2->column_names[1], "age");
    cr_assert_str_eq(df2->column_names[2], "city");
    cr_assert(df2->column_names[3] == NULL);
    // check column types
    cr_assert(df2->column_types[0] == STRING);
    cr_assert(df2->column_types[1] == UINT);
    cr_assert(df2->column_types[2] == STRING);
    // check data
    cr_assert(df2->data != NULL);
    cr_assert(df2->data[3] == NULL);
    //      check the name column
    cr_assert(df2->data[0] != NULL);
    cr_assert_str_eq(df2->data[0][0], "Nathan");
    cr_assert_str_eq(df2->data[0][1], "Alex");
    cr_assert_str_eq(df2->data[0][2], "Paul");
    cr_assert(df2->data[0][3] == NULL);
    //      check the age column
    cr_assert(df2->data[1] != NULL);
    cr_assert(*((unsigned int *)(df2->data[1][0])) == 30);
    cr_assert(*((unsigned int *)(df2->data[1][1])) == 35);
    cr_assert(*((unsigned int *)(df2->data[1][2])) == 25);
    cr_assert(df2->data[1][3] == NULL);
    //      check the city column
    cr_assert(df2->data[2] != NULL);
    cr_assert_str_eq(df2->data[2][0], "London");
    cr_assert_str_eq(df2->data[2][1], "Berlin");
    cr_assert_str_eq(df2->data[2][2], "Paris");
    cr_assert(df2->data[2][3] == NULL);
    // check the separator
    cr_assert_str_eq(df2->separator, ",");

    df_free(df2);
}

Test(df_tail, test_with_the_data2_csv_file)
{
    dataframe_t *df1 = df_read_csv("tests/data2.csv", ",");
    dataframe_t *df2 = NULL;

    cr_assert(df1 != NULL);
    df2 = df_tail(df1, 2);
    df_free(df1);
    cr_assert(df2 != NULL);
    // check size
    cr_assert(df2->nb_rows == 2);
    cr_assert(df2->nb_columns == 2);
    // check column names
    cr_assert_str_eq(df2->column_names[0], "name");
    cr_assert_str_eq(df2->column_names[1], "amount");
    cr_assert(df2->column_names[2] == NULL);
    // check column types
    cr_assert(df2->column_types[0] == STRING);
    cr_assert(df2->column_types[1] == STRING);
    // check data
    cr_assert(df2->data != NULL);
    cr_assert(df2->data[2] == NULL);
    //      check the name column
    cr_assert(df2->data[0] != NULL);
    cr_assert_str_eq(df2->data[0][0], "Bob");
    cr_assert_str_eq(df2->data[0][1], "Léo");
    cr_assert(df2->data[0][2] == NULL);
    //      check the amount column
    cr_assert(df2->data[1] != NULL);
    cr_assert_str_eq(df2->data[1][0], "30e");
    cr_assert_str_eq(df2->data[1][1], "25e");
    cr_assert(df2->data[1][2] == NULL);
    // check the separator
    cr_assert_str_eq(df2->separator, ",");
}

Test(df_tail, tail_with_five_lines)
{
    dataframe_t *df1 = df_read_csv("tests/data.csv", ",");
    dataframe_t *df2 = NULL;

    cr_assert(df1 != NULL);
    df2 = df_tail(df1, 5);
    df_free(df1);
    cr_assert(df2 != NULL);
    // check size
    cr_assert(df2->nb_rows == 5);
    cr_assert(df2->nb_columns == 3);
    // check column names
    cr_assert_str_eq(df2->column_names[0], "name");
    cr_assert_str_eq(df2->column_names[1], "age");
    cr_assert_str_eq(df2->column_names[2], "city");
    cr_assert(df2->column_names[3] == NULL);
    // check column types
    cr_assert(df2->column_types[0] == STRING);
    cr_assert(df2->column_types[1] == UINT);
    cr_assert(df2->column_types[2] == STRING);
    // check data
    cr_assert(df2->data != NULL);
    cr_assert(df2->data[3] == NULL);
    //      check the name column
    cr_assert(df2->data[0] != NULL);
    cr_assert_str_eq(df2->data[0][0], "Charlie");
    cr_assert_str_eq(df2->data[0][1], "Léo");
    cr_assert_str_eq(df2->data[0][2], "Nathan");
    cr_assert_str_eq(df2->data[0][3], "Alex");
    cr_assert_str_eq(df2->data[0][4], "Paul");
    cr_assert(df2->data[0][5] == NULL);
    //      check the age column
    cr_assert(df2->data[1] != NULL);
    cr_assert(*((unsigned int *)(df2->data[1][0])) == 35);
    cr_assert(*((unsigned int *)(df2->data[1][1])) == 25);
    cr_assert(*((unsigned int *)(df2->data[1][2])) == 30);
    cr_assert(*((unsigned int *)(df2->data[1][3])) == 35);
    cr_assert(*((unsigned int *)(df2->data[1][4])) == 25);
    cr_assert(df2->data[1][5] == NULL);
    //      check the city column
    cr_assert(df2->data[2] != NULL);
    cr_assert_str_eq(df2->data[2][0], "Berlin");
    cr_assert_str_eq(df2->data[2][1], "Paris");
    cr_assert_str_eq(df2->data[2][2], "London");
    cr_assert_str_eq(df2->data[2][3], "Berlin");
    cr_assert_str_eq(df2->data[2][4], "Paris");
    cr_assert(df2->data[2][5] == NULL);
    // check the separator
    cr_assert_str_eq(df2->separator, ",");

    df_free(df2);
}
