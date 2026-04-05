/*
** EPITECH PROJECT, 2026
** G2 - Discovery of Data Analysis - Cuddle - Alexis & Emilien
** File description:
** this file countains the convertion tools functions
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dataframe.h"

char *to_lower(char *str)
{
    char *str_new = strdup((const char *)(str));

    if (str_new == NULL)
        return NULL;
    for (int i = 0; str_new[i] != '\0'; ++i) {
        if (str_new[i] >= 'A' && str_new[i] <= 'Z')
            str_new[i] = str_new[i] + ('a' - 'A');
    }
    return str_new;
}

int get_int_part(double nbr)
{
    int i = 0;

    if (nbr < 0)
        return -get_int_part(-nbr);
    while (i + 1 < nbr)
        i += 1;
    return i;
}

int iround(double nbr)
{
    int int_part = 0;

    if (nbr < 0)
        return -iround(-nbr);
    int_part = get_int_part(nbr);
    if ((nbr - int_part) >= 0.5)
        int_part += 1;
    return int_part;
}

void *convert_nbr_from_str(char *str, column_type_t type)
{
    int int_val = 0;
    double f_val = 0;
    char *tmp = NULL;

    if (str[0] == '+' || str[0] == '-')
        if (!(str[1] >= '0' && str[1] <= '9'))
            return NULL;
    if (!(str[0] >= '0' && str[0] <= '9') && str[0] != '+' && str[0] != '-')
        return NULL;
    if (type == UINT || type == INT) {
        int_val = atoi((const char *)(str));
        if (int_val < 0 && type == UINT)
            return NULL;
        return cpy_data(&int_val, type);
    }
    f_val = strtod((const char *)(str), &tmp);
    return cpy_data(&f_val, type);
}

int get_nbr_digits(int nbr)
{
    int nd = 0;

    if (nbr < 0)
        return get_nbr_digits(-nbr) + 1;
    if (nbr == 0)
        return 1;
    for (; nbr > 0; ++nd)
        nbr /= 10;
    return nd;
}
