/*
** EPITECH PROJECT, 2026
** G2 - Discovery of Data Analysis - Cuddle - Alexis & Emilien
** File description:
** unit tests for the df_groupby, df_apply, df_to_type, df_filter and df_sort
** functions
*/

#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "dataframe.h"

void compare_file_content(char *filename, char *expected[])
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
    char *new_value = strdup((char *)(value));

    if (new_value[0] != '\0')
        new_value[0] = 'T';
    return new_value;
}

static bool filter_func(void *value) {
    return *(unsigned int *)(value) > 30;
}

static bool sort_func(void *value1, void *value2) {
    return *(unsigned int *)(value1) > *(unsigned int *)(value2);
}

// unit tests

Test(df_groupby, test_groupby_of_the_subject)
{
    char *filename = "tests/grouped.csv";
    dataframe_t *df1 = df_read_csv("tests/data.csv", ",");
    dataframe_t *df2 = df_groupby(df1, "city", (const char *[]){"age", NULL},
        &agg_func);
    FILE *file = NULL;
    size_t size;
    char *buffer = NULL;
    int i = 0;
    char *lines[5] = {"city,age\n", "Paris,75\n", "London,60\n", "Berlin,70\n",
        NULL};

    df_free(df1);
    cr_assert(df2 != NULL);
    cr_assert(df_write_csv(df2, filename) == 0);
    file = fopen(filename, "r");
    cr_assert(file != NULL);
    for (; getline(&buffer, &size, file) > 0; ++i) {
        cr_assert(lines[i] != NULL);
        cr_assert_str_eq(buffer, lines[i]);
    }
    free(buffer);
    fclose(file);
    remove(filename);
    cr_assert(lines[i] == NULL);
}

Test(df_apply, test_apply_of_the_subject)
{
    char *filename = "tests/applied.csv";
    dataframe_t *df1 = df_read_csv("tests/data.csv", ",");
    dataframe_t *df2 = df_apply(df1, "age", &apply_func1);
    FILE *file = NULL;
    size_t size;
    char *buffer = NULL;
    int i = 0;
    char *lines[9] = {"name,age,city\n", "Alice,50,Paris\n", "Bob,60,London\n",
        "Charlie,70,Berlin\n", "Léo,50,Paris\n", "Nathan,60,London\n",
        "Alex,70,Berlin\n", "Paul,50,Paris\n", NULL};

    df_free(df1);
    cr_assert(df2 != NULL);
    cr_assert(df_write_csv(df2, filename) == 0);
    file = fopen(filename, "r");
    cr_assert(file != NULL);
    for (; getline(&buffer, &size, file) > 0; ++i) {
        cr_assert(lines[i] != NULL);
        cr_assert_str_eq(buffer, lines[i]);
    }
    free(buffer);
    fclose(file);
    remove(filename);
    cr_assert(lines[i] == NULL);
}

Test(df_apply, test_apply_with_the_data2_csv_file)
{
    char *filename = "tests/applied2.csv";
    dataframe_t *df1 = df_read_csv("tests/data2.csv", ",");
    dataframe_t *df2 = df_apply(df1, "name", &apply_func2);
    FILE *file = NULL;
    size_t size;
    char *buffer = NULL;
    int i = 0;
    char *lines[5] = {"name,amount\n", "Tlice,25e\n", "Tob,30e\n", "Téo,25e\n",
        NULL};

    df_free(df1);
    cr_assert(df2 != NULL);
    cr_assert(df_write_csv(df2, filename) == 0);
    file = fopen(filename, "r");
    cr_assert(file != NULL);
    for (; getline(&buffer, &size, file) > 0; ++i) {
        cr_assert(lines[i] != NULL);
        cr_assert_str_eq(buffer, lines[i]);
    }
    free(buffer);
    fclose(file);
    remove(filename);
    cr_assert(lines[i] == NULL);
}

Test(df_to_type, test_conversion_of_the_subject)
{
    char *filename = "tests/converted.csv";
    dataframe_t *df1 = df_read_csv("tests/data2.csv", ",");
    dataframe_t *df2 = df_to_type(df1, "amount", INT);
    char *lines[5] = {"name,amount\n", "Alice,25\n", "Bob,30\n", "Léo,25\n",
        NULL};

    df_free(df1);
    cr_assert(df2 != NULL);
    cr_assert(df2->column_types[0] == STRING);
    cr_assert(df2->column_types[1] == INT);
    cr_assert(df_write_csv(df2, filename) == 0);
    compare_file_content(filename, lines);
    remove(filename);
}

Test(df_to_type, test_conversion_with_the_data_csv_file)
{
    char *filename = "tests/converted2.csv";
    dataframe_t *df1 = df_read_csv("tests/data.csv", ",");
    dataframe_t *df2 = df_to_type(df1, "age", FLOAT);
    char *lines[9] = {"name,age,city\n", "Alice,25.000000,Paris\n",
        "Bob,30.000000,London\n", "Charlie,35.000000,Berlin\n",
        "Léo,25.000000,Paris\n", "Nathan,30.000000,London\n",
        "Alex,35.000000,Berlin\n", "Paul,25.000000,Paris\n", NULL};

    df_free(df1);
    cr_assert(df2 != NULL);
    cr_assert(df2->column_types[0] == STRING);
    cr_assert(df2->column_types[1] == FLOAT);
    cr_assert(df2->column_types[2] == STRING);
    cr_assert(df_write_csv(df2, filename) == 0);
    compare_file_content(filename, lines);
    remove(filename);
}

