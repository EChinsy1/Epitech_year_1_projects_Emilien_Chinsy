/*
** EPITECH PROJECT, 2026
** tests
** File description:
** tests
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../my.h"

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(my_putchar, it_puts_chars, .init = redirect_all_std)
{
    my_putchar('a');
    cr_assert_stdout_eq_str("a");
}

Test(number_printer, o_is_zero, .init = redirect_all_std)
{
    number_printer('o');
    cr_assert_stdout_eq_str("0");
}

Test(number_printer, O_is_zero, .init = redirect_all_std)
{
    number_printer('O');
    cr_assert_stdout_eq_str("0");
}

Test(number_printer, i_is_one, .init = redirect_all_std)
{
    number_printer('i');
    cr_assert_stdout_eq_str("1");
}

Test(number_printer, I_is_one, .init = redirect_all_std)
{
    number_printer('I');
    cr_assert_stdout_eq_str("1");
}

Test(number_printer, u_is_two, .init = redirect_all_std)
{
    number_printer('u');
    cr_assert_stdout_eq_str("2");
}

Test(number_printer, U_is_two, .init = redirect_all_std)
{
    number_printer('U');
    cr_assert_stdout_eq_str("2");
}

Test(number_printer, e_is_three, .init = redirect_all_std)
{
    number_printer('e');
    cr_assert_stdout_eq_str("3");
}

Test(number_printer, E_is_three, .init = redirect_all_std)
{
    number_printer('E');
    cr_assert_stdout_eq_str("3");
}

Test(number_printer, a_is_four, .init = redirect_all_std)
{
    number_printer('a');
    cr_assert_stdout_eq_str("4");
}

Test(number_printer, A_is_four, .init = redirect_all_std)
{
    number_printer('A');
    cr_assert_stdout_eq_str("4");
}

Test(number_printer, y_is_five, .init = redirect_all_std)
{
    number_printer('y');
    cr_assert_stdout_eq_str("5");
}

Test(number_printer, Y_is_five, .init = redirect_all_std)
{
    number_printer('Y');
    cr_assert_stdout_eq_str("5");
}

Test(number_printer, random_is_nothing, .init = redirect_all_std)
{
    number_printer('P');
    cr_assert_stdout_eq_str("");
}

Test(normal_letter_printer, capitalizes_when_prev_mod_two_is_zero, .init = redirect_all_std)
{
    normal_letter_printer('a', 2);
    normal_letter_printer('g', 0);
    normal_letter_printer('z', 4);
    cr_assert_stdout_eq_str("AGZ");
}

Test(normal_letter_printer, minimizes_when_prev_mod_two_is_one, .init = redirect_all_std)
{
    normal_letter_printer('A', 3);
    normal_letter_printer('G', 1);
    normal_letter_printer('Z', 5);
    cr_assert_stdout_eq_str("agz");
}

Test(normal_letter_printer, ignores_non_letters, .init = redirect_all_std)
{
    char result[5];
    
    normal_letter_printer('a' - 1, 2);
    normal_letter_printer('z' + 1, 3);
    normal_letter_printer('z' + 1, 2);
    normal_letter_printer('a' - 1, 3);
    result[0] = 'a' - 1;
    result[1] = 'z' + 1;
    result[2] = 'z' + 1;
    result[3] = 'a' - 1;
    cr_assert_stdout_eq_str(result);
}

Test(pretty_printer, normal_use_case, .init = redirect_all_std)
{
    pretty_printer("santa Tomato!KETCHUP/");
    cr_assert_stdout_eq_str("S4Nt4 T0M4T0!k3tCh2p/\n");
}

Test(geek_name_formatter, argc_is_not_2, .init = redirect_all_std)
{
    cr_assert(geek_name_formatter(1, NULL) == 84);
}

Test(geek_name_formatter, argc_is_2, .init = redirect_all_std)
{
    char *argv[2] = {"./geekNameFormatter", "santa Tomato!KETCHUP/"};

    cr_assert(geek_name_formatter(2, argv) == 0);
}

Test(geek_name_formatter, argc_is_2_output, .init = redirect_all_std)
{
    char *argv[2] = {"./geekNameFormatter", "santa Tomato!KETCHUP/"};

    geek_name_formatter(2, argv);
    cr_assert_stdout_eq_str("S4Nt4 T0M4T0!k3tCh2p/\n");
}

Test(geek_name_formatter, argv_2_is_null, .init = redirect_all_std)
{
    char *argv[2] = {"./geekNameFormatter", NULL};

    cr_assert(geek_name_formatter(2, argv) == 84);
}

Test(geek_name_formatter, usage_prints, .init = redirect_all_std)
{
    char *argv[2] = {"./geekNameFormatter", NULL};

    geek_name_formatter(1, argv);
    cr_assert_stderr_eq_str("Usage: geekNameFormatter string\n");
}
