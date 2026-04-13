/*
** EPITECH PROJECT, 2025
** my add ptr adress
** File description:
** handles the %p specifier for printf
*/

#include "../../includes/my.h"

char *my_add_ptr_address(void *ptr, char **other_args)
{
    unsigned long addr = (unsigned long)ptr;
    char *buffer = my_calloc(2 + (sizeof(void *) * 2) + 1, sizeof(char));
    char *real_buffer = my_calloc(2 + (sizeof(void *) * 2) + 1 - 4,
        sizeof(char));
    char *lookup_table = "0123456789abcdef";
    int i = sizeof(void *) * 2 + 1;
    int j = 0;

    buffer[i] = '\0';
    for (i = sizeof(void *) * 2; i > 4; --i){
        buffer[i + 1] = lookup_table[addr & 0xF];
        addr >>= 4;
    }
    real_buffer[0] = '0';
    real_buffer[1] = 'x';
    my_strcat(real_buffer, &buffer[i + 2]);
    free(buffer);
    return (change_buffer_with_precision_int(real_buffer, other_args));
}

char *my_pivot_add_ptr_address(va_list args, char **other_args, char *buffer)
{
    char *temp_buffer = my_add_ptr_address(va_arg(args, void *), other_args);

    my_strcat(buffer, temp_buffer);
    free(temp_buffer);
    return (buffer);
}
