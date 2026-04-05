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

Test(verify_args, valid_args_0, .init = redirect_all_std)
{
    char *argv[4] = {"./103cipher", "bonjour", "hello", "0"};
    int result = cipher(4, argv);

    cr_assert_eq(result, 0);
}

Test(verify_args, too_many_args, .init = redirect_all_std)
{
    char *argv[5] = {"./103cipher", "bonjour", "hello", "0", "extra"};
    int result = cipher(5, argv);

    cr_assert_eq(result, 84);
}

Test(verify_args, wrong_last_arg, .init = redirect_all_std)
{
    char *argv[4] = {"./103cipher", "bonjour", "hello", "2"};
    int result = cipher(4, argv);

    cr_assert_eq(result, 84);
}

Test(inv, 2x2)
{
    float **inv_func;
    float **matrix = malloc(sizeof(float *) * 3);

    matrix[0] = malloc(sizeof(float) * 2);
    matrix[1] = malloc(sizeof(float) * 2);
    matrix[0][0] = 106;
    matrix[0][1] = 101;
    matrix[1][0] = 97;
    matrix[1][1] = 110;
    inv_func = twoxtwo_inverse(matrix);

    if (inv_func[0][0] > 0 &&
        inv_func[0][1] < 0 &&
        inv_func[1][0] < 0 &&
        inv_func[1][1] > 0)
        cr_assert_eq(1, 1);
    else
        cr_assert_eq(1, 0);
    free(matrix[0]);
    free(matrix[1]);
    free(matrix);
}

Test(inv, 3x3)
{
    float **inv_func;
    float **matrix = malloc(sizeof(float *) * 4);

    matrix[0] = malloc(sizeof(float) * 3);
    matrix[1] = malloc(sizeof(float) * 3);
    matrix[2] = malloc(sizeof(float) * 3);
    matrix[0][0] = 72;
    matrix[0][1] = 111;
    matrix[0][2] = 109;
    matrix[1][0] = 101;
    matrix[1][1] = 114;
    matrix[1][2] = 32;
    matrix[2][0] = 83;
    matrix[2][1] = 97;
    matrix[2][2] = 97;
    inv_func = threexthree_inverse(matrix);
    if (inv_func[0][0] < 0 &&
	inv_func[0][1] > 0 &&
        inv_func[0][2] > 0 &&
        inv_func[1][0] > 0 &&
        inv_func[1][1] > 0 &&
        inv_func[1][2] < 0 &&
        inv_func[2][0] < 0 &&
        inv_func[2][1] < 0 &&
        inv_func[2][2] > 0)
        cr_assert_eq(1, 1);
    else
        cr_assert_eq(1, 0);
    free(matrix[0]);
    free(matrix[1]);
    free(matrix[2]);
    free(matrix);
}

Test(num_occurences, num_space_occurence)
{
    char *string = "Je vais manger";
    int occ = num_occurences(string, ' ');

    cr_assert_eq(2, occ);
}
