/*
** EPITECH PROJECT, 2025
** format specifier separator
** File description:
** a file to get the flags, width, precision and length
** of the current argument
*/

#include "../../includes/my.h"

int multiple_instances_of_char(const char to_check, char *str)
{
    for (int i = 0; i < my_strlen(str); i++){
        if (str[i] == to_check){
            return (0);
        }
    }
    add_char(str, to_check);
    return (0);
}

static char *flag_storer(int *i, const char *to_check)
{
    char *flags = my_calloc(my_strlen(to_check) + 1, sizeof(char));

    while (my_char_is_flag(to_check[*i]) == 1) {
        multiple_instances_of_char(to_check[*i], flags);
        *i = *i + 1;
    }
    return (flags);
}

static char *width_storer(int *i, const char *to_check, va_list args)
{
    char *width = my_calloc(10, sizeof(char));
    int arg_width = 0;
    int size_of_arg_width = 0;

    while (my_char_isnum(to_check[*i]) == 1){
        add_char(width, to_check[*i]);
        *i = *i + 1;
    }
    if (to_check[*i] == '*'){
        arg_width = (va_arg(args, int));
        my_add_nbr_ndigits(arg_width, size_of_num(arg_width), width);
        *i = *i + 1;
    }
    return (width);
}

static char *precision_storer(int *i, const char *to_check, va_list args)
{
    char *precision = my_calloc(10, sizeof(char));
    int arg_width = 0;
    int size_of_arg_width = 0;

    if (to_check[*i] == 46){
        *i = *i + 1;
        while (my_char_isnum(to_check[*i]) == 1) {
            add_char(precision, to_check[*i]);
            *i = *i + 1;
        }
        if (to_check[*i] == '*'){
            arg_width = (va_arg(args, int));
            my_add_nbr_ndigits(arg_width, size_of_num(arg_width), precision);
            *i = *i + 1;
        }
    }
    return (precision);
}

static char *length_storer(int *i, const char *to_check)
{
    char *length = my_calloc(3, sizeof(char));

    if (my_char_is_length(to_check[*i]) == 1) {
        if (to_check[*i] == 'l' && to_check[*i + 1] == 'l'){
            add_char(length, to_check[*i]);
            *i = *i + 1;
        }
        if (to_check[*i] == 'h' && to_check[*i + 1] == 'h'){
            add_char(length, to_check[*i]);
            *i = *i + 1;
        }
        add_char(length, to_check[*i]);
        *i = *i + 1;
    }
    return (length);
}

static char **valid_format(int i,
    const char *to_check,
    char **other_args,
    int *j)
{
    other_args[4] = my_calloc(2, sizeof(char));
    add_char(other_args[4], to_check[i]);
    return (other_args);
}

char **format_specifier_separator(va_list args,
    const char *to_check,
    int *j,
    char **other_args)
{
    int i = 0;
    char *flags = flag_storer(&i, to_check);
    char *width = width_storer(&i, to_check, args);
    char *precision = precision_storer(&i, to_check, args);
    char *length = length_storer(&i, to_check);

    *j = *j + i;
    other_args[0] = flags;
    add_char(other_args[0], '\0');
    other_args[1] = width;
    add_char(other_args[1], '\0');
    other_args[2] = precision;
    add_char(other_args[2], '\0');
    other_args[3] = length;
    add_char(other_args[3], '\0');
    return (valid_format(i, to_check, other_args, j));
}
