/*
** EPITECH PROJECT, 2025
** test
** File description:
** test file for my_printf
*/
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "my.h"

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(my_printf, basic_use_case, .init = redirect_all_std)
{
    my_printf("J'ai faim");
    cr_assert_stdout_eq_str("J'ai faim");
}

Test(my_printf, return_value, .init = redirect_all_std)
{
    int value = my_printf("J'ai faim");

    cr_assert_eq(value, 9);
}

Test(my_printf, return_value_args, .init = redirect_all_std)
{
    int value = my_printf("J'ai %s", "faim");

    cr_assert_eq(value, 9);
}

Test(my_printf, return_value_empty, .init = redirect_all_std)
{
    int value = my_printf("");

    cr_assert_eq(value, 0);
}

Test(my_printf, adding_a_string, .init = redirect_all_std)
{
    my_printf("J'ai %s faim", "vraiment");
    cr_assert_stdout_eq_str("J'ai vraiment faim");
}

Test(my_printf, adding_a_char, .init = redirect_all_std)
{
    my_printf("J'ai %c faim", '\n');
    cr_assert_stdout_eq_str("J'ai \n faim");
}

Test(my_printf, adding_a_number_with_d, .init = redirect_all_std)
{
    my_printf("I love baldur's gate %d", 3);
    cr_assert_stdout_eq_str("I love baldur's gate 3");
}

Test(my_printf, adding_a_number_with_i, .init = redirect_all_std)
{
    my_printf("I love baldur's gate %i", 3);
    cr_assert_stdout_eq_str("I love baldur's gate 3");
}

Test(my_printf, writing_a_percent, .init = redirect_all_std)
{
    my_printf("I have played 100%% of Baldur's gate 3");
    cr_assert_stdout_eq_str("I have played 100% of Baldur's gate 3");
}

Test(my_printf, u_pos, .init = redirect_all_std)
{
    my_printf("%u\n", 2345);
    cr_assert_stdout_eq_str("2345\n");
}

Test(my_printf, u_zero, .init = redirect_all_std)
{
    my_printf("%u\n", 0);
    cr_assert_stdout_eq_str("0\n");
}

Test(my_printf, u_neg, .init = redirect_all_std)
{
    my_printf("%u\n", -123);
    cr_assert_stdout_eq_str("4294967173\n");
}

Test(my_printf, o_pos, .init = redirect_all_std)
{
    my_printf("%o\n", 2345);
    cr_assert_stdout_eq_str("4451\n");
}

Test(my_printf, o_zero, .init = redirect_all_std)
{
    my_printf("%o\n", 0);
    cr_assert_stdout_eq_str("0\n");
}

Test(my_printf, o_neg, .init = redirect_all_std)
{
    my_printf("%o\n", -123);
    cr_assert_stdout_eq_str("37777777605\n");
}

Test(my_printf, o_hash, .init = redirect_all_std)
{
    my_printf("%#o\n", 2345);
    cr_assert_stdout_eq_str("04451\n");
}

Test(my_printf, x_pos, .init = redirect_all_std)
{
    my_printf("%x\n", 2345);
    cr_assert_stdout_eq_str("929\n");
}

Test(my_printf, x_zero, .init = redirect_all_std)
{
    my_printf("%x\n", 0);
    cr_assert_stdout_eq_str("0\n");
}

Test(my_printf, x_neg, .init = redirect_all_std)
{
    my_printf("%x\n", -123);
    cr_assert_stdout_eq_str("ffffff85\n");
}

Test(my_printf, x_hash, .init = redirect_all_std)
{
    my_printf("%#x\n", 2345);
    cr_assert_stdout_eq_str("0x929\n");
}

Test(my_printf, X_pos, .init = redirect_all_std)
{
    my_printf("%X\n", 2345);
    cr_assert_stdout_eq_str("929\n");
}

Test(my_printf, X_zero, .init = redirect_all_std)
{
    my_printf("%X\n", 0);
    cr_assert_stdout_eq_str("0\n");
}

Test(my_printf, X_neg, .init = redirect_all_std)
{
    my_printf("%X\n", -123);
    cr_assert_stdout_eq_str("FFFFFF85\n");
}

