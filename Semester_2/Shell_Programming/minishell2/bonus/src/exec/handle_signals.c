/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** signal_handling
*/

#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "macros.h"
#include "my.h"
#include "arguments.h"
#include "builtins.h"

int broken_pipe_handling(int count, int status, tree_t *tree, args_t **args)
{
    int i = 0;

    if (!tree->left_node ||
        (tree->left_node->symbol && tree->left_node->symbol[0] != ' ')
        || !tree->right_node)
        return ((*args)->last_command_return);
    while (builtinfuncs[i].name != NULL) {
        if (my_strcmp(builtinfuncs[i].name,
                tree->right_node->value[0]) == 0) {
            return (141);
        }
        ++i;
    }
    return ((*args)->last_command_return);
}

static int print_the_inside(int signal, int status)
{
    if (signal == SIGFPE) {
        my_putstr(2, "Floating exception");
    } else
        my_putstr(2, strsignal(signal));
    if (WCOREDUMP(status))
        my_putstr(2, " (core dumped)");
    if (WIFSTOPPED(status) == 1) {
        signal = WSTOPSIG(status);
        my_putstr(2, strsignal(signal));
    }
    return (signal);
}

void display_signal(args_t **args, tree_t *tree, int status, char *name)
{
    int signal = 0;

    if (WIFEXITED(status) || !WIFSIGNALED(status) || status == BROKEN_PIPE)
        return;
    signal = WTERMSIG(status);
    (*args)->last_command_return = status;
    if (signal == SIGINT)
        return;
    signal = print_the_inside(signal, status);
    write(2, "\n", 1);
}
