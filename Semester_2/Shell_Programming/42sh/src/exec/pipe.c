/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** pipe.c
*/

#include <unistd.h>

void pipe_closer(int count, int pfildes[][2])
{
    for (int i = 0; i < count; ++i) {
        close(pfildes[i][0]);
        close(pfildes[i][1]);
    }
}

int activate_correct_pipes(int i, int count, int pfildes[][2])
{
    if (i > 0)
        dup2(pfildes[i - 1][0], STDIN_FILENO);
    if (i < count - 1)
        dup2(pfildes[i][1], STDOUT_FILENO);
    pipe_closer(count - 1, pfildes);
    return (0);
}
