/*
** EPITECH PROJECT, 2026
** G2 - Discovery of Data Analysis - Cuddle - Alexis & Emilien
** File description:
** main file to test the project
*/

#include <stdlib.h>
#include <stdio.h>
#include "dataframe.h"

static bool filter_funct_test(void *value)
{
    return (*((unsigned int *)(value)) >= 30);
}

static bool sort_func_test(void *value1, void *value2)
{
    return (*((unsigned int *)(value1)) > *((int *)(value2)));
}

static void *agg_func_test(void **values, int nb_values)
{
    unsigned int *sum = malloc(sizeof(unsigned int));

    if (sum == NULL)
        return NULL;
    *sum = 0;
    for (int i = 0; i < nb_values; ++i)
        *sum += *((unsigned int *)(values[i]));
    return sum;
}

static void *apply_func_test(void *value)
{
    unsigned int *new_value = malloc(sizeof(unsigned int));

    if (new_value == NULL)
        return NULL;
    *new_value = *((unsigned int *)(value)) * 2;
    return new_value;
}

int main(void)
{
    dataframe_t *dataframe = df_read_csv("tests/data.csv", ",");
    dataframe_t *filtered = df_filter(dataframe, "age", &filter_funct_test);
    dataframe_t *sorted = df_sort(dataframe, "age", &sort_func_test);
    dataframe_t *agg = df_groupby(dataframe, "city",
        (const char *[]){"age", NULL}, &agg_func_test);
    dataframe_t *applied = df_apply(dataframe, "age", &apply_func_test);
    dataframe_t *conv = df_to_type(dataframe, "amount", INT);

    printf("%i\n%i\n%i\n%i\n%i\n", df_write_csv(dataframe,
        "tests/data_write.csv"),
        df_write_csv(filtered, "tests/data_filtered.csv"),
        df_write_csv(sorted, "tests/data_sorted.csv"),
        df_write_csv(agg, "tests/data_agg.csv"),
        df_write_csv(applied, "tests/data_applied.csv"));
    df_free(dataframe);
    df_free(filtered);
    df_free(sorted);
    df_free(agg);
    df_free(applied);
    df_free(conv);
    return EPITECH_SUCCESS;
}