Test(df_to_type, test_conversion_from_bool_to_bool)
{
    char *filename = "tests/bool_to_bool.csv";
    dataframe_t *df1 = df_read_csv("tests/data3.csv", ",");
    dataframe_t *df2 = df_to_type(df1, "is_hot", BOOL);
    char *lines[8] = {"name,r,g,b,percent,is_hot,coef\n",
        "red,255,0,0,99.609381,true,3\n", "orange,255,128,0,99.804693,true,2\n",
        "yellow,255,255,0,99.998480,true,1\n",
        "green,0,255,0,0.389099,false,-1\n", "blue,0,0,255,0.001520,false,-2\n",
        "purple,255,0,255,99.610901,false,-3\n", NULL};

    df_free(df1);
    cr_assert(df2 != NULL);
    cr_assert(df2->column_types[0] == STRING);
    cr_assert(df2->column_types[1] == UINT);
    cr_assert(df2->column_types[2] == UINT);
    cr_assert(df2->column_types[3] == UINT);
    cr_assert(df2->column_types[4] == FLOAT);
    cr_assert(df2->column_types[5] == BOOL);
    cr_assert(df2->column_types[6] == INT);
    cr_assert(df_write_csv(df2, filename) == 0);
    compare_file_content(filename, lines);
    remove(filename);
    cr_assert(*((bool *)(df2->data[5][3])) == false);
    df_free(df2);
}

Test(df_to_type, test_conversion_from_bool_to_uint)
{
    char *filename = "tests/bool_to_uint.csv";
    dataframe_t *df1 = df_read_csv("tests/data3.csv", ",");
    dataframe_t *df2 = df_to_type(df1, "is_hot", UINT);
    char *lines[8] = {"name,r,g,b,percent,is_hot,coef\n",
        "red,255,0,0,99.609381,1,3\n", "orange,255,128,0,99.804693,1,2\n",
        "yellow,255,255,0,99.998480,1,1\n",
        "green,0,255,0,0.389099,0,-1\n", "blue,0,0,255,0.001520,0,-2\n",
        "purple,255,0,255,99.610901,0,-3\n", NULL};

    df_free(df1);
    cr_assert(df2 != NULL);
    cr_assert(df2->column_types[0] == STRING);
    cr_assert(df2->column_types[1] == UINT);
    cr_assert(df2->column_types[2] == UINT);
    cr_assert(df2->column_types[3] == UINT);
    cr_assert(df2->column_types[4] == FLOAT);
    cr_assert(df2->column_types[5] == UINT);
    cr_assert(df2->column_types[6] == INT);
    cr_assert(df_write_csv(df2, filename) == 0);
    compare_file_content(filename, lines);
    remove(filename);
    cr_assert(*((unsigned int *)(df2->data[5][3])) == 0);
    df_free(df2);
}

Test(df_to_type, test_conversion_from_bool_to_int)
{
    char *filename = "tests/bool_to_int.csv";
    dataframe_t *df1 = df_read_csv("tests/data3.csv", ",");
    dataframe_t *df2 = df_to_type(df1, "is_hot", INT);
    char *lines[8] = {"name,r,g,b,percent,is_hot,coef\n",
        "red,255,0,0,99.609381,1,3\n", "orange,255,128,0,99.804693,1,2\n",
        "yellow,255,255,0,99.998480,1,1\n",
        "green,0,255,0,0.389099,0,-1\n", "blue,0,0,255,0.001520,0,-2\n",
        "purple,255,0,255,99.610901,0,-3\n", NULL};

    df_free(df1);
    cr_assert(df2 != NULL);
    cr_assert(df2->column_types[0] == STRING);
    cr_assert(df2->column_types[1] == UINT);
    cr_assert(df2->column_types[2] == UINT);
    cr_assert(df2->column_types[3] == UINT);
    cr_assert(df2->column_types[4] == FLOAT);
    cr_assert(df2->column_types[5] == INT);
    cr_assert(df2->column_types[6] == INT);
    cr_assert(df_write_csv(df2, filename) == 0);
    compare_file_content(filename, lines);
    remove(filename);
    cr_assert(*((int *)(df2->data[5][3])) == 0);
    df_free(df2);
}

Test(df_to_type, test_conversion_from_bool_to_float)
{
    char *filename = "tests/bool_to_float.csv";
    dataframe_t *df1 = df_read_csv("tests/data3.csv", ",");
    dataframe_t *df2 = df_to_type(df1, "is_hot", FLOAT);
    char *lines[8] = {"name,r,g,b,percent,is_hot,coef\n",
        "red,255,0,0,99.609381,1.000000,3\n",
        "orange,255,128,0,99.804693,1.000000,2\n",
        "yellow,255,255,0,99.998480,1.000000,1\n",
        "green,0,255,0,0.389099,0.000000,-1\n",
        "blue,0,0,255,0.001520,0.000000,-2\n",
        "purple,255,0,255,99.610901,0.000000,-3\n", NULL};

    df_free(df1);
    cr_assert(df2 != NULL);
    cr_assert(df2->column_types[0] == STRING);
    cr_assert(df2->column_types[1] == UINT);
    cr_assert(df2->column_types[2] == UINT);
    cr_assert(df2->column_types[3] == UINT);
    cr_assert(df2->column_types[4] == FLOAT);
    cr_assert(df2->column_types[5] == FLOAT);
    cr_assert(df2->column_types[6] == INT);
    cr_assert(df_write_csv(df2, filename) == 0);
    compare_file_content(filename, lines);
    remove(filename);
    cr_assert(*((double *)(df2->data[5][3])) == 0.0);
    df_free(df2);
}

