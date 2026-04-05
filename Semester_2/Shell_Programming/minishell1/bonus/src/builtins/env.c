/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** minishell1
*/

#include <unistd.h>
#include <stdio.h>
#include "my.h"
#include "arguments.h"


int print_env(args_t *args, char **command_array)
{
    int i = 0;

    if (command_array[1] != NULL) {
        write(2, "Too many arguments\n", 19);
        return (84);
    }
    while (args->env[i] != NULL) {
        write(1, args->env[i], my_strlen(args->env[i]));
        write(1, "\n", 1);
        ++i;
    }
    free_word_array(command_array);
    return 0;
}
