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

Test(error_handling, too_many_args)
{
    char *argv[5] = {"./106bombyx", "1", "2", "3", "4"};
    cr_assert(error_handling(5, argv) == 84);
}

Test(error_handling, not_enough_args)
{
    char *argv[2] = {"./106bombyx", "1"};
    cr_assert(error_handling(2, argv) == 84);
}

Test(error_handling, four_args)
{
    char *argv[4] = {"./106bombyx", "1", "2", "3"};
    cr_assert(error_handling(4, argv) == 0);
}

Test(error_handling, three_args)
{
    char *argv[3] = {"./106bombyx", "1", "2"};
    cr_assert(error_handling(3, argv) == 0);
}

Test(error_handling, k_too_small)
{
    char *argv[3] = {"./106bombyx", "1", "0.5"};
    cr_assert(error_handling(3, argv) == 84);
}

Test(error_handling, k_too_big)
{
    char *argv[3] = {"./106bombyx", "1", "5"};
    cr_assert(error_handling(3, argv) == 84);
}

Test(error_handling, n_is_zero)
{
    char *argv[3] = {"./106bombyx", "0", "2"};
    cr_assert(error_handling(3, argv) == 84);
}

Test(error_handling, n_is_zero_four)
{
    char *argv[4] = {"./106bombyx", "0", "2", "3"};
    cr_assert(error_handling(4, argv) == 84);
}

Test(error_handling, i0_bigger_than_i1)
{
    char *argv[4] = {"./106bombyx", "1", "3", "2"};
    cr_assert(error_handling(4, argv) == 84);
}

Test(error_handling, i0_not_a_number)
{
    char *argv[4] = {"./106bombyx", "1", "fake", "2"};
    cr_assert(error_handling(4, argv) == 84);
}

Test(error_handling, i1_not_a_number)
{
    char *argv[4] = {"./106bombyx", "1", "1", "fake"};
    cr_assert(error_handling(4, argv) == 84);
}

Test(bombyx, print_help, .init = redirect_all_std)
{
    char *argv[2] = {"./106bombyx", "-h"};
    int result = bombyx(2, argv);

    cr_assert(result == 0);
}

Test(bombyx, error, .init = redirect_all_std)
{
    char *argv[2] = {"./106bombyx", "hello"};
    int result = bombyx(2, argv);

    cr_assert(result == 84);
}

Test(bombyx, three_args, .init = redirect_all_std)
{
    char *argv[3] = {"./106bombyx", "10", "3.3"};
    int result = bombyx(3, argv);

    cr_assert(result == 0);
}

Test(bombyx, four_args_args, .init = redirect_all_std)
{
    char *argv[4] = {"./106bombyx", "10", "10000", "10010"};
    int result = bombyx(4, argv);

    cr_assert(result == 0);
}

