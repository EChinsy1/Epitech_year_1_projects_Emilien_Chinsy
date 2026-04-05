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
#include "struct.h"

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(my_argv_is_valid, valid_args)
{
    char *argv[7] = {"1.1", "3", "5", "-7", "9", "2", "4"};
    int result = my_argv_is_valid(8, argv);
    cr_assert_eq(result, 1);
}

Test(pong, wrong_number_of_args, .init = redirect_all_std)
{
    char *argv[7] = {"./101pong", "1.1", "3", "5", "-7", "9", "2"};
    int result = pong(7, argv);
    cr_assert_eq(result, 84);
}

Test(my_argv_is_valid, negative_time_shift)
{
    char *argv[7] = {"1.1", "3", "5", "-7", "9", "2", "-4"};
    int result = my_argv_is_valid(8, argv);
    cr_assert_eq(result, 0);
}

Test(my_argv_is_valid, float_time_shift)
{
    char *argv[7] = {"1.1", "3", "5", "-7", "9", "2", "4.1"};
    int result = my_argv_is_valid(8, argv);
    cr_assert_eq(result, 0);
}

Test(my_argv_is_valid, string_as_arg)
{
    char *argv[7] = {"1.1", "wrong", "5", "-7", "9", "2", "4"};
    int result = my_argv_is_valid(8, argv);
    cr_assert_eq(result, 0);
}

Test(make_vector, example_vector)
{
    vector_t vector;
    double x = 1.1;
    double y = 3;
    double z = 5;

    make_vector(x, y, z, &vector);
    if (vector.x == x && vector.y == y && vector.z == z){
        cr_assert_eq(1, 1);
    } else {
        cr_assert_eq(1, 2);
    }
}

Test(make_velocity, example_velocity)
{
    vector_t vector_minus_one;
    vector_t vector_zero;
    vector_t velocity;
    int result_x;
    int result_y;
    int result_z;

    make_vector(1.1, 3, 5, &vector_minus_one);
    make_vector(-7, 9, 2, &vector_zero);
    make_velocity(&vector_minus_one, &vector_zero, &velocity);
    result_x = (velocity.x + (0.005 * velocity.x / fabs(velocity.x))) * 100;
    result_y = (velocity.y + (0.005 * velocity.y / fabs(velocity.y))) * 100;
    result_z = (velocity.z + (0.005 * velocity.x / fabs(velocity.x))) * 100;
    if (result_x == -810 && result_y == 600 && result_z == -300){
        cr_assert_eq(1, 1);
    } else {
        cr_assert_eq(1, 2);
    }
}

Test(calc_angle, example_angle_pos_to_neg)
{
    vector_t vector;
    double result;
    int final;

    make_vector(-8.10, 6.00, -3.00, &vector);
    result = calc_angle(&vector);
    result += 0.005;
    final = result * 100;
    cr_assert_eq(final, 1657);
}

Test(calc_angle, neg_to_pos)
{
    vector_t vector;
    double result;
    int final;

    make_vector(-8.10, 6.00, 1.00, &vector);
    result = calc_angle(&vector);
    result += 0.005;
    final = result * 100;
    cr_assert_eq(final, 567);
}
