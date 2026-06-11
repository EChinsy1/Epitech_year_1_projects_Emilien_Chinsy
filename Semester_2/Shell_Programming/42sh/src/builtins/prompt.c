/*
** EPITECH PROJECT, 2026
** prompt
** File description:
** prompt
*/

#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arguments.h"
#include "input.h"
#include "macros.h"
#include "my.h"

static int ask_to_ia(args_t *argument)
{
    pid_t pid = fork();
    int status = 0;
    char *python_path = "/usr/bin/python3";
    char *script_path = "./script/prompt.py";
    char *exec_args[] = {"python3", script_path, NULL};

    if (pid == ERROR) {
        perror("fork");
        return ERROR;
    }
    if (pid == SUCCESS) {
        if (execve(python_path, exec_args, argument->env) == ERROR) {
            perror("execve ai");
            return ERROR;
        }
    } else
        waitpid(pid, &status, 0);
    return SUCCESS;
}
/*
int prompt_builtin(args_t *argument, char **env)
{
    char **args = my_str_to_word_array(argument->buffer, " ", argument);

    if (args[1] == NULL) {
        printf("ai: erreur: il manque la question.\n");
        printf("Usage: ai \"comment lister les dossiers\"\n");
        return ERROR;
    }
    for (size_t i = 0; args[i] != NULL; i++)
        printf("%s\n", args[i]);
    if (ask_to_ia(argument, args) == ERROR)
        return ERROR;
    return SUCCESS;
}
*/
int prompt_builtin(args_t *argument, char **env)
{
    ask_to_ia(argument);
    return SUCCESS;
}