Test(my_printf, X_hash, .init = redirect_all_std)
{
    my_printf("%#X\n", 2345);
    cr_assert_stdout_eq_str("0X929\n");
}

Test(my_printf, e_pos, .init = redirect_all_std)
{
    my_printf("%e\n", 230.4567);
    cr_assert_stdout_eq_str("2.304567e+02\n");
}

Test(my_printf, e_precision, .init = redirect_all_std)
{
    my_printf("%.3e\n", 230.4567);
    cr_assert_stdout_eq_str("2.305e+02\n");
}

Test(my_printf, e_zero, .init = redirect_all_std)
{
    my_printf("%e\n", 0.0);
    cr_assert_stdout_eq_str("0.000000e+00\n");
}

Test(my_printf, e_neg, .init = redirect_all_std)
{
    my_printf("%e\n", -123.876);
    cr_assert_stdout_eq_str("-1.238760e+02\n");
}

Test(my_printf, e_hash, .init = redirect_all_std)
{
    my_printf("%#.0e\n", 230.4567);
    cr_assert_stdout_eq_str("2.e+02\n");
}

Test(my_printf, E_pos, .init = redirect_all_std)
{
    my_printf("%E\n", 230.4567);
    cr_assert_stdout_eq_str("2.304567E+02\n");
}

Test(my_printf, E_precision, .init = redirect_all_std)
{
    my_printf("%.3E\n", 230.4567);
    cr_assert_stdout_eq_str("2.305E+02\n");
}

Test(my_printf, E_zero, .init = redirect_all_std)
{
    my_printf("%E\n", 0.0);
    cr_assert_stdout_eq_str("0.000000E+00\n");
}

Test(my_printf, E_neg, .init = redirect_all_std)
{
    my_printf("%E\n", -123.876);
    cr_assert_stdout_eq_str("-1.238760E+02\n");
}

Test(my_printf, E_hash, .init = redirect_all_std)
{
    my_printf("%#.0E\n", 230.4567);
    cr_assert_stdout_eq_str("2.E+02\n");
}

Test(my_printf, f_pos, .init = redirect_all_std)
{
    my_printf("%f\n", 230.4567);
    cr_assert_stdout_eq_str("230.456700\n");
}

Test(my_printf, f_precision, .init = redirect_all_std)
{
    my_printf("%.3f\n", 230.4567);
    cr_assert_stdout_eq_str("230.457\n");
}

Test(my_printf, f_zero, .init = redirect_all_std)
{
    my_printf("%f\n", 0.0);
    cr_assert_stdout_eq_str("0.000000\n");
}

Test(my_printf, f_neg, .init = redirect_all_std)
{
    my_printf("%f\n", -123.876);
    cr_assert_stdout_eq_str("-123.876000\n");
}

Test(my_printf, f_hash, .init = redirect_all_std)
{
    my_printf("%#.0f\n", 230.4567);
    cr_assert_stdout_eq_str("230.\n");
}

Test(my_printf, F_pos, .init = redirect_all_std)
{
    my_printf("%F\n", 230.4567);
    cr_assert_stdout_eq_str("230.456700\n");
}

Test(my_printf, F_precision, .init = redirect_all_std)
{
    my_printf("%.3f\n", 230.4567);
    cr_assert_stdout_eq_str("230.457\n");
}

Test(my_printf, F_zero, .init = redirect_all_std)
{
    my_printf("%F\n", 0.0);
    cr_assert_stdout_eq_str("0.000000\n");
}

Test(my_printf, F_neg, .init = redirect_all_std)
{
    my_printf("%F\n", -123.876);
    cr_assert_stdout_eq_str("-123.876000\n");
}

Test(my_printf, F_hash, .init = redirect_all_std)
{
    my_printf("%#.0F\n", 230.4567);
    cr_assert_stdout_eq_str("230.\n");
}

Test(my_printf, g_float_pos, .init = redirect_all_std)
{
    my_printf("%g\n", 3.14);
    cr_assert_stdout_eq_str("3.14\n");
}

Test(my_printf, g_e_pos, .init = redirect_all_std)
{
    my_printf("%g\n", 0.00000000024);
    cr_assert_stdout_eq_str("2.4e-10\n");
}

