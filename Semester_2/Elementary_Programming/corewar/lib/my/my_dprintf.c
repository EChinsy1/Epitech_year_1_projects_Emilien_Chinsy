/*
** EPITECH PROJECT, 2026
** Lib
** File description:
** My mini Dprintf
*/

#include <unistd.h>
#include <stdarg.h>
#include "my.h"

static void my_puts(int fd, char *str)
{
    write(fd, str, my_strlen(str));
}

static int mini_check_flags(int fd, char flag, va_list list)
{
    char c = 0;

    if (flag == 'd' || flag == 'i')
        my_put_nbr(va_arg(list, int));
    if (flag == 's')
        my_puts(fd, va_arg(list, char *));
    if (flag == 'c') {
        c = (char)va_arg(list, int);
        write(fd, &c, 1);
    }
    if (flag == '%')
        write(fd, "%", 1);
    return 0;
}

int my_dprintf(int fd, const char *format, ...)
{
    int i = 0;
    va_list list;

    va_start(list, format);
    while (format[i]){
        if (format[i] == '%' && format[i + 1]){
            i++;
            mini_check_flags(fd, format[i], list);
            i++;
        } else {
            write(fd, &format[i], 1);
            i++;
        }
    }
    va_end(list);
    return i;
}