Test(df_to_type, test_conversion_from_bool_to_string)
{
    char *filename = "tests/bool_to_str.csv";
    dataframe_t *df1 = df_read_csv("tests/data3.csv", ",");
    dataframe_t *df2 = df_to_type(df1, "is_hot", STRING);
    char *lines[8] = {"name,r,g,b,percent,is_hot,coef\n",
        "red,255,0,0,99.609381,true,3\n", "orange,255,128,0,99.804693,true,2\n",
        "yellow,255,255,0,99.998480,true,1\n",
        "green,0,255,0,0.389099,false,-1\n", "blue,0,0,255,0.001520,false,-2\n",
        "purple,255,0,255,99.610901,false,-3\n", NULL};

    df_free(df1);
    cr_assert(df2 != NULL);
    cr_assert(df2->column_types[0] == STRING);
    cr_assert(df2->column_types[1] == UINT);
    cr_assert(df2->column_types[2] == UINT);
    cr_assert(df2->column_types[3] == UINT);
    cr_assert(df2->column_types[4] == FLOAT);
    cr_assert(df2->column_types[5] == STRING);
    cr_assert(df2->column_types[6] == INT);
    cr_assert(df_write_csv(df2, filename) == 0);
    compare_file_content(filename, lines);
    remove(filename);
    cr_assert_str_eq((char *)(df2->data[5][3]), "false");
    df_free(df2);
}

Test(df_to_type, test_conversion_from_uint_to_bool)
{
    char *filename = "tests/bool_to_bool.csv";
    dataframe_t *df1 = df_read_csv("tests/data3.csv", ",");
    dataframe_t *df2 = df_to_type(df1, "g", BOOL);
    char *lines[8] = {"name,r,g,b,percent,is_hot,coef\n",
        "red,255,false,0,99.609381,true,3\n",
        "orange,255,true,0,99.804693,true,2\n",
        "yellow,255,true,0,99.998480,true,1\n",
        "green,0,true,0,0.389099,false,-1\n",
        "blue,0,false,255,0.001520,false,-2\n",
        "purple,255,false,255,99.610901,false,-3\n", NULL};

    df_free(df1);
    cr_assert(df2 != NULL);
    cr_assert(df2->column_types[0] == STRING);
    cr_assert(df2->column_types[1] == UINT);
    cr_assert(df2->column_types[2] == BOOL);
    cr_assert(df2->column_types[3] == UINT);
    cr_assert(df2->column_types[4] == FLOAT);
    cr_assert(df2->column_types[5] == BOOL);
    cr_assert(df2->column_types[6] == INT);
    cr_assert(df_write_csv(df2, filename) == 0);
    compare_file_content(filename, lines);
    remove(filename);
    cr_assert(*((bool *)(df2->data[2][3])) == true);
    df_free(df2);
}

Test(df_to_type, test_conversion_from_uint_to_uint)
{
    char *filename = "tests/uint_to_uint.csv";
    dataframe_t *df1 = df_read_csv("tests/data3.csv", ",");
    dataframe_t *df2 = df_to_type(df1, "g", UINT);
    char *lines[8] = {"name,r,g,b,percent,is_hot,coef\n",
        "red,255,0,0,99.609381,true,3\n", "orange,255,128,0,99.804693,true,2\n",
        "yellow,255,255,0,99.998480,true,1\n",
        "green,0,255,0,0.389099,false,-1\n", "blue,0,0,255,0.001520,false,-2\n",
        "purple,255,0,255,99.610901,false,-3\n", NULL};

    df_free(df1);
    cr_assert(df2 != NULL);
    cr_assert(df2->column_types[0] == STRING);
    cr_assert(df2->column_types[1] == UINT);
    cr_assert(df2->column_types[2] == UINT);
    cr_assert(df2->column_types[3] == UINT);
    cr_assert(df2->column_types[4] == FLOAT);
    cr_assert(df2->column_types[5] == BOOL);
    cr_assert(df2->column_types[6] == INT);
    cr_assert(df_write_csv(df2, filename) == 0);
    compare_file_content(filename, lines);
    remove(filename);
    cr_assert(*((unsigned int *)(df2->data[2][3])) == 255);
    df_free(df2);
}

Test(df_to_type, test_conversion_from_uint_to_int)
{
    char *filename = "tests/uint_to_int.csv";
    dataframe_t *df1 = df_read_csv("tests/data3.csv", ",");
    dataframe_t *df2 = df_to_type(df1, "g", INT);
    char *lines[8] = {"name,r,g,b,percent,is_hot,coef\n",
        "red,255,0,0,99.609381,true,3\n", "orange,255,128,0,99.804693,true,2\n",
        "yellow,255,255,0,99.998480,true,1\n",
        "green,0,255,0,0.389099,false,-1\n", "blue,0,0,255,0.001520,false,-2\n",
        "purple,255,0,255,99.610901,false,-3\n", NULL};

    df_free(df1);
    cr_assert(df2 != NULL);
    cr_assert(df2->column_types[0] == STRING);
    cr_assert(df2->column_types[1] == UINT);
    cr_assert(df2->column_types[2] == INT);
    cr_assert(df2->column_types[3] == UINT);
    cr_assert(df2->column_types[4] == FLOAT);
    cr_assert(df2->column_types[5] == BOOL);
    cr_assert(df2->column_types[6] == INT);
    cr_assert(df_write_csv(df2, filename) == 0);
    compare_file_content(filename, lines);
    remove(filename);
    cr_assert(*((int *)(df2->data[2][3])) == 255);
    df_free(df2);
}

