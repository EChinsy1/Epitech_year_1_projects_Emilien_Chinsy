/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** minishell1
*/

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include "my.h"

static void new_sigterm(int pid)
{
    write(1, "\n", 1);
    write_console_message();
}

int main(int argc, char **argv, char **env)
{
    int final_return = 0;

    if (argc > 1)
        return (scripting(argv[1], argc, argv, env));
    signal(SIGINT, &new_sigterm);
    signal(SIGTSTP, &new_sigterm);
    final_return = minishell(argc, argv, env);
    return (final_return);
}
