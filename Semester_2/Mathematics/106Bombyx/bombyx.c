/*
** EPITECH PROJECT, 2026
** bombyx
** File description:
** bombyx
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int print_help(void)
{
    printf("USAGE\n");
    printf("\t./106bombyx n [k | i0 i1]\n\n");
    printf("DESCRIPTION\n");
    printf("\tn\tnumber of first generation individuals\n");
    printf("\tk\tgrowth rate from 1 to 4\n");
    printf("\ti0\tinitial generation (included)\n");
    printf("\ti1\tfinal generation (included)\n");
    return (0);
}

static void printer(float k, float pop, int i, int which)
{
    if (which == 1) {
        if (pop < 0) {
            printf("%d 0.00\n", i);
        } else {
            printf("%d %.2f\n", i, pop);
        }
    }
    if (which == 2) {
        if (pop < 0) {
            printf("%.2f 0.00\n", k);
        } else {
            printf("%.2f %.2f\n", k, pop);
        }
    }
}

int with_k(double n, double k)
{
    double pop = n;

    for (int i = 1; i <= 100; ++i) {
        printer(3.0, pop, i, 1);
        pop = k * pop * ((1000 - pop) / 1000);
    }
    return (0);
}

int with_i0_i1(double n, int i0, int i1)
{
    double pop = 0;

    for (double k = 1.00; k <= 4.00; k = k + 0.01) {
        pop = n;
        for (int i = 1; i < i0; ++i)
            pop = k * pop * ((1000 - pop) / 1000);
        for (int i = i0; i <= i1; ++i) {
            printer(k, pop, 0, 2);
            pop = k * pop * ((1000 - pop) / 1000);
        }
    }
    return (0);
}

static int is_a_number(char *str)
{
    int i = 0;

    while (str[i] != '\0') {
        if ((str[i] < '0' || str[i] > '9') && str[i] != '.')
            return (0);
        ++i;
    }
    return (1);
}

int error_handling(int argc, char **argv, char *endptr)
{
    double k = 0;
    double i0 = 0;
    double i1 = 0;

    if ((argc != 3 && argc != 4) || strtold(argv[1], &endptr) < 1
        || is_a_number(argv[1]) == 0)
        return (84);
    if (argc == 3) {
        k = strtold(argv[2], &endptr);
        if (is_a_number(argv[2]) == 0 || k < 1 || k > 4)
            return (84);
        return (0);
    } else {
        i0 = strtold(argv[2], &endptr);
        i1 = strtold(argv[3], &endptr);
        if ((i0 <= 0 || is_a_number(argv[2]) == 0)
            || (i1 <= 0 || is_a_number(argv[3]) == 0) || i1 <= i0)
            return (84);
        return (0);
    }
}

int bombyx(int argc, char **argv)
{
    char *endptr = NULL;

    if (argc == 2 && strcmp(argv[1], "-h") == 0)
        return (print_help());
    if (error_handling(argc, argv, endptr) == 84)
        return (84);
    if (argc == 3)
        return (with_k(strtold(argv[1], &endptr), strtold(argv[2], &endptr)));
    return (with_i0_i1(strtold(argv[1], &endptr),
            strtold(argv[2], &endptr), strtold(argv[3], &endptr)));
}
