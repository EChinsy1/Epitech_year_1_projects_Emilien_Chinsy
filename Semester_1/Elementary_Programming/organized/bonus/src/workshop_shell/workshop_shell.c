/*
** EPITECH PROJECT, 2025
** workshop_shell
** File description:
** workshop_shell
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "my.h"
#include "shell_functions.h"

int exec_function(void *data, char **args)
{
    int i = 0;

    if (strcmp(args[0], "exit") == 0)
        return (1);
    while (SHELL_FUNCS[i].name != NULL) {
        if (strcmp(SHELL_FUNCS[i].name, args[0]) == 0)
            return (SHELL_FUNCS[i].fptr(data, &args[1]));
        ++i;
    }
    printf("%s: Command not found.\n", args[0]);
    return (0);
}

void free_word_array(char **word_array)
{
    for (int i = 0; word_array[i]; ++i) {
        free(word_array[i]);
    }
    free(word_array);
}

int workshop_shell(void *data)
{
    char **args = NULL;
    char *buffer = NULL;
    int return_value = 0;

    while (return_value == 0) {
        printf("\x1b[1;33mWorkshop >> \x1b[m");
        buffer = calloc(sizeof(char *), BUF_SIZE);
        fgets(buffer, BUF_SIZE, stdin);
        args = my_str_to_word_array(buffer);
        if (args[0] != NULL) {
            return_value = exec_function(data, args);
        } else
            return_value = 0;
        free_word_array(args);
        free(buffer);
    }
    if (return_value != 0 && return_value != 1)
        return (84);
    return (0);
}