Test(my_printf, g_float_neg, .init = redirect_all_std)
{
    my_printf("%g\n", -3.14);
    cr_assert_stdout_eq_str("-3.14\n");
}

Test(my_printf, g_e_neg, .init = redirect_all_std)
{
    my_printf("%g\n", -0.00000000024);
    cr_assert_stdout_eq_str("-2.4e-10\n");
}

Test(my_printf, g_zero, .init = redirect_all_std)
{
    my_printf("%g\n", 0.0);
    cr_assert_stdout_eq_str("0\n");
}

Test(my_printf, g_less_than_one, .init = redirect_all_std)
{
    my_printf("%g\n", 0.4);
    cr_assert_stdout_eq_str("0.4\n");
}

Test(my_printf, g_e_pos_more_than_one, .init = redirect_all_std)
{
    my_printf("%g\n", 39874678.123);
    cr_assert_stdout_eq_str("3.98747e+07\n");
}

Test(my_printf, g_e_pos_less_than_zero, .init = redirect_all_std)
{
    my_printf("%g\n", -39874678.123);
    cr_assert_stdout_eq_str("-3.98747e+07\n");
}

Test(my_printf, g_hash, .init = redirect_all_std)
{
    my_printf("%#.1g\n", 0.0);
    cr_assert_stdout_eq_str("0.\n");
}

Test(my_printf, G_e_pos, .init = redirect_all_std)
{
    my_printf("%G\n", 0.00000000024);
    cr_assert_stdout_eq_str("2.4E-10\n");
}

Test(my_printf, plus_flag_int, .init = redirect_all_std)
{
    my_printf("%+d\n", 42);
    cr_assert_stdout_eq_str("+42\n");
}

Test(my_printf, plus_flag_float, .init = redirect_all_std)
{
    my_printf("%+f\n", 42.0);
    cr_assert_stdout_eq_str("+42.000000\n");
}

Test(my_printf, space_flag_not_str, .init = redirect_all_std)
{
    my_printf("% s\n", "meg");
    cr_assert_stdout_eq_str("meg\n");
}

Test(my_printf, space_flag_int, .init = redirect_all_std)
{
    my_printf("% d\n", 3);
    cr_assert_stdout_eq_str(" 3\n");
}

Test(my_printf, space_flag_float, .init = redirect_all_std)
{
    my_printf("% f\n", 3.0);
    cr_assert_stdout_eq_str(" 3.000000\n");
}

Test(my_printf, space_flag_not_char, .init = redirect_all_std)
{
    my_printf("% c\n", 'm');
    cr_assert_stdout_eq_str("m\n");
}

Test(my_printf, space_flag_width_int, .init = redirect_all_std)
{
    my_printf("% 5d\n", 3);
    cr_assert_stdout_eq_str("    3\n");
}

Test(my_printf, space_flag_width_float, .init = redirect_all_std)
{
    my_printf("% 10f\n", 3.0);
    cr_assert_stdout_eq_str("  3.000000\n");
}

Test(my_printf, width_str, .init = redirect_all_std)
{
    my_printf("%5s\n", "bob");
    cr_assert_stdout_eq_str("  bob\n");
}

Test(my_printf, width_char, .init = redirect_all_std)
{
    my_printf("%5c\n", 'F');
    cr_assert_stdout_eq_str("    F\n");
}

Test(my_printf, width_int, .init = redirect_all_std)
{
    my_printf("%5d\n", 3);
    cr_assert_stdout_eq_str("    3\n");
}

Test(my_printf, width_float, .init = redirect_all_std)
{
    my_printf("%10f\n", 3.0);
    cr_assert_stdout_eq_str("  3.000000\n");
}

Test(my_printf, minus_flag_width_str, .init = redirect_all_std)
{
    my_printf("%-5s\n", "bob");
    cr_assert_stdout_eq_str("bob  \n");
}

Test(my_printf, minus_flag_width_char, .init = redirect_all_std)
{
    my_printf("%-5c\n", 'F');
    cr_assert_stdout_eq_str("F    \n");
}

Test(my_printf, minus_flag_width_int, .init = redirect_all_std)
{
    my_printf("%-5d\n", 3);
    cr_assert_stdout_eq_str("3    \n");
}

