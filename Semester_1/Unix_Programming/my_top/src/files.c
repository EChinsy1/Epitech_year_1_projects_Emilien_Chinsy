/*
** EPITECH PROJECT, 2026
** my_top
** File description:
** functions to handle files
*/

#include <asm-generic/errno-base.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

FILE *open_file(char *name)
{
    FILE *file = fopen(name, "r");

    while (file == NULL) {
        return (NULL);
    }
    return (file);
}