Test(df_to_type, test_conversion_from_uint_to_float)
{
    char *filename = "tests/uint_to_float.csv";
    dataframe_t *df1 = df_read_csv("tests/data3.csv", ",");
    dataframe_t *df2 = df_to_type(df1, "g", FLOAT);
    char *lines[8] = {"name,r,g,b,percent,is_hot,coef\n",
        "red,255,0.000000,0,99.609381,true,3\n",
        "orange,255,128.000000,0,99.804693,true,2\n",
        "yellow,255,255.000000,0,99.998480,true,1\n",
        "green,0,255.000000,0,0.389099,false,-1\n",
        "blue,0,0.000000,255,0.001520,false,-2\n",
        "purple,255,0.000000,255,99.610901,false,-3\n", NULL};

    df_free(df1);
    cr_assert(df2 != NULL);
    cr_assert(df2->column_types[0] == STRING);
    cr_assert(df2->column_types[1] == UINT);
    cr_assert(df2->column_types[2] == FLOAT);
    cr_assert(df2->column_types[3] == UINT);
    cr_assert(df2->column_types[4] == FLOAT);
    cr_assert(df2->column_types[5] == BOOL);
    cr_assert(df2->column_types[6] == INT);
    cr_assert(df_write_csv(df2, filename) == 0);
    compare_file_content(filename, lines);
    remove(filename);
    cr_assert(*((double *)(df2->data[2][3])) == 255.0);
    df_free(df2);
}

Test(df_to_type, test_conversion_from_uint_to_string)
{
    char *filename = "tests/uint_to_str.csv";
    dataframe_t *df1 = df_read_csv("tests/data3.csv", ",");
    dataframe_t *df2 = df_to_type(df1, "g", STRING);
    char *lines[8] = {"name,r,g,b,percent,is_hot,coef\n",
        "red,255,0,0,99.609381,true,3\n", "orange,255,128,0,99.804693,true,2\n",
        "yellow,255,255,0,99.998480,true,1\n",
        "green,0,255,0,0.389099,false,-1\n", "blue,0,0,255,0.001520,false,-2\n",
        "purple,255,0,255,99.610901,false,-3\n", NULL};

    df_free(df1);
    cr_assert(df2 != NULL);
    cr_assert(df2->column_types[0] == STRING);
    cr_assert(df2->column_types[1] == UINT);
    cr_assert(df2->column_types[2] == STRING);
    cr_assert(df2->column_types[3] == UINT);
    cr_assert(df2->column_types[4] == FLOAT);
    cr_assert(df2->column_types[5] == BOOL);
    cr_assert(df2->column_types[6] == INT);
    cr_assert(df_write_csv(df2, filename) == 0);
    compare_file_content(filename, lines);
    remove(filename);
    cr_assert_str_eq((char *)(df2->data[2][3]), "255");
    df_free(df2);
}

Test(df_to_type, test_conversion_from_int_to_bool)
{
    char *filename = "tests/int_to_bool.csv";
    dataframe_t *df1 = df_read_csv("tests/data3.csv", ",");
    dataframe_t *df2 = df_to_type(df1, "coef", BOOL);
    char *lines[8] = {"name,r,g,b,percent,is_hot,coef\n",
        "red,255,0,0,99.609381,true,true\n",
        "orange,255,128,0,99.804693,true,true\n",
        "yellow,255,255,0,99.998480,true,true\n",
        "green,0,255,0,0.389099,false,true\n",
        "blue,0,0,255,0.001520,false,true\n",
        "purple,255,0,255,99.610901,false,true\n", NULL};

    df_free(df1);
    cr_assert(df2 != NULL);
    cr_assert(df2->column_types[0] == STRING);
    cr_assert(df2->column_types[1] == UINT);
    cr_assert(df2->column_types[2] == UINT);
    cr_assert(df2->column_types[3] == UINT);
    cr_assert(df2->column_types[4] == FLOAT);
    cr_assert(df2->column_types[5] == BOOL);
    cr_assert(df2->column_types[6] == BOOL);
    cr_assert(df_write_csv(df2, filename) == 0);
    compare_file_content(filename, lines);
    remove(filename);
    cr_assert(*((bool *)(df2->data[6][3])) == true);
    df_free(df2);
}

Test(df_to_type, test_conversion_from_int_to_uint_without_error)
{
    char *filename = "tests/int_to_uint.csv";
    dataframe_t *df1 = df_read_csv("tests/data3.csv", ",");
    dataframe_t *df3 = df_to_type(df1, "g", INT);
    dataframe_t *df2 = df_to_type(df3, "g", UINT);
    char *lines[8] = {"name,r,g,b,percent,is_hot,coef\n",
        "red,255,0,0,99.609381,true,3\n", "orange,255,128,0,99.804693,true,2\n",
        "yellow,255,255,0,99.998480,true,1\n",
        "green,0,255,0,0.389099,false,-1\n", "blue,0,0,255,0.001520,false,-2\n",
        "purple,255,0,255,99.610901,false,-3\n", NULL};

    df_free(df1);
    df_free(df3);
    cr_assert(df2 != NULL);
    cr_assert(df2->column_types[0] == STRING);
    cr_assert(df2->column_types[1] == UINT);
    cr_assert(df2->column_types[2] == UINT);
    cr_assert(df2->column_types[3] == UINT);
    cr_assert(df2->column_types[4] == FLOAT);
    cr_assert(df2->column_types[5] == BOOL);
    cr_assert(df2->column_types[6] == INT);
    cr_assert(df_write_csv(df2, filename) == 0);
    compare_file_content(filename, lines);
    remove(filename);
    cr_assert(*((unsigned int *)(df2->data[2][3])) == 255);
    df_free(df2);
}