Test(my_printf, minus_flag_width_float, .init = redirect_all_std)
{
    my_printf("%-10f\n", 3.0);
    cr_assert_stdout_eq_str("3.000000  \n");
}

Test(my_printf, zero_flag_width_d, .init = redirect_all_std)
{
    my_printf("%010d\n", 394);
    cr_assert_stdout_eq_str("0000000394\n");
}

Test(my_printf, zero_flag_width_i, .init = redirect_all_std)
{
    my_printf("%010i\n", 394);
    cr_assert_stdout_eq_str("0000000394\n");
}

Test(my_printf, zero_flag_width_u, .init = redirect_all_std)
{
    my_printf("%010u\n", 394);
    cr_assert_stdout_eq_str("0000000394\n");
}

Test(my_printf, zero_flag_width_o, .init = redirect_all_std)
{
    my_printf("%010o\n", 394);
    cr_assert_stdout_eq_str("0000000612\n");
}

Test(my_printf, zero_flag_width_x, .init = redirect_all_std)
{
    my_printf("%#010x\n", 394);
    cr_assert_stdout_eq_str("0x0000018a\n");
}

Test(my_printf, zero_flag_width_X, .init = redirect_all_std)
{
    my_printf("%#010X\n", 394);
    cr_assert_stdout_eq_str("0X0000018A\n");
}

Test(my_printf, zero_flag_width_f, .init = redirect_all_std)
{
    my_printf("%010f\n", 3.94);
    cr_assert_stdout_eq_str("003.940000\n");
}

Test(my_printf, zero_flag_width_F, .init = redirect_all_std)
{
    my_printf("%010F\n", 3.94);
    cr_assert_stdout_eq_str("003.940000\n");
}

Test(my_printf, zero_flag_width_e, .init = redirect_all_std)
{
    my_printf("%010e\n", 3.94);
    cr_assert_stdout_eq_str("3.940000e+00\n");
}

Test(my_printf, zero_flag_width_E, .init = redirect_all_std)
{
    my_printf("%010E\n", 3.94);
    cr_assert_stdout_eq_str("3.940000E+00\n");
}

Test(my_printf, zero_flag_width_g, .init = redirect_all_std)
{
    my_printf("%010g\n", 3.94);
    cr_assert_stdout_eq_str("0000003.94\n");
}

Test(my_printf, zero_flag_width_G, .init = redirect_all_std)
{
    my_printf("%010G\n", 3.94);
    cr_assert_stdout_eq_str("0000003.94\n");
}

Test(my_printf, zero_flag_width_a, .init = redirect_all_std)
{
    my_printf("%010a\n", 3.94);
    cr_assert_stdout_eq_str("0x1.f851eb851eb85p+1\n");
}

Test(my_printf, zero_flag_width_A, .init = redirect_all_std)
{
    my_printf("%010A\n", 3.94);
    cr_assert_stdout_eq_str("0X1.F851EB851EB85P+1\n");
}

Test(my_printf, inexsitent_specifier, .init = redirect_all_std)
{
    my_printf("%k\n", 3);
    cr_assert_stdout_eq_str("%k\n");
}

Test(my_printf, impossible_format, .init = redirect_all_std)
{
    my_printf("%000000 #-+30.37lllc\n", 'c');
    cr_assert_stdout_eq_str("%#-+30.37lc\n");
}

Test(my_printf, star_width_and_star_precision, .init = redirect_all_std)
{
    my_printf("%*.*d\n", 10, 5, 3);
    cr_assert_stdout_eq_str("     00003\n");
}

Test(my_printf, length_int_l, .init = redirect_all_std)
{
    my_printf("%ld\n", 2147483648);
    cr_assert_stdout_eq_str("2147483648\n");
}

Test(my_printf, length_int_ll, .init = redirect_all_std)
{
    my_printf("%lld\n", 9223372036854775807);
    cr_assert_stdout_eq_str("9223372036854775807\n");
}

Test(my_printf, length_int_q, .init = redirect_all_std)
{
    my_printf("%qd\n", 9223372036854775807);
    cr_assert_stdout_eq_str("9223372036854775807\n");
}

