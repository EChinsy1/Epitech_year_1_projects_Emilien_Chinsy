/*
** EPITECH PROJECT, 2026
** tests
** File description:
** tests
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <string.h>
#include "tests.h"
#include "macro.h"

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(decrypt, basic_use_case)
{
    char *result = decrypt("HERE IS A SIMPLE EXAMPLE!", 3);

    cr_assert_str_eq(result, "KHUH LV D VLPSOH HADPSOH!");
}

Test(decrypt, null_string)
{
    char *result = decrypt(NULL, 3);

    cr_assert(result == NULL);
}

Test(decrypt, negative_n)
{
    char *result = decrypt("HERE IS A SIMPLE EXAMPLE!", -3);

    cr_assert_str_eq(result, "EBOB FP X PFJMIB BUXJMIB!");
}

Test(decrypt, edge_cases)
{
    char *result = decrypt("ZzAa[", 3);
    char *result2 = decrypt("ZzAa]", -3);

    if (strcmp(result, "CcDd[") == 0 && strcmp(result2, "WwXx]") == 0)
        cr_assert(1 == 1);
    else {
        printf("%s & %s\n", result, result2);
        cr_assert(1 == 0);
    }
}

Test(open_file, NULL_file_name)
{
    char *buffer = open_file(NULL);

    cr_assert(buffer == NULL);
}

Test(open_file, bad_file_name)
{
    char *buffer = open_file("not a file !!");

    cr_assert(buffer == NULL);
}

Test(open_file, good_file_name)
{
    char *buffer = open_file("Makefile");

    cr_assert(buffer != NULL);
}

Test(cesar, functional_test)
{
    char *argv[5] = {0};
    int return_value = 0;

    argv[0] = "./cesar";
    argv[1] = "-f";
    argv[2] = "./tests/instructions.txt";
    argv[3] = "42";
    argv[4] = NULL;
    return_value = cesar(4, argv);
    cr_assert(return_value == 0);
}

Test(cesar, wrong_num_of_args, .init = redirect_all_std)
{
    char *argv[4] = {0};
    int return_value = 0;

    argv[0] = "./cesar";
    argv[1] = "-f";
    argv[2] = "./tests/instructions.txt";
    argv[3] = NULL;
    return_value = cesar(3, argv);
    cr_assert(return_value == 84);
}

Test(cesar, invalid_flag, .init = redirect_all_std)
{
    char *argv[5] = {0};
    int return_value = 0;

    argv[0] = "./cesar";
    argv[1] = "-e";
    argv[2] = "./tests/instructions.txt";
    argv[3] = "42";
    argv[4] = NULL;
    return_value = cesar(4, argv);
    cr_assert(return_value == 84);
}

Test(cesar, key_not_number, .init = redirect_all_std)
{
    char *argv[5] = {0};
    int return_value = 0;

    argv[0] = "./cesar";
    argv[1] = "-s";
    argv[2] = "thisisatext";
    argv[3] = "not_number";
    argv[4] = NULL;
    return_value = cesar(4, argv);
    cr_assert(return_value == 84);
}

Test(cesar, string, .init = redirect_all_std)
{
    char *argv[5] = {0};
    char *buffer = NULL;

    argv[0] = "./cesar";
    argv[1] = "-s";
    argv[2] = "tisisatext";
    argv[3] = "-8";
    argv[4] = NULL;
    buffer = get_buffer(argv);
    cr_assert_str_eq(buffer, "tisisatext");
}
