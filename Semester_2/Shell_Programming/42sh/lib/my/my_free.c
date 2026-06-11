/*
** EPITECH PROJECT, 2026
** my_top
** File description:
** File that frees arrays and strings
*/

#include <stdlib.h>
#include <stdarg.h>

void my_str_free(int count, ...)
{
    va_list strings;

    va_start(strings, count);
    for (; count > 0; count--) {
        free((char *)va_arg(strings, char *));
    }
    va_end(strings);
}

void my_array_free(int count, ...)
{
    char **ptr = NULL;
    va_list arrays;

    va_start(arrays, count);
    for (; count > 0; count--) {
        ptr = va_arg(arrays, char **);
        for (int i = 0; ptr[i] != NULL; i++)
            free(ptr[i]);
        free(ptr);
    }
    va_end(arrays);
}

void my_strtok_free(int count, ...)
{
    char **ptr = NULL;
    va_list arrays;

    va_start(arrays, count);
    for (; count > 0; count--) {
        ptr = va_arg(arrays, char **);
        free(ptr[0]);
        free(ptr);
    }
    va_end(arrays);
}
