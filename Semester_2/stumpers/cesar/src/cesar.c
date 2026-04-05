/*
** EPITECH PROJECT, 2026
** stumper3
** File description:
** césar
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "my.h"
#include "macro.h"

static int error_handling(int ac, char **av)
{
    if (ac != 4) {
        dprintf(STDERR, "./cesar [flag] [filename/string] [key]\n");
        return ERROR;
    }
    if (strcmp(av[1], FLAG_S) != SUCCESS && strcmp(av[1], FLAG_F) != SUCCESS) {
        dprintf(STDERR, "You need a flag : '-s' or '-f'\n");
        return ERROR;
    }
    return SUCCESS;
}

char *get_buffer(char **argv)
{
    char *buffer = NULL;

    if (strcmp(argv[1], FLAG_F) == SUCCESS)
        buffer = open_file(argv[2]);
    if (strcmp(argv[1], FLAG_S) == SUCCESS)
        buffer = strdup(argv[2]);
    if (buffer == NULL)
        return NULL;
    return buffer;
}

int free_all_and_return(char *buffer, char *result, int return_value)
{
    free(buffer);
    free(result);
    return (return_value);
}

int cesar(int argc, char **argv)
{
    char *result = NULL;
    char *buffer = NULL;
    int n = 0;
    int return_value = 0;

    if (error_handling(argc, argv) == ERROR)
        return EXIT_ERROR;
    n = strtol(argv[3], NULL, BASE);
    if (n == 0 && argv[3][0] != ZERO_C)
        return EXIT_ERROR;
    buffer = get_buffer(argv);
    if (buffer == NULL)
        return EXIT_ERROR;
    result = decrypt(buffer, n % ALPH_SIZE);
    if (result == NULL) {
        free(buffer);
        return EXIT_ERROR;
    }
    return_value = crypt_in_file(result);
    return free_all_and_return(buffer, result, return_value);
}
