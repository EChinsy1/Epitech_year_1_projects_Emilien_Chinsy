/*
** EPITECH PROJECT, 2026
** G2 - Discovery of Data Analysis - Cuddle - Alexis & Emilien
** File description:
** this file countains the is_a_bool tool function
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dataframe.h"

bool is_a_bool(char *str)
{
    char *low = to_lower(str);
    bool r_val = false;

    if (low == NULL)
        return false;
    r_val = (strcmp(low, STRUE) == 0 || strcmp(low, SFALSE) == 0);
    free(low);
    return r_val;
}