Test(df_to_type, test_conversion_from_int_to_uint_with_error)
{
    dataframe_t *df1 = df_read_csv("tests/data3.csv", ",");
    dataframe_t *df2 = df_to_type(df1, "coef", UINT);

    df_write_csv(df2, "tests/error.csv");
    df_free(df1);
    cr_assert(df2 == NULL);
}

Test(df_to_type, test_conversion_from_int_to_int)
{
    char *filename = "tests/int_to_int.csv";
    dataframe_t *df1 = df_read_csv("tests/data3.csv", ",");
    dataframe_t *df2 = df_to_type(df1, "coef", INT);
    char *lines[8] = {"name,r,g,b,percent,is_hot,coef\n",
        "red,255,0,0,99.609381,true,3\n", "orange,255,128,0,99.804693,true,2\n",
        "yellow,255,255,0,99.998480,true,1\n",
        "green,0,255,0,0.389099,false,-1\n", "blue,0,0,255,0.001520,false,-2\n",
        "purple,255,0,255,99.610901,false,-3\n", NULL};

    df_free(df1);
    cr_assert(df2 != NULL);
    cr_assert(df2->column_types[0] == STRING);
    cr_assert(df2->column_types[1] == UINT);
    cr_assert(df2->column_types[2] == UINT);
    cr_assert(df2->column_types[3] == UINT);
    cr_assert(df2->column_types[4] == FLOAT);
    cr_assert(df2->column_types[5] == BOOL);
    cr_assert(df2->column_types[6] == INT);
    cr_assert(df_write_csv(df2, filename) == 0);
    compare_file_content(filename, lines);
    remove(filename);
    cr_assert(*((int *)(df2->data[6][3])) == -1);
    df_free(df2);
}

Test(df_to_type, test_conversion_from_int_to_float)
{
    char *filename = "tests/int_to_float.csv";
    dataframe_t *df1 = df_read_csv("tests/data3.csv", ",");
    dataframe_t *df2 = df_to_type(df1, "coef", FLOAT);
    char *lines[8] = {"name,r,g,b,percent,is_hot,coef\n",
        "red,255,0,0,99.609381,true,3.000000\n",
        "orange,255,128,0,99.804693,true,2.000000\n",
        "yellow,255,255,0,99.998480,true,1.000000\n",
        "green,0,255,0,0.389099,false,-1.000000\n",
        "blue,0,0,255,0.001520,false,-2.000000\n",
        "purple,255,0,255,99.610901,false,-3.000000\n", NULL};

    df_free(df1);
    cr_assert(df2 != NULL);
    cr_assert(df2->column_types[0] == STRING);
    cr_assert(df2->column_types[1] == UINT);
    cr_assert(df2->column_types[2] == UINT);
    cr_assert(df2->column_types[3] == UINT);
    cr_assert(df2->column_types[4] == FLOAT);
    cr_assert(df2->column_types[5] == BOOL);
    cr_assert(df2->column_types[6] == FLOAT);
    cr_assert(df_write_csv(df2, filename) == 0);
    compare_file_content(filename, lines);
    remove(filename);
    cr_assert(*((double *)(df2->data[6][3])) == -1.0);
    df_free(df2);
}

Test(df_to_type, test_conversion_from_int_to_string)
{
    char *filename = "tests/int_to_str.csv";
    dataframe_t *df1 = df_read_csv("tests/data3.csv", ",");
    dataframe_t *df2 = df_to_type(df1, "coef", STRING);
    char *lines[8] = {"name,r,g,b,percent,is_hot,coef\n",
        "red,255,0,0,99.609381,true,3\n", "orange,255,128,0,99.804693,true,2\n",
        "yellow,255,255,0,99.998480,true,1\n",
        "green,0,255,0,0.389099,false,-1\n", "blue,0,0,255,0.001520,false,-2\n",
        "purple,255,0,255,99.610901,false,-3\n", NULL};

    df_free(df1);
    cr_assert(df2 != NULL);
    cr_assert(df2->column_types[0] == STRING);
    cr_assert(df2->column_types[1] == UINT);
    cr_assert(df2->column_types[2] == UINT);
    cr_assert(df2->column_types[3] == UINT);
    cr_assert(df2->column_types[4] == FLOAT);
    cr_assert(df2->column_types[5] == BOOL);
    cr_assert(df2->column_types[6] == STRING);
    cr_assert(df_write_csv(df2, filename) == 0);
    compare_file_content(filename, lines);
    remove(filename);
    cr_assert_str_eq((char *)(df2->data[6][3]), "-1");
    df_free(df2);
}

