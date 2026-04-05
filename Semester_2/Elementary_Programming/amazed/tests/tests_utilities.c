/*
** EPITECH PROJECT, 2026
** amazed
** File description:
** unit tests for utility functions
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <stdlib.h>
#include "my_string.h"
#include "prints.h"

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(my_calloc, calloc_a_string)
{
    char *test = my_calloc(5, sizeof(char));

    for (int i = 0; i < 5; i++)
        cr_assert(test[i] == 0);
    free(test);
}

Test(put_wordarr, put_word_array, .init = redirect_all_std)
{
    char *test[3] = {"hello", "world", NULL};

    put_wordarr(test);
    cr_assert_stdout_eq(stdout, "helloworld\n");
}

Test(put_wordarr, do_not_crash_if_arr_is_null)
{
    put_wordarr(NULL);
}

Test(my_lenwordarr, len_of_an_array)
{
    char *test[3] = {"hello", "world", NULL};

    cr_assert(my_lenwordarr(test) == 2);
}

Test(my_lenwordarr, null_array_handling)
{
    cr_assert(my_lenwordarr(NULL) == -1);
}

Test(my_str_to_wordarr, separate_three_words)
{
    char **test = my_str_to_wordarr("hello world !", ' ');

    cr_assert_str_eq(test[0], "hello");
    cr_assert_str_eq(test[1], "world");
    cr_assert_str_eq(test[2], "!");
    cr_assert(!test[3]);
    free_wordarr(test);
}

Test(my_str_to_wordarr, return_if_str_is_null)
{
    char **test = my_str_to_wordarr(NULL, ' ');

    cr_assert(!test);
}

Test(my_strcat, cat_two_strings)
{
    char *hello = "hello ";
    char *world = "world !";

    cr_assert_str_eq("hello world !", my_strcat(hello, world));
}

Test(my_strcat, return_if_null)
{
    cr_assert(!my_strcat(NULL, NULL));
}

Test(my_strncat, cat_two_strings)
{
    char *hello = "hello ";
    char *world = "world ! kjahbuixuhahd";

    cr_assert_str_eq("hello world !", my_strncat(hello, world, 7));
}

Test(my_strncat, return_if_null)
{
    cr_assert(!my_strncat(NULL, NULL, 1));
}

Test(my_strcmp, two_equal_strings)
{
    cr_assert(my_strcmp("foo", "foo") == 0);
}

Test(my_strcmp, string_one_greater_than_string_two)
{
    cr_assert(my_strcmp("foo", "bar") == 1);
}

Test(my_strcmp, string_two_greater_than_string_one)
{
    cr_assert(my_strcmp("bar", "foo") == -1);
}

Test(my_strcmp, return_minus_one_if_null)
{
    cr_assert(my_strcmp("foo", NULL) == -2);
}

Test(my_strdup, dup_a_string)
{
    char *test = my_strdup("foo");

    cr_assert_str_eq("foo", test);
    free(test);
}

Test(my_strdup, return_null_if_null)
{
    char *test = my_strdup(NULL);

    cr_assert(!test);
}

Test(my_strlen, len_of_a_string)
{
    int len = my_strlen("hello world !");

    cr_assert(len == 13);
}

Test(my_strlen, return_minus_one_if_null)
{
    int len = my_strlen(NULL);

    cr_assert(len == -1);
}

Test(my_strncmp, two_equal_strings)
{
    cr_assert(my_strncmp("fool", "foo", 3) == 0);
}

Test(my_strncmp, string_one_greater_than_string_two)
{
    cr_assert(my_strncmp("foo", "fol", 3) == 1);
}

Test(my_strncmp, string_two_greater_than_string_one)
{
    cr_assert(my_strncmp("fol", "foo", 3) == -1);
}

Test(my_strncmp, return_if_null_strings)
{
    cr_assert(my_strncmp(NULL, NULL, 1) == -2);
}

Test(my_strncmp, return_if_negative_length)
{
    cr_assert(my_strncmp("foo", "bar", -1) == -2);
}

Test(my_putnbr, put_positive_number, .init = redirect_all_std)
{
    my_putnbr(65);
    cr_assert_stdout_eq(stdout, "65");
}

Test(my_putnbr, put_negative_number, .init = redirect_all_std)
{
    my_putnbr(-65);
    cr_assert_stdout_eq(stdout, "-65");
}

Test(my_putchar, put_character, .init = redirect_all_std)
{
    my_putchar('a');
    cr_assert_stdout_eq(stdout, "a");
}

Test(my_putstr, put_string, .init = redirect_all_std)
{
    my_putstr("foo");
    cr_assert_stdout_eq(stdout, "foo");
}

Test(my_putstr, return_if_null)
{
    my_putstr(NULL);
}
