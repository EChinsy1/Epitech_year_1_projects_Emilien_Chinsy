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
#include "struct.h"

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

int compare_matrix(float matrix_1[3][3], float **matrix_2)
{
    for (int i = 0; i < 3; ++i)
        if(matrix_1[i][0] != matrix_2[i][0] ||
           matrix_1[i][1] != matrix_2[i][1] ||
           matrix_1[i][2] != matrix_2[i][2]){
            return (0);
        }
    return (1);
}

Test(verify_args, valid_args)
{
    char *argv[13] = {"./102architect", "1", "2", "-t", "2", "3", "-z", "1", "-2", "-r", "45", "-s", "30"};
    int result = verify_args(13, argv);

    cr_assert_eq(result, 1);
}

Test(architect, normal_operation, .init = redirect_all_std)
{
    char *argv[13] = {"./102architect", "1", "2", "-t", "2", "3", "-z", "1", "-2", "-r", "45", "-s", "30"};
    int result = architect(13, argv);
    printf("result = %d\n", result);

    cr_assert_eq(result, 0);
}


Test(verify_args, not_a_num_arg)
{
    char *argv[13] = {"./102architect", "1", "2", "-t", "rien", "3", "-z", "1", "-2", "-r", "45", "-s", "30"};
    int result = verify_args(13, argv);

    cr_assert_eq(result, 84);
}

Test(verify_args, wrong_arg_two)
{
    char *argv[8] = {"./102architect", "1", "2", "-t", "2", "3", "-z", "2"};
    int result = verify_args(8, argv);

    cr_assert_eq(result, 84);
}

Test(architect, wrong_arg_two_architect)
{
    char *argv[7] = {"./102architect", "1", "2", "-t", "2", "3", "-z"};
    int result = architect(7, argv);

    cr_assert_eq(result, 84);
}


Test(verify_args, not_enough_args)
{
    char *argv[2] = {"./102architect", "1"};
    int result = verify_args(2, argv);

    cr_assert_eq(result, 84);
}

Test(verify_args, wrong_first_arg)
{
    char *argv[6] = {"./102architect", "rien", "1", "-t", "2", "3"};
    int result = verify_args(6, argv);

    cr_assert_eq(result, 84);
}

Test(verify_args, wrong_second_arg)
{
    char *argv[6] = {"./102architect", "1", "rien", "-t", "2", "3"};
    int result = verify_args(6, argv);

    cr_assert_eq(result, 84);
}



Test(verify_args, wrong_arg_one)
{
    char *argv[9] = {"./102architect", "1", "2", "-t", "2", "3", "-r", "2", "3"};
    int result = verify_args(9, argv);

    cr_assert_eq(result, 84);
}

Test(verify_args, inexistant_arg)
{
    char *argv[9] = {"./102architect", "1", "2", "-t", "2", "3", "-%", "2", "3"};
    int result = verify_args(9, argv);

    cr_assert_eq(result, 84);
}

Test(architect, help, .init = redirect_all_std)
{
    char *argv[2] = {"./102architect", "-h"};
    int result = architect(2, argv);

    cr_assert_eq(result, 0);
}

Test(do_operation, two_item_operation, .init = redirect_all_std)
{
    char *argv[6] = {"./102architect", "1", "2", "-t", "2", "3"};
    float **matrix = NULL;
    int i = 3;
    float should_be_result[3][3] = {{1.00, 0.00, 2.00}, {0.00, 1.00, 3.00}, {0.00, 0.00, 1.00}};
    float **result = do_operation(matrix, &i, argv);

    cr_assert_eq(1, compare_matrix(should_be_result, result));
}

Test(do_operation, one_item_operation, .init = redirect_all_std)
{
    char *argv[5] = {"./102architect", "1", "2", "-r", "90"};
    float **matrix = NULL;
    int i = 3;
    float should_be_result[3][3] = {{0.00, -1.00, 0.00}, {1.00, 0.00, 0.00}, {0.00, 0.00, 1.00}};
    float **result = do_operation(matrix, &i, argv);

    cr_assert_eq(1, compare_matrix(should_be_result, result));
}
