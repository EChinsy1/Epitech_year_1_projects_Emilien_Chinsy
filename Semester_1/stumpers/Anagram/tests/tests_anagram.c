/*
** EPITECH PROJECT, 2026
** tests
** File description:
** tests
*/

#include <criterion/criterion.h>
#include "../my.h"

Test (anagram, actually_an_anagram)
{
    char *str_1 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char *str_2 = "zyxwvutsrqponmlkjihgfedcba";
    
    cr_assert_eq(anagram(str_1, str_2, 26), 1);
}

Test (anagram, not_an_anagram)
{
    char *str_1 = "aJean Neymar";
    char *str_2 = "bNeyje anmar";

    cr_assert_eq(anagram(str_1, str_2, 12), 0);
}


Test (anagram_main, return_0_when_normal)
{
    char *argv[3] = {"./anagram", "Jean Neymar", "Neyje anmar"};
    int argc = 3;

    cr_assert_eq(anagram_main(argc, argv), 0);
}

Test (anagram_main, return_84_when_not_normal)
{
    char *argv[2] = {"./anagram", "Jean Neymar"};
    int	argc = 2;

    cr_assert_eq(anagram_main(argc, argv), 84);
}

Test (my_strlen, returns_right_length)
{
    char *test_string = "FREDDY FAZBEAR WHAT HAPPENED?";

    cr_assert_eq(my_strlen(test_string), strlen(test_string));
}