Test(df_to_type, test_conversion_from_float_to_bool)
{
    char *filename = "tests/bool_to_bool.csv";
    dataframe_t *df1 = df_read_csv("tests/data3.csv", ",");
    dataframe_t *df2 = df_to_type(df1, "percent", BOOL);
    char *lines[8] = {"name,r,g,b,percent,is_hot,coef\n",
        "red,255,0,0,true,true,3\n", "orange,255,128,0,true,true,2\n",
        "yellow,255,255,0,true,true,1\n", "green,0,255,0,true,false,-1\n",
        "blue,0,0,255,true,false,-2\n", "purple,255,0,255,true,false,-3\n",
        NULL};

    df_free(df1);
    cr_assert(df2 != NULL);
    cr_assert(df2->column_types[0] == STRING);
    cr_assert(df2->column_types[1] == UINT);
    cr_assert(df2->column_types[2] == UINT);
    cr_assert(df2->column_types[3] == UINT);
    cr_assert(df2->column_types[4] == BOOL);
    cr_assert(df2->column_types[5] == BOOL);
    cr_assert(df2->column_types[6] == INT);
    cr_assert(df_write_csv(df2, filename) == 0);
    compare_file_content(filename, lines);
    remove(filename);
    cr_assert(*((bool *)(df2->data[4][3])) == true);
    df_free(df2);
}

Test(df_to_type, test_conversion_from_float_to_uint)
{
    char *filename = "tests/float_to_uint.csv";
    dataframe_t *df1 = df_read_csv("tests/data3.csv", ",");
    dataframe_t *df2 = df_to_type(df1, "percent", UINT);
    char *lines[8] = {"name,r,g,b,percent,is_hot,coef\n",
        "red,255,0,0,100,true,3\n", "orange,255,128,0,100,true,2\n",
        "yellow,255,255,0,100,true,1\n",
        "green,0,255,0,0,false,-1\n", "blue,0,0,255,0,false,-2\n",
        "purple,255,0,255,100,false,-3\n", NULL};

    df_free(df1);
    cr_assert(df2 != NULL);
    cr_assert(df2->column_types[0] == STRING);
    cr_assert(df2->column_types[1] == UINT);
    cr_assert(df2->column_types[2] == UINT);
    cr_assert(df2->column_types[3] == UINT);
    cr_assert(df2->column_types[4] == UINT);
    cr_assert(df2->column_types[5] == BOOL);
    cr_assert(df2->column_types[6] == INT);
    cr_assert(df_write_csv(df2, filename) == 0);
    compare_file_content(filename, lines);
    remove(filename);
    cr_assert(*((unsigned int *)(df2->data[4][3])) == 0);
    df_free(df2);
}

Test(df_to_type, test_conversion_from_float_to_int)
{
    char *filename = "tests/float_to_int.csv";
    dataframe_t *df1 = df_read_csv("tests/data3.csv", ",");
    dataframe_t *df2 = df_to_type(df1, "percent", INT);
    char *lines[8] = {"name,r,g,b,percent,is_hot,coef\n",
        "red,255,0,0,100,true,3\n", "orange,255,128,0,100,true,2\n",
        "yellow,255,255,0,100,true,1\n",
        "green,0,255,0,0,false,-1\n", "blue,0,0,255,0,false,-2\n",
        "purple,255,0,255,100,false,-3\n", NULL};

    df_free(df1);
    cr_assert(df2 != NULL);
    cr_assert(df2->column_types[0] == STRING);
    cr_assert(df2->column_types[1] == UINT);
    cr_assert(df2->column_types[2] == UINT);
    cr_assert(df2->column_types[3] == UINT);
    cr_assert(df2->column_types[4] == INT);
    cr_assert(df2->column_types[5] == BOOL);
    cr_assert(df2->column_types[6] == INT);
    cr_assert(df_write_csv(df2, filename) == 0);
    compare_file_content(filename, lines);
    remove(filename);
    cr_assert(*((int *)(df2->data[4][3])) == 0);
    df_free(df2);
}

Test(df_to_type, test_conversion_from_float_to_float)
{
    char *filename = "tests/float_to_float.csv";
    dataframe_t *df1 = df_read_csv("tests/data3.csv", ",");
    dataframe_t *df2 = df_to_type(df1, "percent", FLOAT);
    char *lines[8] = {"name,r,g,b,percent,is_hot,coef\n",
        "red,255,0,0,99.609381,true,3\n", "orange,255,128,0,99.804693,true,2\n",
        "yellow,255,255,0,99.998480,true,1\n",
        "green,0,255,0,0.389099,false,-1\n", "blue,0,0,255,0.001520,false,-2\n",
        "purple,255,0,255,99.610901,false,-3\n", NULL};

    df_free(df1);
    cr_assert(df2 != NULL);
    cr_assert(df2->column_types[0] == STRING);
    cr_assert(df2->column_types[1] == UINT);
    cr_assert(df2->column_types[2] == UINT);
    cr_assert(df2->column_types[3] == UINT);
    cr_assert(df2->column_types[4] == FLOAT);
    cr_assert(df2->column_types[5] == BOOL);
    cr_assert(df2->column_types[6] == INT);
    cr_assert(df_write_csv(df2, filename) == 0);
    compare_file_content(filename, lines);
    remove(filename);
    cr_assert(*((double *)(df2->data[4][3])) == 0.389099);
    df_free(df2);
}

