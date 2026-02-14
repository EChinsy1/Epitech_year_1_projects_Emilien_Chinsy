/*
** EPITECH PROJECT, 2025
** my_add_scientific_nota.c
** File description:
** function to show scientific notation
*/

#include "../../includes/my.h"

char *my_add_nbr_ndigits(int nb, int precision, char *real_buffer)
{
    char *buffer = my_calloc((precision + 1), sizeof(char));
    int i = 0;

    while (precision > 0){
        buffer[i] = ((nb % 10) + '0');
        nb = nb / 10;
        precision--;
        i++;
    }
    my_revstr(buffer);
    my_strcat(real_buffer, buffer);
    free(buffer);
    return (buffer);
}

int scientific_total_size(int decal, int float_part, int sign, int precision)
{
    int sum = 0;

    sum = sign + 3;
    if (precision > 0)
        sum = sum + 1 + precision;
    sum = sum + size_of_num(decal);
    if (size_of_num(decal) > 0)
        sum++;
    if ((size_of_num(decal) == 1) || (size_of_num(decal) == 2) && (decal < 0))
        sum++;
    return (sum);
}

static char *exposant(int decalage, char **other_args, char *true_buffer)
{
    char *buffer = NULL;
    int sign = 0;
    char *new_other_args[6];

    if (decalage < 0){
        sign = 1;
        decalage = -1 * decalage;
    }
    buffer = my_calloc((decalage + 5), sizeof(char));
    my_strcat(buffer, "e");
    if (sign != 0){
        my_strcat(buffer, "-");
    } else
        my_strcat(buffer, "+");
    if (decalage < 10)
        my_strcat(buffer, "0");
    my_fake_pivot_add_nbr(decalage, empty_other_args(new_other_args), buffer);
    my_strcat(true_buffer, my_strcat(buffer, "\0"));
    free(buffer);
    return (buffer);
}

char *scientific(long double nbr, int decalage, int sign, char **other_args)
{
    int precision = get_precision(other_args);
    int int_part = nbr;
    char *buffer = NULL;
    int sum = 0;
    float float_part = (nbr - int_part) * my_compute_power_rec(10, precision);
    int test = float_part;
    char *new_other_args[6];

    sum = scientific_total_size(decalage, float_part, sign, precision);
    buffer = my_calloc(sum, sizeof(char));
    if (sign == 1)
        my_strcat(buffer, "-");
    my_fake_pivot_add_nbr(int_part, empty_other_args(new_other_args), buffer);
    if (precision > 0 || flag_is_hash(other_args)){
        my_strcat(buffer, ".");
        my_add_nbr_ndigits(test, precision, buffer);
    }
    exposant(decalage, other_args, buffer);
    return (buffer);
}

char *my_add_scientific_nota(double percentage, char **other_args)
{
    int decalage = 0;
    char *buffer = NULL;
    int sign = 0;
    int precision = get_precision(other_args);

    if (percentage < 0){
        percentage = -1 * percentage;
        sign = 1;
    }
    while (percentage > 9){
        percentage = percentage / 10;
        decalage++;
    }
    while (percentage < 1 && percentage > 0){
        percentage = percentage * 10;
        decalage--;
    }
    buffer = scientific(my_round(percentage, precision),
        decalage, sign, other_args);
    return (change_buffer_with_width(buffer, other_args));
}

char *my_pivot_add_scientific(va_list args, char **other_args, char *buffer)
{
    char *temp_buffer = my_add_scientific_nota(
        length_for_double(args, other_args),
        other_args);

    my_strcat(buffer, temp_buffer);
    free(temp_buffer);
    return (buffer);
}
