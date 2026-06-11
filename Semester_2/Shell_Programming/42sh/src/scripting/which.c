/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** which
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include "my.h"
#include "redirections.h"
#include "macros.h"

static void check_error(char *command)
{
    FILE *file = NULL;
    char *buffer = NULL;
    size_t size = 0;

    file = fopen(WHICH_FILE, "r");
    if (file && getline(&buffer, &size, file) > 0)
        dprintf(2, "%s: Command not found.\n", command);
    if (file)
        fclose(file);
    file = fopen(WHICH_FILE, "w");
    fwrite("", 1, 1, file);
    if (file)
        fclose(file);
    remove(WHICH_FILE);
}

static void update_with_command(char *command, args_t *args)
{
    char *commandd = calloc(sizeof(char), strlen(command) + 7);
    int dup_fd = dup(STDERR_FILENO);
    int fd = 0;

    strcat(commandd, "which ");
    strcat(commandd, command);
    if (system(commandd) != 0) {
        fd = open(WHICH_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd > 0) {
            dup2(fd, STDERR_FILENO);
            system(command);
            close(fd);
        }
    }
    dup2(dup_fd, STDERR_FILENO);
    check_error(command);
    free(commandd);
}

int which(args_t *args, char **command_array)
{
    if (!command_array || command_array[0] == NULL)
        return (0);
    for (int i = 1; command_array[i]; ++i) {
        update_with_command(command_array[i], args);
    }
    return 0;
}
