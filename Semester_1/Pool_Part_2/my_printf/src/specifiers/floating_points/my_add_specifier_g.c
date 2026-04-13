/*
** EPITECH PROJECT, 2025
** my_add_specifier_g.c
** File description:
** handles the specifier %g
*/

#include "../../includes/my.h"

int get_exposant(double percentage)
{
    int decalage = 0;

    if (percentage < 0)
        percentage = -1 * percentage;
    while (percentage > 9){
        percentage = percentage / 10;
        decalage++;
    }
    while (percentage < 1 && percentage > 0){
        percentage = percentage * 10;
        decalage--;
    }
    return (decalage);
}

static char *change_precision_for_f(char **other_args,
    int precision,
    double number)
{
    char *new_precision = NULL;

    while ((int)number == 0 && number != 0){
        ++precision;
        number = number * 10;
    }
    precision = precision - size_of_num(number);
    new_precision = my_calloc(size_of_num(precision) + 1, sizeof(int));
    for (int i = 0; i < size_of_num(precision); i++){
        add_char(new_precision, (precision % 10) + '0');
        precision = precision / 10;
    }
    my_revstr(new_precision);
    new_precision[size_of_num(precision)] = '\0';
    free(other_args[2]);
    other_args[2] = new_precision;
    return ("");
}

static char *change_precision_for_e(char **other_args, int precision)
{
    char *new_precision = NULL;

    precision = precision - 1;
    new_precision = my_calloc(size_of_num(precision), sizeof(int));
    for (int i = 0; i < size_of_num(precision); i++){
        add_char(new_precision, (precision % 10) + '0');
        precision = precision / 10;
    }
    my_revstr(new_precision);
    free(other_args[2]);
    other_args[2] = new_precision;
    return ("");
}

static char *remove_zeros_float(char *buffer, char **other_args)
{
    int i = my_strlen(buffer) - 1;
    char *new_buffer = NULL;

    while ((buffer[i] == '0' || buffer[i] == '\0') && i > 0){
        --i;
    }
    if (buffer[i] == '.'){
        if (buffer[i - 1] == '0'){
            --i;
        }
    }
    new_buffer = my_calloc(i + 2, sizeof(char));
    for (int j = 0; j <= i; j++){
        new_buffer[j] = buffer[j];
    }
    new_buffer[i + 1] = '\0';
    free(buffer);
    return (change_buffer_with_width(new_buffer, other_args));
}

static char *remove_zeros_e(char *buffer, char **other_args)
{
    int i = my_strlen(buffer) - 1;
    char *new_buffer = NULL;
    int modifier = 0;
    int where_is_e = 0;

    while ((buffer[(i - 4 - modifier)] == '0' ||
            buffer[(i - 4 - modifier)] == '\0') && i > 0){
        ++modifier;
    }
    new_buffer = my_calloc(i - modifier + 2, sizeof(int));
    for (int j = 0; j <= (i - 4 - modifier); j++){
        new_buffer[j] = buffer[j];
    }
    while (buffer[where_is_e] != 'e'){
        ++where_is_e;
    }
    my_strcat(new_buffer, &buffer[where_is_e]);
    new_buffer[i + 1] = '\0';
    free(buffer);
    return (change_buffer_with_width(new_buffer, other_args));
}

static char *final_return(char *temp_buffer, char *buffer, char **other_args)
{
    int i = 0;

    while (temp_buffer[i] && *other_args[4] == 'G'){
        if (temp_buffer[i] == 'e')
            temp_buffer[i] = 'E';
        i++;
    }
    my_strcat(buffer, temp_buffer);
    free(temp_buffer);
    return (buffer);
}

char *my_pivot_add_g(va_list args, char **other_ars, char *buffer)
{
    int precision = get_precision(other_ars);
    double nbr = length_for_double(args, other_ars);
    int exposant = get_exposant(nbr);
    char *temp;

    if (exposant < -4 || exposant >= precision){
        change_precision_for_e(other_ars, precision);
        if (flag_is_hash(other_ars)) {
            temp = my_add_scientific_nota(nbr, other_ars);
        } else
            temp = remove_zeros_e(my_add_scientific_nota(nbr, other_ars),
                other_ars);
    } else {
        change_precision_for_f(other_ars, precision, nbr);
        if (flag_is_hash(other_ars)) {
            temp = my_add_float(nbr, other_ars);
        } else
            temp = remove_zeros_float(my_add_float(nbr, other_ars), other_ars);
    }
    return (final_return(temp, buffer, other_ars));
}

char *my_pivot_add_g_maj(va_list args, char **other_args, char *buffer)
{
    return (my_pivot_add_g(args, other_args, buffer));
}