Test(df_to_type, test_conversion_from_float_to_string)
{
    char *filename = "tests/float_to_str.csv";
    dataframe_t *df1 = df_read_csv("tests/data3.csv", ",");
    dataframe_t *df2 = df_to_type(df1, "percent", STRING);
    char *lines[8] = {"name,r,g,b,percent,is_hot,coef\n",
        "red,255,0,0,99.609381,true,3\n", "orange,255,128,0,99.804693,true,2\n",
        "yellow,255,255,0,99.998480,true,1\n",
        "green,0,255,0,0.389099,false,-1\n", "blue,0,0,255,0.001520,false,-2\n",
        "purple,255,0,255,99.610901,false,-3\n", NULL};

    df_free(df1);
    cr_assert(df2 != NULL);
    cr_assert(df2->column_types[0] == STRING);
    cr_assert(df2->column_types[1] == UINT);
    cr_assert(df2->column_types[2] == UINT);
    cr_assert(df2->column_types[3] == UINT);
    cr_assert(df2->column_types[4] == STRING);
    cr_assert(df2->column_types[5] == BOOL);
    cr_assert(df2->column_types[6] == INT);
    cr_assert(df_write_csv(df2, filename) == 0);
    compare_file_content(filename, lines);
    remove(filename);
    cr_assert_str_eq((char *)(df2->data[4][3]), "0.389099");
    df_free(df2);
}

Test(df_to_type, test_conversion_from_string_to_bool)
{
    char *filename = "tests/bool_to_bool.csv";
    dataframe_t *df1 = df_read_csv("tests/data3.csv", ",");
    dataframe_t *df3 = df_to_type(df1, "is_hot", STRING);
    dataframe_t *df2 = df_to_type(df3, "is_hot", BOOL);
    char *lines[8] = {"name,r,g,b,percent,is_hot,coef\n",
        "red,255,0,0,99.609381,true,3\n", "orange,255,128,0,99.804693,true,2\n",
        "yellow,255,255,0,99.998480,true,1\n",
        "green,0,255,0,0.389099,false,-1\n", "blue,0,0,255,0.001520,false,-2\n",
        "purple,255,0,255,99.610901,false,-3\n", NULL};

    df_free(df1);
    df_free(df3);
    cr_assert(df2 != NULL);
    cr_assert(df2->column_types[0] == STRING);
    cr_assert(df2->column_types[1] == UINT);
    cr_assert(df2->column_types[2] == UINT);
    cr_assert(df2->column_types[3] == UINT);
    cr_assert(df2->column_types[4] == FLOAT);
    cr_assert(df2->column_types[5] == BOOL);
    cr_assert(df2->column_types[6] == INT);
    cr_assert(df_write_csv(df2, filename) == 0);
    compare_file_content(filename, lines);
    remove(filename);
    cr_assert(*((bool *)(df2->data[5][3])) == false);
    df_free(df2);
}

Test(df_to_type, test_conversion_from_string_to_uint)
{
    char *filename = "tests/str_to_uint.csv";
    dataframe_t *df1 = df_read_csv("tests/data3.csv", ",");
    dataframe_t *df3 = df_to_type(df1, "g", STRING);
    dataframe_t *df2 = df_to_type(df3, "g", UINT);
    char *lines[8] = {"name,r,g,b,percent,is_hot,coef\n",
        "red,255,0,0,99.609381,true,3\n", "orange,255,128,0,99.804693,true,2\n",
        "yellow,255,255,0,99.998480,true,1\n",
        "green,0,255,0,0.389099,false,-1\n", "blue,0,0,255,0.001520,false,-2\n",
        "purple,255,0,255,99.610901,false,-3\n", NULL};

    df_free(df1);
    df_free(df3);
    cr_assert(df2 != NULL);
    cr_assert(df2->column_types[0] == STRING);
    cr_assert(df2->column_types[1] == UINT);
    cr_assert(df2->column_types[2] == UINT);
    cr_assert(df2->column_types[3] == UINT);
    cr_assert(df2->column_types[4] == FLOAT);
    cr_assert(df2->column_types[5] == BOOL);
    cr_assert(df2->column_types[6] == INT);
    cr_assert(df_write_csv(df2, filename) == 0);
    compare_file_content(filename, lines);
    remove(filename);
    cr_assert(*((unsigned int *)(df2->data[2][3])) == 255);
    df_free(df2);
}

Test(df_to_type, test_conversion_from_string_to_int)
{
    char *filename = "tests/str_to_int.csv";
    dataframe_t *df1 = df_read_csv("tests/data3.csv", ",");
    dataframe_t *df3 = df_to_type(df1, "coef", STRING);
    dataframe_t *df2 = df_to_type(df3, "coef", INT);
    char *lines[8] = {"name,r,g,b,percent,is_hot,coef\n",
        "red,255,0,0,99.609381,true,3\n", "orange,255,128,0,99.804693,true,2\n",
        "yellow,255,255,0,99.998480,true,1\n",
        "green,0,255,0,0.389099,false,-1\n", "blue,0,0,255,0.001520,false,-2\n",
        "purple,255,0,255,99.610901,false,-3\n", NULL};

    df_free(df1);
    df_free(df3);
    cr_assert(df2 != NULL);
    cr_assert(df2->column_types[0] == STRING);
    cr_assert(df2->column_types[1] == UINT);
    cr_assert(df2->column_types[2] == UINT);
    cr_assert(df2->column_types[3] == UINT);
    cr_assert(df2->column_types[4] == FLOAT);
    cr_assert(df2->column_types[5] == BOOL);
    cr_assert(df2->column_types[6] == INT);
    cr_assert(df_write_csv(df2, filename) == 0);
    compare_file_content(filename, lines);
    remove(filename);
    cr_assert(*((int *)(df2->data[6][3])) == -1);
    df_free(df2);
}

