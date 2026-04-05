/*
** EPITECH PROJECT, 2025
** 104neutrinos
** File description:
** Main file for 104neutrinos
*/

#include "my.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void h_flag(void)
{
    printf("USAGE\n    ./104neutrinos n a h sd\n\n");
    printf("DESCRIPTION\n    n       number of values");
    printf("\n    a       arithmetic mean\n");
    printf("    h       harmonic mean\n    sd      standard deviation\n");
}

int is_num(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] < '0' || str[i] > '9')
            return 84;
    return 0;
}

int error_handling(int ac, char **av)
{
    if (ac != 5)
        return 84;
    for (int i = 1; av[i] != NULL; i++)
        if (is_num(av[i]) == 84)
            return 84;
    return 0;
}
