/*
** EPITECH PROJECT, 2025
** length handler
** File description:
** a file to handle length
*/

#include "../../includes/my.h"

intmax_t length_for_int(va_list args, char **other_ars)
{
    if (my_strcmp(other_ars[3], "hh") == 0)
        return ((signed char)va_arg(args, int));
    if (*other_ars[3] == 'h')
        return ((short int)va_arg(args, int));
    if (my_strcmp(other_ars[3], "ll") == 0 || my_strcmp(other_ars[3], "q") == 0)
        return (va_arg(args, long long int));
    if (*other_ars[3] == 'l')
        return (va_arg(args, long int));
    if (*other_ars[3] == 'j')
        return (va_arg(args, intmax_t));
    if (*other_ars[3] == 'z')
        return (va_arg(args, size_t));
    if (*other_ars[3] == 'Z')
        return (va_arg(args, size_t));
    if (*other_ars[3] == 't')
        return (va_arg(args, ptrdiff_t));
    return (va_arg(args, int));
}

uintmax_t length_for_ui(va_list args, char **other_ars)
{
    if (my_strcmp(other_ars[3], "hh") == 0)
        return ((unsigned char)va_arg(args, int));
    if (*other_ars[3] == 'h')
        return ((unsigned short int)va_arg(args, int));
    if (my_strcmp(other_ars[3], "ll") == 0 || my_strcmp(other_ars[3], "q") == 0)
        return (va_arg(args, unsigned long long int));
    if (*other_ars[3] == 'l')
        return (va_arg(args, unsigned long int));
    if (*other_ars[3] == 'j')
        return (va_arg(args, uintmax_t));
    if (*other_ars[3] == 'z')
        return (va_arg(args, size_t));
    if (*other_ars[3] == 'Z')
        return (va_arg(args, size_t));
    if (*other_ars[3] == 't')
        return (va_arg(args, ptrdiff_t));
    return (va_arg(args, unsigned int));
}

long double length_for_double(va_list args, char **other_ars)
{
    if (*other_ars[3] == 'L')
        return (va_arg(args, long double));
    return (va_arg(args, double));
}

void *length_for_n(va_list args, char **other_ars)
{
    if (my_strcmp(other_ars[3], "hh") == 0)
        return va_arg(args, signed char *);
    if (*other_ars[3] == 'h')
        return va_arg(args, short int *);
    if (my_strcmp(other_ars[3], "ll") == 0 || my_strcmp(other_ars[3], "q") == 0)
        return va_arg(args, long long int *);
    if (*other_ars[3] == 'l')
        return va_arg(args, long int *);
    if (*other_ars[3] == 'j')
        return va_arg(args, intmax_t *);
    if (*other_ars[3] == 'z')
        return va_arg(args, size_t *);
    if (*other_ars[3] == 't')
        return va_arg(args, ptrdiff_t *);
    return va_arg(args, int *);
}
