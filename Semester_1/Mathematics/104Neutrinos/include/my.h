/*
** EPITECH PROJECT, 2025
** 104neutrinos
** File description:
** Header file for 104neutrinos
*/

#ifndef MY_H
    #define MY_H

    #define BUF_SIZE 1096

int main_loop(int ac, char **av);
int error_handling(int ac, char **av);
int is_num(char *str);
void h_flag(void);
int err_fgets(char *buffer);
long double *store_args(int ac, char **av);
long double *calculate_new_vals(long double *new_av, char *buffer);
long double arithmetic_mean(long double n, long double a, long double new_val);
long double new_root_mean_square(long double n,
    long double rms, long double new_val);
long double harmonic_mean(long double n, long double h, long double new_val);
long double actual_root_mean_square(long double sd, long double a);
long double standard_dev(long double n, long double sd,
    long double a, long double new_val);

#endif
