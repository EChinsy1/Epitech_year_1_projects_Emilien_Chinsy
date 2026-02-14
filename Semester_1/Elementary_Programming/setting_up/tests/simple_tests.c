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
#include "my.h"

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(setting_up, too_many_args)
{
    char *argv[4] = {"./setting_up", "6", "..o..", "7"};
    int result = setting_up(4, argv);
    cr_assert_eq(result, 84);
}

Test(setting_up, not_enough_args)
{
    char *argv[1] = {"./setting_up"};
    int result = setting_up(1, argv);
    cr_assert_eq(result, 84);
}

Test(setting_up, empty_string_generate)
{
    char *argv[3] = {"./setting_up", "", "..o.."};
    int result = setting_up(3, argv);
    cr_assert_eq(result, 84);
}

Test(setting_up, negative_generate)
{
    char *argv[3] = {"./setting_up", "-5", "..o.."};
    int result = setting_up(3, argv);
    cr_assert_eq(result, 84);
}

Test(setting_up, zero_generate)
{
    char *argv[3] = {"./setting_up", "0", "..o.."};
    int result = setting_up(3, argv);
    cr_assert_eq(result, 0);
}

Test(setting_up, empty_pattern_generate)
{
    char *argv[3] = {"./setting_up", "6", ""};
    int result = setting_up(3, argv);
    cr_assert_eq(result, 84);
}

Test(setting_up, empty_both_generate)
{
    char *argv[3] = {"./setting_up", "", ""};
    int result = setting_up(3, argv);
    cr_assert_eq(result, 84);
}

Test(setting_up, inexistent_open)
{
    char *argv[2] = {"./setting_up", "fake.txt"};
    int result = setting_up(2, argv);
    cr_assert_eq(result, 84);
}

Test(setting_up, no_first_line_open)
{
    char *argv[2] = {"./setting_up", "tests/empty_first_line.txt"};
    int result = setting_up(2, argv);
    cr_assert_eq(result, 84);
}

Test(setting_up, file_contains_a_open)
{
    char *argv[2] = {"./setting_up", "tests/first_contains_a.txt"};
    int result = setting_up(2, argv);
    cr_assert_eq(result, 84);
}

Test(setting_up, valid_file_open, .init = redirect_all_std)
{
    char *argv[2] = {"./setting_up", "tests/valid_file.txt"};
    int result = setting_up(2, argv);
    cr_assert_eq(result, 0);
}

Test(setting_up, valid_generate, .init = redirect_all_std)
{
    char *argv[3] = {"./setting_up", "6", "..o.."};
    int result = setting_up(3, argv);
    cr_assert_eq(result, 0);
}

Test(file_validaition, valid_generate, .init = redirect_all_std)
{
    char *argv[3] = {"./setting_up", "6", "..o.."};
    int result = setting_up(3, argv);
    cr_assert_eq(result, 0);
}
