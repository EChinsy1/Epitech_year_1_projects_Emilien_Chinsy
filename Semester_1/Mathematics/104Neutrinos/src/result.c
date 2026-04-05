/*
** EPITECH PROJECT, 2025
** 104neutrinos
** File description:
** File that contains the main function
*/

#include "my.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long double *calculate_new_vals(long double *new_av, char *buffer)
{
    long double n = new_av[0];
    long double a = new_av[1];
    long double h = new_av[2];
    long double sd = new_av[3];
    long double new_val = strtold(buffer, NULL);
    long double *final_value = calloc(sizeof(long double), 6);

    final_value[0] = n + 1;
    final_value[1] = arithmetic_mean(n, a, new_val);
    final_value[2] = harmonic_mean(n, h, new_val);
    final_value[3] = standard_dev(n, sd, a, new_val);
    final_value[4] = actual_root_mean_square(final_value[3], final_value[1]);
    free(new_av);
    return final_value;
}

long double *store_args(int ac, char **av)
{
    long double *new_args = calloc(sizeof(long double), 5);

    for (int i = 0; i < ac - 1; i++)
        new_args[i] = strtold(av[i + 1], NULL);
    return new_args;
}

int err_fgets(char *buffer)
{
    for (int i = 0; buffer[i] != '\0'; i++) {
        if ((buffer[i] < '0' || buffer[i] > '9') && buffer[i] != '\n'
            && buffer[i] != 'E' && buffer[i] != 'N' && buffer[i] != 'D')
            return 84;
    }
    return 0;
}

void print_result(long double *final_value)
{
    printf("    Number of values:   %.0Lf\n", final_value[0]);
    printf("    Standard deviation: %.2Lf\n", final_value[3]);
    printf("    Arithmetic mean:    %.2Lf\n", final_value[1]);
    printf("    Root mean square:   %.2Lf\n", final_value[4]);
    printf("    Harmonic mean:      %.2Lf\n\n", final_value[2]);
}

int main_loop(int ac, char **av)
{
    char *buffer = calloc(sizeof(char), BUF_SIZE);
    long double *final_value = store_args(ac, av);

    printf("Enter next value: ");
    fgets(buffer, BUF_SIZE, stdin);
    if (err_fgets(buffer) == 84)
        return 84;
    while (strcmp(buffer, "END\n") != 0) {
        final_value = calculate_new_vals(final_value, buffer);
        print_result(final_value);
        free(buffer);
        buffer = calloc(sizeof(char), BUF_SIZE);
        printf("Enter next value: ");
        fgets(buffer, BUF_SIZE, stdin);
        if (err_fgets(buffer) == 84)
            return 84;
    }
    free(final_value);
    free(buffer);
    return 0;
}
