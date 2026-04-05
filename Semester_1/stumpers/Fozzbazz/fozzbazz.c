/*
** EPITECH PROJECT, 2026
** stumper 3
** File description:
** stumper 3
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "my.h"

int my_strlen(char *str)
{
    int i = 0;

    while (str[i] != '\0')
        ++i;
    return (i);
}

int my_intlen(int nb)
{
    int i = 0;

    if (nb < 0) {
        nb = nb * -1;
        ++i;
    }
    while (nb > 9) {
        nb = nb / 10;
        ++i;
    }
    ++i;
    return (i);
}

int test_arg_validity(char **argv, int num_1, int num_2)
{
    if ((num_1 == 0 && argv[1][0] != '0')
        || (num_2 == 0 && argv[2][0] != '0') || num_1 > num_2)
        return (84);
    if (my_strlen(argv[1]) != (my_intlen(num_1))
        || my_strlen(argv[2]) != (my_intlen(num_2)))
        return (84);
    return (0);
}

int fozzbazz(int argc, char **argv)
{
    int num_1 = 0;
    int num_2 = 0;

    if (argc != 3)
        return (EXIT_ERROR);
    num_1 = atoi(argv[1]);
    num_2 = atoi(argv[2]);
    if (test_arg_validity(argv, num_1, num_2) != 0)
        return (84);
    for (int i = num_1; i <= num_2; ++i){
        if (i % 2 == 0)
            printf("Fozz");
        if (i % 9 == 0)
            printf("Bazz");
        if (i % 2 != 0 && i % 9 != 0)
            printf("%d", i);
        printf("\n");
    }
    return (EXIT_SUCCESS);
}