Test(df_to_type, test_conversion_from_string_to_float)
{
    char *filename = "tests/str_to_float.csv";
    dataframe_t *df1 = df_read_csv("tests/data3.csv", ",");
    dataframe_t *df3 = df_to_type(df1, "percent", STRING);
    dataframe_t *df2 = df_to_type(df3, "percent", FLOAT);
    char *lines[8] = {"name,r,g,b,percent,is_hot,coef\n",
        "red,255,0,0,99.609381,true,3\n", "orange,255,128,0,99.804693,true,2\n",
        "yellow,255,255,0,99.998480,true,1\n",
        "green,0,255,0,0.389099,false,-1\n", "blue,0,0,255,0.001520,false,-2\n",
        "purple,255,0,255,99.610901,false,-3\n", NULL};

    df_free(df1);
    df_free(df3);
    cr_assert(df2 != NULL);
    cr_assert(df2->column_types[0] == STRING);
    cr_assert(df2->column_types[1] == UINT);
    cr_assert(df2->column_types[2] == UINT);
    cr_assert(df2->column_types[3] == UINT);
    cr_assert(df2->column_types[4] == FLOAT);
    cr_assert(df2->column_types[5] == BOOL);
    cr_assert(df2->column_types[6] == INT);
    cr_assert(df_write_csv(df2, filename) == 0);
    compare_file_content(filename, lines);
    remove(filename);
    cr_assert(*((double *)(df2->data[4][3])) == 0.389099);
    df_free(df2);
}

Test(df_to_type, test_conversion_from_string_to_string)
{
    char *filename = "tests/str_to_str.csv";
    dataframe_t *df1 = df_read_csv("tests/data3.csv", ",");
    dataframe_t *df2 = df_to_type(df1, "name", STRING);
    char *lines[8] = {"name,r,g,b,percent,is_hot,coef\n",
        "red,255,0,0,99.609381,true,3\n", "orange,255,128,0,99.804693,true,2\n",
        "yellow,255,255,0,99.998480,true,1\n",
        "green,0,255,0,0.389099,false,-1\n", "blue,0,0,255,0.001520,false,-2\n",
        "purple,255,0,255,99.610901,false,-3\n", NULL};

    df_free(df1);
    cr_assert(df2 != NULL);
    cr_assert(df2->column_types[0] == STRING);
    cr_assert(df2->column_types[1] == UINT);
    cr_assert(df2->column_types[2] == UINT);
    cr_assert(df2->column_types[3] == UINT);
    cr_assert(df2->column_types[4] == FLOAT);
    cr_assert(df2->column_types[5] == BOOL);
    cr_assert(df2->column_types[6] == INT);
    cr_assert(df_write_csv(df2, filename) == 0);
    compare_file_content(filename, lines);
    remove(filename);
    cr_assert_str_eq((char *)(df2->data[0][3]), "green");
    df_free(df2);
}

Test(df_to_type, test_conversion_from_string_to_bool_with_error)
{
    char *filename = "tests/str_to_bool_err.csv";
    dataframe_t *df1 = df_read_csv("tests/data3.csv", ",");
    dataframe_t *df2 = df_to_type(df1, "name", BOOL);

    cr_assert(df2 == NULL);
}

Test(df_to_type, test_conversion_from_string_to_uint_with_error)
{
    char *filename = "tests/str_to_uint_err.csv";
    dataframe_t *df1 = df_read_csv("tests/data3.csv", ",");
    dataframe_t *df2 = df_to_type(df1, "name", UINT);

    cr_assert(df2 == NULL);
}

Test(df_to_type, test_conversion_from_string_to_int_with_error)
{
    char *filename = "tests/str_to_int_err.csv";
    dataframe_t *df1 = df_read_csv("tests/data3.csv", ",");
    dataframe_t *df2 = df_to_type(df1, "name", INT);

    cr_assert(df2 == NULL);
}

Test(df_to_type, test_conversion_from_string_to_float_with_error)
{
    char *filename = "tests/bool_to_bool.csv";
    dataframe_t *df1 = df_read_csv("tests/data3.csv", ",");
    dataframe_t *df2 = df_to_type(df1, "name", FLOAT);

    cr_assert(df2 == NULL);
}

Test(df_filter, test_of_the_subject)
{
    char *filename = "tests/filtered.csv";
    dataframe_t *df1 = df_read_csv("tests/data.csv", ",");
    dataframe_t *df2 = df_filter(df1, "age", &filter_func);
    char *lines[4] = {"name,age,city\n", "Charlie,35,Berlin\n",
        "Alex,35,Berlin\n", NULL};

    df_free(df1);
    cr_assert(df2 != NULL);
    cr_assert(df_write_csv(df2, filename) == 0);
    compare_file_content(filename, lines);
    df_free(df2);
}

Test(df_sort, test_of_the_subject)
{
    char *filename = "tests/sorted.csv";
    dataframe_t *df1 = df_read_csv("tests/data.csv", ",");
    dataframe_t *df2 = df_sort(df1, "age", &sort_func);
    char *lines[9] = {"name,age,city\n", "Alice,25,Paris\n", "Léo,25,Paris\n",
        "Paul,25,Paris\n", "Bob,30,London\n", "Nathan,30,London\n",
        "Charlie,35,Berlin\n", "Alex,35,Berlin\n", NULL};

    df_free(df1);
    cr_assert(df2 != NULL);
    cr_assert(df_write_csv(df2, filename) == 0);
    compare_file_content(filename, lines);
    df_free(df2);
}
