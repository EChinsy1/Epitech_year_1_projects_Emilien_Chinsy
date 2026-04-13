/*
** EPITECH PROJECT, 2025
** test
** File description:
** test file for mini_printf
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "my.h"

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(mini_printf, basic_use_case, .init = redirect_all_std)
{
    mini_printf("J'ai faim");
    cr_assert_stdout_eq_str("J'ai faim");
}

Test(mini_printf, adding_a_string, .init = redirect_all_std)
{
    mini_printf("J'ai %s faim", "vraiment");
    cr_assert_stdout_eq_str("J'ai vraiment faim");
}

Test(mini_printf, adding_a_char, .init = redirect_all_std)
{
    mini_printf("J'ai %c faim", '\n');
    cr_assert_stdout_eq_str("J'ai \n faim");
}

Test(mini_printf, adding_a_number_with_d, .init = redirect_all_std)
{
    mini_printf("I love baldur's gate %d", 3);
    cr_assert_stdout_eq_str("I love baldur's gate 3");
}

Test(mini_printf, adding_a_number_with_i, .init = redirect_all_std)
{
    mini_printf("I love baldur's gate %i", 3);
    cr_assert_stdout_eq_str("I love baldur's gate 3");
}

Test(mini_printf, writing_a_percent, .init = redirect_all_std)
{
    mini_printf("I have played 100%% of Baldur's gate 3");
    cr_assert_stdout_eq_str("I have played 100% of Baldur's gate 3");
}

Test(mini_printf, all_at_once, .init = redirect_all_std)
{
    mini_printf("%c %s%d a lot %i/%i 100%%", 'I', "love bg", -3, 20, 20);
    cr_assert_stdout_eq_str("I love bg-3 a lot 20/20 100%");
}
