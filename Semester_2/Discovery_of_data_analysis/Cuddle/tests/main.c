/*
** EPITECH PROJECT, 2026
** G2 - Discovery of Data Analysis - Cuddle - Alexis & Emilien
** File description:
** main file to test the project
*/

#include <stdlib.h>
#include <stdio.h>
#include "dataframe.h"

int main(void)
{
    dataframe_t *df = df_read_csv("tests/data4.csv", ";");

    df_write_csv(df, "tests/tmp.csv");
    df_free(df);
    return EPITECH_SUCCESS;
}
