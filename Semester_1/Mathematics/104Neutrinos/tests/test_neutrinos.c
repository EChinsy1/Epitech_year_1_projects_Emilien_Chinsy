/*
** EPITECH PROJECT, 2025
** test
** File description:
** test file for 101_pong
** A few tests will have weird int conversions,
** this is because we only print the float with two precision,
** And I am not going to redo the math as the function I am testing
** only returns the math so if the func is wrong the test would pass
** So it would be useless
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <stdio.h>
#include "my.h"

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(arithmetic_mean, basic_use_case)
{
    long double result = arithmetic_mean(12000, 297514, 299042);

    if (result < 297514.135 && result > 297514.125) {
        cr_assert_eq(1, 1);
    } else {
        cr_assert_eq(1, 0);
    }
}

Test(standard_dev, basic_use_case)
{
    long double result = standard_dev(12000, 4363, 297514, 299042);

    if (result < 4362.845 && result > 4362.835) {
        cr_assert_eq(1, 1);
    } else {
        cr_assert_eq(1, 0);
    }
}

Test(harmonic_mean, basic_use_case)
{
    long double result = harmonic_mean(12000, 297912, 299042);

    if (result < 297912.095 && result > 297912.085) {
        cr_assert_eq(1, 1);
    } else {
        cr_assert_eq(1, 0);
    }
}

Test(new_rms, basic_use_case)
{
    long double a = arithmetic_mean(12000, 297514, 299042);
    long double sd = standard_dev(12000, 4363, 297514, 299042);
    long double result = actual_root_mean_square(a, sd);

    if (result > 297546.100 && result < 297546.150) {
        cr_assert_eq(1, 1);
    } else {
        cr_assert_eq(1, 0);
    }
}

Test(is_num, is_a_number)
{
    char *num = "2";
    int result = is_num(num);
    cr_assert_eq(result, 0);
}


Test(is_num, is_not_a_number)
{
    char *num = "nan";
    int result = is_num(num);
    cr_assert_eq(result, 84);
}

Test(error_handling, basic_call)
{
    char *argv[5] = {"./104neutrinos", "1", "2", "3", "4"};
    int result = error_handling(5, argv);
    cr_assert_eq(result, 0);
}

Test(error_handling, not_five_args)
{
    char *argv[6] = {"./104neutrinos", "1", "2", "3", "4", "5"};
    int result = error_handling(6, argv);
    cr_assert_eq(result, 84);
}

Test(error_handling, not_num_arg)
{
    char *argv[5] = {"./104neutrinos", "1", "not_num", "3", "4"};
    int result = error_handling(5, argv);
    cr_assert_eq(result, 84);
}

Test(err_fgets, num)
{
    char *str = "34";
    int result = err_fgets(str);
    cr_assert_eq(result, 0);
}

Test(err_fgets, word)
{
    char *str = "hello";
    int result = err_fgets(str);
    cr_assert_eq(result, 84);
}

Test(store_args, store_args)
{
    char *argv[5] = {"./104neutrinos", "12000", "297514", "297912", "4363"};
    long double *result = store_args(5, argv);

    if (result[0] == 12000.0 && result[1] == 297514.0 && result[2] == 297912.0 && result[3] == 4363.0)
        cr_assert_eq(1, 1);
    else
        cr_assert_eq(0, 1);
}

Test(calculate_new_vals, calculate_new_vals)
{
    char *argv[5] = {"./104neutrinos", "12000", "297514", "297912", "4363"};
    long double *new_av = store_args(5, argv);
    long double *result = calculate_new_vals(new_av, "299042");
    if(result[0] == 12001.0 && result[1] >= 297514.127 && result[1] <= 297514.128 && result[2] <= 297912.1 && result[2] >= 297912.09 && result[3] <= 4362.85 && result[3] >= 4362.84 && result[4] >= 297546.11 && result[4] <= 297546.12)
        cr_assert_eq(1, 1);
    else
        cr_assert_eq(1, 0);
}