Test(my_printf, length_int_hh, .init = redirect_all_std)
{
    my_printf("%hhd\n", 128);
    cr_assert_stdout_eq_str("-128\n");
}

Test(my_printf, length_int_h, .init = redirect_all_std)
{
    my_printf("%hd\n", 32768);
    cr_assert_stdout_eq_str("-32768\n");
}

Test(my_printf, length_int_j, .init = redirect_all_std)
{
    my_printf("%jd\n", 9223372036854775807);
    cr_assert_stdout_eq_str("9223372036854775807\n");
}

Test(my_printf, length_int_z, .init = redirect_all_std)
{
    my_printf("%zd\n", 9223372036854775807);
    cr_assert_stdout_eq_str("9223372036854775807\n");
}

Test(my_printf, length_int_Z, .init = redirect_all_std)
{
    my_printf("%Zd\n", 9223372036854775807);
    cr_assert_stdout_eq_str("9223372036854775807\n");
}

Test(my_printf, length_int_t, .init = redirect_all_std)
{
    my_printf("%td\n", 9223372036854775807);
    cr_assert_stdout_eq_str("9223372036854775807\n");
}

Test(my_printf, length_uint_l, .init = redirect_all_std)
{
    my_printf("%lu\n", 2147483648);
    cr_assert_stdout_eq_str("2147483648\n");
}

Test(my_printf, length_uint_ll, .init = redirect_all_std)
{
    my_printf("%llu\n", 2147483648);
    cr_assert_stdout_eq_str("2147483648\n");
}

Test(my_printf, length_uint_q, .init = redirect_all_std)
{
    my_printf("%qu\n", 2147483648);
    cr_assert_stdout_eq_str("2147483648\n");
}

Test(my_printf, length_uint_hh, .init = redirect_all_std)
{
    my_printf("%hhu\n", 256);
    cr_assert_stdout_eq_str("0\n");
}

Test(my_printf, length_uint_h, .init = redirect_all_std)
{
    my_printf("%hu\n", 65536);
    cr_assert_stdout_eq_str("0\n");
}

Test(my_printf, length_uint_j, .init = redirect_all_std)
{
    my_printf("%ju\n", 2147483648);
    cr_assert_stdout_eq_str("2147483648\n");
}

Test(my_printf, length_uint_t, .init = redirect_all_std)
{
    my_printf("%tu\n", 2147483648);
    cr_assert_stdout_eq_str("2147483648\n");
}

Test(my_printf, length_uint_z, .init = redirect_all_std)
{
    my_printf("%zu\n", 2147483648);
    cr_assert_stdout_eq_str("2147483648\n");
}

Test(my_printf, length_uint_Z, .init = redirect_all_std)
{
    my_printf("%Zu\n", 2147483648);
    cr_assert_stdout_eq_str("2147483648\n");
}

Test(my_printf, length_L, .init = redirect_all_std)
{
    my_printf("%Lf", 3.14L);
    cr_assert_stdout_eq_str("3.140000");
}

Test(my_printf, precision_minus, .init = redirect_all_std)
{
    my_printf("%.5d", -42);
    cr_assert_stdout_eq_str("-00042");
}

Test(my_printf, precision_str, .init = redirect_all_std)
{
    my_printf("%.5s", "hello ceci ne doit pas s'afficher");
    cr_assert_stdout_eq_str("hello");
}

Test(my_printf, n_basic_use_case, .init = redirect_all_std)
{
    int value = 0;

    my_printf("Bonjour je suis %n Olivier", &value);
    cr_assert_eq(value, 16);
}

Test(my_printf, a_basic_use_case, .init = redirect_all_std)
{
    my_printf("%a", 6.5);
    cr_assert_stdout_eq_str("0x1.ap+2");
}

Test(my_printf, a_basic_use_case_negative, .init = redirect_all_std)
{
    my_printf("%a", -6.5);
    cr_assert_stdout_eq_str("-0x1.ap+2");
}

Test(my_printf, a_basic_use_case_less_than_0, .init = redirect_all_std)
{
    my_printf("%a", 0.1);
    cr_assert_stdout_eq_str("0x1.999999999999ap-4");
}

