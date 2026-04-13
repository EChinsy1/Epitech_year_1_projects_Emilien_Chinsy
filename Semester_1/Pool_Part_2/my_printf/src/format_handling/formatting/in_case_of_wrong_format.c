/*
** EPITECH PROJECT, 2025
** in case of wrong format
** File description:
** handle printing in case of wrong format, such as an inexistant specifier
** or an impossible flag
*/

#include "../../includes/my.h"

int add_flags(char *to_add, char *buffer)
{
    for (int i = 0; i < my_strlen(to_add); i++){
        if (to_add[i] == '#' || to_add[i] == '+' || to_add[i] == '-'){
            add_char(buffer, to_add[i]);
        }
    }
    return (1);
}

char *my_add_wrong_format(char const *str, char **other_args)
{
    char *buffer = malloc(100);

    add_char(buffer, '%');
    add_flags(other_args[0], buffer);
    my_strcat(buffer, other_args[1]);
    if (my_strlen(other_args[2]) > 0){
        add_char(buffer, '.');
    }
    my_strcat(buffer, other_args[2]);
    add_char(buffer, *other_args[4]);
    add_char(buffer, '\0');
    return (buffer);
}

char *my_pivot_wrong_format(va_list args, char **other_args, char *buffer)
{
    char *temp_buffer = my_add_wrong_format("", other_args);

    my_strcat(buffer, temp_buffer);
    free(temp_buffer);
    return (buffer);
}
