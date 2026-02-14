/*
** EPITECH PROJECT, 2025
** change buffer with width
** File description:
** a file that handles width
*/

#include "../../includes/my.h"

static char *space_flag_new_buffer(char *buffer, char **other_args)
{
    char *new_buffer = NULL;
    int i = 1;
    int width = my_getnbr(other_args[1]);

    if (width > my_strlen(buffer)) {
        return (buffer);
    }
    new_buffer = my_calloc((my_strlen(buffer) + 2), sizeof(char));
    new_buffer[0] = ' ';
    for (int j = 0; j < my_strlen(buffer); j++){
        new_buffer[i] = buffer[j];
        i++;
    }
    new_buffer[i] = '\0';
    free(buffer);
    return (new_buffer);
}

static char *float_fill_buffer(int width,
    char *buffer,
    char width_char,
    char **other_args)
{
    char *new_buffer = NULL;
    int i = 0;

    new_buffer = my_calloc((width + 1), sizeof(char));
    if (flag_is_plus(other_args, buffer) == 1){
        new_buffer[0] = '+';
        i++;
    } else if (flag_is_space(other_args, buffer) == 1){
        new_buffer[0] = ' ';
        i++;
    }
    for (; i < (width - my_strlen(buffer)); i++)
        new_buffer[i] = width_char;
    for (int j = 0; j < (my_strlen(buffer)); j++){
        new_buffer[i] = buffer[j];
        i++;
    }
    new_buffer[i] = '\0';
    free(buffer);
    return (new_buffer);
}

static char *fill_buffer_zerox(int *max,
    char *buffer,
    int *i,
    char **other_ars)
{
    char *new_buffer = my_calloc((my_getnbr(other_ars[1]) + 1), sizeof(char));

    if (flag_is_hash(other_ars) == 1 && flag_is_zero(other_ars, buffer) == '0'){
        if (*other_ars[4] == 'x' || *other_ars[4] == 'X')
            *max = 2;
    }
    if ((*other_ars[4] == 'a' || *other_ars[4] == 'A') &&
        flag_is_zero(other_ars, buffer) == '0'){
        *max = 2;
        if (buffer[0] == '-' || buffer[0] == '+')
            *max = *max + 1;
    } else if ((buffer[0] == '-' || buffer[0] == '+') &&
        flag_is_zero(other_ars, buffer) == '0'){
        *max = *max + 1;
    }
    for (int y = 0; y < *max; y++){
        new_buffer[*i] = buffer[y];
        *i = *i + 1;
    }
    return (new_buffer);
}

static char *fill_buffer(int width,
    char *buffer,
    char width_char,
    char **other_ars)
{
    char *new_buffer = NULL;
    int i = 0;
    int max = 0;

    if (my_str_isfloat(buffer) == 1)
        return (float_fill_buffer(width, buffer, width_char, other_ars));
    new_buffer = fill_buffer_zerox(&max, buffer, &i, other_ars);
    for (; i < (width - my_strlen(buffer) + max); i++){
        new_buffer[i] = width_char;
    }
    for (int j = max; j < (my_strlen(buffer)); j++){
        new_buffer[i] = buffer[j];
        i++;
    }
    new_buffer[i] = '\0';
    free(buffer);
    return (new_buffer);
}

static char *minus_flag_new_buffer(int width, char *buffer, char **other_args)
{
    char *new_buffer = my_calloc((width + 1), sizeof(char));
    int i = 0;

    if (flag_is_space(other_args, buffer)){
        new_buffer[i] = ' ';
        i++;
    }
    for (int j = 0; j < my_strlen(buffer); j++){
        new_buffer[i] = buffer[j];
        i++;
    }
    for (; i < (width); i++){
        new_buffer[i] = ' ';
    }
    new_buffer[i] = '\0';
    free(buffer);
    return (new_buffer);
}

static char *plus_flag_new_buffer(char *buffer)
{
    char *new_buffer = my_calloc((my_strlen(buffer) + 2), sizeof(char));
    int i = 1;

    new_buffer[0] = '+';
    for (int j = 0; j < my_strlen(buffer); j++){
        new_buffer[i] = buffer[j];
        i++;
    }
    new_buffer[i] = '\0';
    return (new_buffer);
}

static char *hash_flag_new_buffer(char *buffer, char **other_args)
{
    char *new_buffer = NULL;
    int i = 0;

    if (*other_args[4] == 'x' || *other_args[4] == 'X') {
        new_buffer = my_calloc((my_strlen(buffer) + 3), sizeof(char));
        add_char(new_buffer, '0');
        add_char(new_buffer, *other_args[4]);
        i = 2;
    } else if (*other_args[4] == 'o') {
        new_buffer = my_calloc((my_strlen(buffer) + 2), sizeof(char));
        add_char(new_buffer, '0');
        i = 1;
    } else
        return (buffer);
    for (int j = 0; j < my_strlen(buffer); j++){
        new_buffer[i] = buffer[j];
        i++;
    }
    new_buffer[i] = '\0';
    return (new_buffer);
}

static void setup_final_buffer(char *final_buffer, char *buffer)
{
    int i = 0;

    for (; i < my_strlen(buffer); i++){
        final_buffer[i] = buffer[i];
    }
    final_buffer[i] = '\0';
}

char *apply_flags(char *final_buffer,
    char **other_args,
    char *buffer)
{
    if (*other_args[4] == 'X' || *other_args[4] == 'x'
        || *other_args[4] == 'o'){
        if (flag_is_hash(other_args)){
            return (hash_flag_new_buffer(final_buffer, other_args));
        }
    }
    if (flag_is_plus(other_args, buffer)){
        final_buffer = plus_flag_new_buffer(final_buffer);
    }
    if (flag_is_space(other_args, buffer) == 1){
        final_buffer = space_flag_new_buffer(final_buffer, other_args);
    }
    return (final_buffer);
}

char *change_buffer_with_width(char *buffer, char **other_args)
{
    int width = my_getnbr(other_args[1]);
    char width_char = flag_is_zero(other_args, buffer);
    char *fin_buffer = NULL;

    if (width > my_strlen(buffer)){
        fin_buffer = my_calloc((width + 1), sizeof(char));
    } else {
        fin_buffer = my_calloc((my_strlen(buffer) + 1), sizeof(char));
    }
    setup_final_buffer(fin_buffer, buffer);
    fin_buffer = apply_flags(fin_buffer, other_args, buffer);
    if (width > my_strlen(buffer)){
        if (flag_is_minus(other_args, buffer)){
            fin_buffer = minus_flag_new_buffer(width, fin_buffer, other_args);
        } else {
            fin_buffer = fill_buffer(width, fin_buffer, width_char, other_args);
        }
    }
    free(buffer);
    return (fin_buffer);
}
