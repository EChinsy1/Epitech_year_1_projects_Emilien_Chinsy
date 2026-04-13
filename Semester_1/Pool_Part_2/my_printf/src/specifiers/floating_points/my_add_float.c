/*
** EPITECH PROJECT, 2025
** my put float
** File description:
** a function to show float numbers
*/

#include "../../includes/my.h"

double my_round(double nb, int precision)
{
    double round = 5;

    for (int i = 0; i <= precision; i++){
        round = round / 10;
    }
    if (nb > 0){
        nb = nb + round;
    } else if (nb < 0){
        nb = nb - round;
    }
    return (nb);
}

int get_precision(char **other_args)
{
    if (my_strlen(other_args[2]) > 0){
        return (my_getnbr(other_args[2]));
    }
    return (6);
}

char **empty_other_args(char **new_other_args)
{
    new_other_args[0] = "";
    new_other_args[1] = "";
    new_other_args[2] = "";
    new_other_args[3] = "";
    new_other_args[4] = "";
    new_other_args[5] = NULL;
    return (new_other_args);
}

static float make_float_part_pos(float float_part)
{
    if (float_part < 0){
        return (float_part * -1);
    }
    return (float_part);
}

static int has_minus_and_is_zero(double nb, int int_part)
{
    if (nb < 0 && int_part == 0){
        return (1);
    }
    return (0);
}

static char *add_decimal_part(double nb,
    int int_part,
    char *buffer,
    char **other_args)
{
    int precision = get_precision(other_args);
    char *new_other_args[6];

    if (has_minus_and_is_zero(nb, int_part)){
        buffer = my_calloc((5 + precision), sizeof(char));
        buffer[0] = '-';
    } else {
        buffer = my_calloc((size_of_num(int_part) +
                precision + 2), sizeof(char));
    }
    my_fake_pivot_add_nbr(int_part, empty_other_args(new_other_args), buffer);
    if (precision > 0 || flag_is_hash(other_args)){
        add_char(buffer, '.');
    }
    return (buffer);
}

static char *add_decimal_part_precision_zero(double nb,
    int int_part,
    char *buffer,
    char **other_args)
{
    char *new_other_args[6];

    if (has_minus_and_is_zero(nb, int_part)){
        buffer = my_calloc((size_of_num(int_part) + 2), sizeof(char));
        buffer[0] = '-';
    } else {
        buffer = my_calloc((size_of_num(int_part) + 1), sizeof(char));
    }
    my_fake_pivot_add_nbr(int_part, empty_other_args(new_other_args), buffer);
    add_char(buffer, '\0');
    return (buffer);
}

char *my_add_float(long double nb, char **other_args)
{
    int precision = get_precision(other_args);
    long double rnb = my_round(nb, precision);
    int int_part = rnb;
    char *buffer = NULL;
    float float_part = ((rnb - int_part) * my_compute_power_rec(10, precision));

    if (precision == 0){
        buffer = add_decimal_part(rnb, int_part, buffer, other_args);
    } else {
        buffer = add_decimal_part(rnb, int_part, buffer, other_args);
        float_part = make_float_part_pos(float_part);
        my_add_nbr_ndigits(float_part, precision, buffer);
        buffer[size_of_num(int_part) +
            precision + 1 + has_minus_and_is_zero(rnb, int_part)] = '\0';
    }
    return (change_buffer_with_width(buffer, other_args));
}

char *my_pivot_add_float(va_list args, char **other_args, char *buffer)
{
    char *temp_buffer = my_add_float(
        length_for_double(args, other_args),
        other_args);

    my_strcat(buffer, temp_buffer);
    free(temp_buffer);
    return (buffer);
}
