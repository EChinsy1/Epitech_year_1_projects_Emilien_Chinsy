/*
** EPITECH PROJECT, 2025
** mini printf
** File description:
** first mini project of the year,
** we have to make a mini printf function
** that is a printf that handles the:
** s, i, d, c and % flags
*/

#include "includes/my.h"
#include "includes/struct.h"

static void dynamic_free(char **other_args, int size)
{
    for (int i = 0; i < size; i++){
        free(other_args[i]);
    }
    free(other_args);
}

int my_char_is_specifier(char to_check)
{
    int i = 0;

    if (to_check == 'n'){
        return (1);
    }
    while (EACH_FUNCTION[i].flag){
        if (EACH_FUNCTION[i].flag == to_check){
            return (1);
        }
        i++;
    }
    return (0);
}

char *which_type(va_list args,
    const char *to_check,
    char **other_args,
    char *buffer)
{
    int i = 0;
    int *n_ptr = NULL;

    if (my_char_is_specifier(*other_args[4]) != 1){
        return (my_pivot_wrong_format(args, other_args, buffer));
    }
    if (*other_args[4] == 'n'){
        n_ptr = (int *)length_for_n(args, other_args);
        *n_ptr = my_strlen(buffer);
        return ("");
    }
    while (EACH_FUNCTION[i].flag){
        if (EACH_FUNCTION[i].flag == *to_check){
            return (EACH_FUNCTION[i].fptr(args, other_args, buffer));
        }
        i++;
    }
    return ("");
}

static int final_return(char *buffer)
{
    int len = my_strlen(buffer);

    write(1, buffer, my_strlen(buffer));
    free(buffer);
    return (len);
}

int my_printf(const char *format, ...)
{
    va_list args;
    char *buffer = my_calloc(1000, sizeof(char));
    char **other_args = NULL;

    va_start(args, format);
    for (int i = 0; i < my_strlen(format); ++i) {
        if (format[i] == '%' && format[i + 1] != '\0'){
            other_args = my_calloc(6, sizeof(char *));
            i++;
            format_specifier_separator(args, &format[i], &i, other_args);
            which_type(args, &format[i], other_args, buffer);
            dynamic_free(other_args, 5);
        } else
            add_char(buffer, format[i]);
    }
    buffer[my_strlen(buffer)] = '\0';
    va_end(args);
    return (final_return(buffer));
}
