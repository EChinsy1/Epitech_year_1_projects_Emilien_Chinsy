/*
** EPITECH PROJECT, 2026
** cesar
** File description:
** crypt_in_file
*/

#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include "macro.h"

int crypt_in_file(char *message)
{
    int fd = 0;

    if (message == NULL)
        return (EXIT_ERROR);
    fd = open("crypt", (O_CREAT | O_TRUNC | O_WRONLY),
        (S_IRUSR | S_IRGRP | S_IROTH));
    if (fd <= ERROR)
        return EXIT_ERROR;
    write(fd, message, strlen(message));
    close(fd);
    return SUCCESS;
}
