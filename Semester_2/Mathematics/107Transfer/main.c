/*
** EPITECH PROJECT, 2026
** transfer
** File description:
** transfer
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static int check_chars(char *string)
{
    int i = 0;
    int len = strlen(string);
    int num = 0;

    while (string[i] != '\0') {
        if ((string[i] < '0' || string[i] > '9') &&
            string[i] != '*' && string[i] != '-')
            return (0);
        ++i;
    }
    i = 0;
    while (string[i] != '\0') {
        if (string[i] == '*' || string[i] == '-')
            ++num;
        ++i;
    }
    if (num == len)
        return (0);
    return (1);
}

static int check_args(int argc, char **argv)
{
    if (argc % 2 == 0 || argc <= 1)
        return (84);
    for (int i = 1; i < argc; ++i)
        if (check_chars(argv[i]) != 1)
            return (84);
    return (0);
}

static int make_value(int i, int *curr, char **argv)
{
    int value = 0;

    if (*curr != 0)
        ++(*curr);
    value = atoi(&argv[i][(*curr)]);
    while (argv[i][*curr] != '*' && argv[i][*curr] != '\0')
        ++(*curr);
    return (value);
}

static long long int **make_factors(int argc, char **argv)
{
    int curr = 0;
    long long int **factors = calloc(sizeof(long long int *), argc);
    int j = 0;

    if (!factors)
        return (NULL);
    factors[argc - 1] = NULL;
    for (int i = 1; i < argc; ++i) {
        factors[i - 1] = calloc(sizeof(long long int), strlen(argv[i]) + 1);
        for (; argv[i][curr] != '\0'; ++j)
            factors[i - 1][j] = make_value(i, &curr, argv);
        factors[i - 1][j] = -712534;
        j = 0;
        curr = 0;
    }
    return (factors);
}

long double compute_value(long double value, long long int *factors)
{
    long double aled = 0;

    for (int i = 0; factors[i] != -712534; ++i) {
        aled += pow(value, i) * factors[i];
    }
    return (aled);
}

int math(long double value, long long int **factors)
{
    long double result = 1;
    long double numerator = 0;
    long double denominator = 0;

    for (int i = 0; factors[i] != NULL; ++i) {
        if (i % 2 == 0)
            numerator = compute_value(value, factors[i]);
        else {
            denominator = compute_value(value, factors[i]);
        }
        if (i % 2 != 0 && denominator != 0)
            result *= (numerator / denominator);
    }
    printf("%.3Lf -> %.5Lf\n", value, result);
    return (0);
}

int check_current_factor(long long int *factors)
{
    long long int sum = 0;

    if (factors[0] == 0 && factors[1] == -712534)
        return (84);
    return (0);
}

int check_factors(long long int **factors, int argc)
{
    int result = 0;

    for (int i = 1; i < (argc - 1); ++i) {
        result = check_current_factor(factors[i]);
        if (result == 84 && i % 2 != 0) {
            return (84);
        }
    }
    return (1);
}

int main(int argc, char **argv)
{
    long long int **factors = ((void *)0);

    if (check_args(argc, argv) != 0)
        return (84);
    factors = make_factors(argc, argv);
    if (check_factors(factors, argc) != 1)
        return (84);
    for (int i = 0; i <= 1000; ++i) {
        math((i / 1000.0), factors);
    }
    for (int i = 0; factors[i] != NULL; ++i)
        free(factors[i]);
    free(factors);
}
