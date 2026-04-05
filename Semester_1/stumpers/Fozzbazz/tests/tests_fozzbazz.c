/*
** EPITECH PROJECT, 2026
** tests
** File description:
** tests
*/

#include <criterion/criterion.h>
#include "../my.h"

Test(fozzbazz, normal_args)
{
    char *argv[3] = {"./fozzbazz", "1", "10"};
    cr_assert(fozzbazz(3, argv) == 0);
}

Test(fozzbazz, no_args)
{
    char *argv[1] = {"./fozzbazz"};
    cr_assert(fozzbazz(1, argv) == 84);
}

Test(fozzbazz, wrong_args)
{
    char *argv[3] = {"./fozzbazz", "wrong", "args"};
    cr_assert(fozzbazz(3, argv) == 84);
}

Test(fozzbazz, wrong_args_2)
{
    char *argv[3] = {"./fozzbazz", "3", "args"};
    cr_assert(fozzbazz(3, argv) == 84);
}

Test(fozzbazz, 1_bigger_than_two)
{
    char *argv[3] = {"./fozzbazz", "2", "1"};
    cr_assert(fozzbazz(3, argv) == 84);
}