Test(my_printf, a_negative_less_than_zero, .init = redirect_all_std)
{
    my_printf("%a", -0.1);
    cr_assert_stdout_eq_str("-0x1.999999999999ap-4");
}

Test(my_printf, a_basic_use_long_result, .init = redirect_all_std)
{
    my_printf("%a", 3.14);
    cr_assert_stdout_eq_str("0x1.91eb851eb851fp+1");
}

Test(my_printf, a_basic_use_really_small, .init = redirect_all_std)
{
    my_printf("%a", 0.001);
    cr_assert_stdout_eq_str("0x1.0624dd2f1a9fcp-10");
}

Test(my_printf, a_basic_use_zero, .init = redirect_all_std)
{
    my_printf("%a", 0.0);
    cr_assert_stdout_eq_str("0x0p+0");
}

Test(my_printf, a_basic_use_one, .init = redirect_all_std)
{
    my_printf("%a", 1.0);
    cr_assert_stdout_eq_str("0x1p+0");
}

Test(my_printf, no_precision, .init = redirect_all_std)
{
    my_printf("%a", 4.6789);
    cr_assert_stdout_eq_str("0x1.2b7318fc50481p+2");
}

Test(my_printf, precision_zero, .init = redirect_all_std)
{
    my_printf("%.0a", 4.6789);
    cr_assert_stdout_eq_str("0x1p+2");
}

Test(my_printf, precision_one, .init = redirect_all_std)
{
    my_printf("%.1a", 4.6789);
    cr_assert_stdout_eq_str("0x1.3p+2");
}

Test(my_printf, precision_round_up, .init = redirect_all_std)
{
    my_printf("%.5a", 4.6789);
    cr_assert_stdout_eq_str("0x1.2b732p+2");
}

Test(my_printf, precision_round_2_spaces_with_f, .init = redirect_all_std)
{
    my_printf("%.7a", 4.6789);
    cr_assert_stdout_eq_str("0x1.2b73190p+2");
}

Test(my_printf, precision_round_up_to_first_digit, .init = redirect_all_std)
{
    my_printf("%.3a", 1.9999);
    cr_assert_stdout_eq_str("0x2.000p+0");
}

Test(my_printf, precision_zero_round_up, .init = redirect_all_std)
{
    my_printf("%.0a", 1.9999);
    cr_assert_stdout_eq_str("0x2p+0");
}

Test(my_printf, precision_adds_zeros, .init = redirect_all_std)
{
    my_printf("%.3a", 6.5);
    cr_assert_stdout_eq_str("0x1.a00p+2");
}

Test(my_printf, precision_adds_zeros_negative, .init = redirect_all_std)
{
    my_printf("%.12a", -6.5);
    cr_assert_stdout_eq_str("-0x1.a00000000000p+2");
}

Test(my_printf, preci_round_up_to_first_digit_neg, .init = redirect_all_std)
{
    my_printf("%.3a", -1.9999);
    cr_assert_stdout_eq_str("-0x2.000p+0");
}

Test(my_printf, zero_with_zero_precision, .init = redirect_all_std)
{
    my_printf("%.0a", 0.0);
    cr_assert_stdout_eq_str("0x0p+0");
}

Test(my_printf, zero_with_5_precision, .init = redirect_all_std)
{
    my_printf("%.5a", 0.0);
    cr_assert_stdout_eq_str("0x0.00000p+0");
}

Test(my_printf, zero_flag_width_and_neg_int, .init = redirect_all_std)
{
    my_printf("%030d\n", -7);
    cr_assert_stdout_eq_str("-00000000000000000000000000007\n");
}

Test(my_printf, zero_flag_plus_flag_width_and_int, .init = redirect_all_std)
{
    my_printf("%+030d\n", 7);
    cr_assert_stdout_eq_str("+00000000000000000000000000007\n");
}

Test(my_printf, zero_flag_hash_flag_width_and_neg_a, .init = redirect_all_std)
{
    my_printf("%#015a", -6.5);
    cr_assert_stdout_eq_str("-0x0000001.ap+2");
}

Test(my_printf, a_wth_flag_hash_and_0_precision, .init = redirect_all_std)
{
    my_printf("%#.0a", 6.5);
    cr_assert_stdout_eq_str("0x2.p+2");
}
