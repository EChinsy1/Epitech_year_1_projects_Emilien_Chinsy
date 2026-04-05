/*
** EPITECH PROJECT, 2025
** my_str_to_word_array
** File description:
** write a function that splits a string into word
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "my.h"

int get_num_of_commands(char *str)
{
    int i = 0;
    int num = 1;

    if (str == NULL)
        return (0);
    while (str[i] != '\0') {
        if (str[i] == ';')
            ++num;
        ++i;
    }
    return (num);
}

char ***fill_command_args(char *str, char ***command_args,
    char *delim, char *string_to_send)
{
    int start = 0;
    int end = 0;
    int num = 0;

    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] == ';') {
            string_to_send = my_calloc(sizeof(char), end - start + 1);
            my_strncat(string_to_send, &str[start], end - start);
            command_args[num] = my_str_to_word_array(string_to_send, delim);
            free(string_to_send);
            start = end;
            ++num;
        }
        ++end;
    }
    string_to_send = my_calloc(sizeof(char), end - start + 1);
    my_strncat(string_to_send, &str[start], end - start);
    command_args[num] = my_str_to_word_array(string_to_send, delim);
    free(string_to_send);
    return (command_args);
}

char ***parse_stuff(char *str, char *delim)
{
    int num_of_commands = get_num_of_commands(str);
    char ***command_args = NULL;
    char *string_to_send = NULL;

    if (num_of_commands == 0 || str == NULL)
        return (NULL);
    command_args = my_calloc(sizeof(char **), num_of_commands + 1);
    command_args = fill_command_args(str, command_args, delim, string_to_send);
    return (command_args);
}
