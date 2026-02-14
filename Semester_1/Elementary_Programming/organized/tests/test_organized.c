/*
** EPITECH PROJECT, 2025
** tests
** File description:
** tests
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "shell.h"
#include "my.h"

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(valid_type, valid)
{
    int result = valid_type("DEVICE");

    cr_assert_eq(result, 1);
}

Test(valid_type, invalid)
{
    int result = valid_type("Fake");

    cr_assert_eq(result, 0);
}

Test(addd, each_type, .init = redirect_all_std)
{
    main_t *main = my_calloc(sizeof(main_t), 1);
    char **args_add = malloc(sizeof(char *) * 11);
    int result = 0;

    args_add[0] = "WIRE";
    args_add[1] = "one";
    args_add[2] = "ACTUATOR";
    args_add[3] = "two";
    args_add[4] = "DEVICE";
    args_add[5] = "three";
    args_add[6] = "SENSOR";
    args_add[7] = "four";
    args_add[8] = "PROCESSOR";
    args_add[9] = "five";
    args_add[10] = NULL;
    result = add(&main, args_add);
    cr_assert_stdout_eq_str("WIRE n°0 - \"one\" added.\nACTUATOR n°1 - \"two\" added.\nDEVICE n°2 - \"three\" added.\nSENSOR n°3 - \"four\" added.\nPROCESSOR n°4 - \"five\" added.\n");
    free_list(main->list);
    free(main);
    free(args_add);
}

Test(addd, no_args, .init = redirect_all_std)
{
    main_t *main = my_calloc(sizeof(main_t), 1);
    char **no_args = malloc(sizeof(char *) * 1);
    int result = 0;

    no_args[0] = NULL;
    result = add(&main, no_args);
    free(no_args);
    free(main);
    cr_assert_eq(result, 84);
}

Test(addd, wrong_type, .init = redirect_all_std)
{
    main_t *main = my_calloc(sizeof(main_t), 1);
    char **args_add = malloc(sizeof(char *) * 3);
    int result = 0;

    args_add[0] = "FAKE";
    args_add[1] = "one";
    args_add[2] = NULL;
    result = add(&main, args_add);
    cr_assert_eq(result, 84);
    free_list(main->list);
    free(main);
    free(args_add);
}

Test(addd, wrong_num_of_args, .init = redirect_all_std)
{
    main_t *main = my_calloc(sizeof(main_t), 1);
    char **args_add = malloc(sizeof(char *) * 2);
    int result = 0;

    args_add[0] = "FAKE";
    args_add[1] = NULL;
    result = add(&main, args_add);
    cr_assert_eq(result, 84);
    free_list(main->list);
    free(main);
    free(args_add);
}

Test(del, basic_use_case, .init = redirect_all_std)
{
    main_t *main = my_calloc(sizeof(main_t), 1);
    char **args_add = malloc(sizeof(char *) * 5);
    char **args_del = malloc(sizeof(char *) * 2);
    int result = 0;

    args_del[0] = "0";
    args_del[1] = NULL;
    args_add[0] = "WIRE";
    args_add[1] = "one";
    args_add[2] = "WIRE";
    args_add[3] = "two";
    args_add[4] = NULL;
    add(&main, args_add);
    del(&main, args_del);
    cr_assert_stdout_eq_str("WIRE n°0 - \"one\" added.\nWIRE n°1 - \"two\" added.\nWIRE n°0 - \"one\" deleted.\n");
    free_list(main->list);
    free(main);
    free(args_add);
    free(args_del);
}

Test(del, del_one, .init = redirect_all_std)
{
    main_t *main = my_calloc(sizeof(main_t), 1);
    char **args_add = malloc(sizeof(char *) * 3);
    char **args_del = malloc(sizeof(char *) * 2);
    int result = 0;

    args_del[0] = "0";
    args_del[1] = NULL;
    args_add[0] = "WIRE";
    args_add[1] = "one";
    args_add[2] = NULL;
    add(&main, args_add);
    del(&main, args_del);
    cr_assert_stdout_eq_str("WIRE n°0 - \"one\" added.\nWIRE n°0 - \"one\" deleted.\n");
    free(main);
    free(args_add);
    free(args_del);
}

Test(del, del_middle, .init = redirect_all_std)
{
    main_t *main = my_calloc(sizeof(main_t), 1);
    char **args_add = malloc(sizeof(char *) * 7);
    char **args_del = malloc(sizeof(char *) * 2);
    int result = 0;

    args_del[0] = "1";
    args_del[1] = NULL;
    args_add[0] = "WIRE";
    args_add[1] = "one";
    args_add[2] = "WIRE";
    args_add[3] = "two";
    args_add[4] = "WIRE";
    args_add[5] = "three";
    args_add[6] = NULL;
    add(&main, args_add);
    del(&main, args_del);
    cr_assert_stdout_eq_str("WIRE n°0 - \"one\" added.\nWIRE n°1 - \"two\" added.\nWIRE n°2 - \"three\" added.\nWIRE n°1 - \"two\" deleted.\n");
    free_list(main->list);
    free(main);
    free(args_add);
    free(args_del);
}

Test(del, del_last, .init = redirect_all_std)
{
    main_t *main = my_calloc(sizeof(main_t), 1);
    char **args_add = malloc(sizeof(char *) * 7);
    char **args_del = malloc(sizeof(char *) * 2);
    int result = 0;

    args_del[0] = "2";
    args_del[1] = NULL;
    args_add[0] = "WIRE";
    args_add[1] = "one";
    args_add[2] = "WIRE";
    args_add[3] = "two";
    args_add[4] = "WIRE";
    args_add[5] = "three";
    args_add[6] = NULL;
    add(&main, args_add);
    del(&main, args_del);
    cr_assert_stdout_eq_str("WIRE n°0 - \"one\" added.\nWIRE n°1 - \"two\" added.\nWIRE n°2 - \"three\" added.\nWIRE n°2 - \"three\" deleted.\n");
    free_list(main->list);
    free(main);
    free(args_add);
    free(args_del);
}

Test(del, del_several, .init = redirect_all_std)
{
    main_t *main = my_calloc(sizeof(main_t), 1);
    char **args_add = malloc(sizeof(char *) * 7);
    char **args_del = malloc(sizeof(char *) * 3);
    int result = 0;

    args_del[0] = "2";
    args_del[1] = "1";
    args_del[2] = NULL;
    args_add[0] = "WIRE";
    args_add[1] = "one";
    args_add[2] = "WIRE";
    args_add[3] = "two";
    args_add[4] = "WIRE";
    args_add[5] = "three";
    args_add[6] = NULL;
    add(&main, args_add);
    del(&main, args_del);
    cr_assert_stdout_eq_str("WIRE n°0 - \"one\" added.\nWIRE n°1 - \"two\" added.\nWIRE n°2 - \"three\" added.\nWIRE n°2 - \"three\" deleted.\nWIRE n°1 - \"two\" deleted.\n");
    free_list(main->list);
    free(main);
    free(args_add);
    free(args_del);
}

Test(del, wrong_args, .init = redirect_all_std)
{
    main_t *main = my_calloc(sizeof(main_t), 1);
    char **args_add = malloc(sizeof(char *) * 3);
    char **args_del = malloc(sizeof(char *) * 2);
    int result = 0;

    args_del[0] = "fake";
    args_del[1] = NULL;
    args_add[0] = "WIRE";
    args_add[1] = "one";
    args_add[2] = NULL;
    add(&main, args_add);
    result = del(&main, args_del);
    cr_assert_eq(result, 84);
    free(main);
    free(args_add);
    free(args_del);
}

Test(del, inexistent_args, .init = redirect_all_std)
{
    main_t *main = my_calloc(sizeof(main_t), 1);
    char **args_add = malloc(sizeof(char *) * 5);
    char **args_del = malloc(sizeof(char *) * 3);
    int result = 0;

    args_del[0] = "0,";
    args_del[1] = "4";
    args_del[2] = NULL;
    args_add[0] = "WIRE";
    args_add[1] = "one";
    args_add[2] = "WIRE";
    args_add[3] = "two";
    args_add[4] = NULL;
    add(&main, args_add);
    result = del(&main, args_del);
    cr_assert_eq(result, 84);
    free(main);
    free(args_add);
    free(args_del);
}

Test(disp, basic_use_case, .init = redirect_all_std)
{
    main_t *main = my_calloc(sizeof(main_t), 1);
    char **args_add = malloc(sizeof(char *) * 5);
    char **args_disp = malloc(sizeof(char *) * 1);
    int result = 0;

    args_disp[0] = NULL;
    args_add[0] = "WIRE";
    args_add[1] = "one";
    args_add[2] = "ACTUATOR";
    args_add[3] = "two";
    args_add[4] = NULL;
    result = add(&main, args_add);
    disp(&main, args_disp);
    cr_assert_stdout_eq_str("WIRE n°0 - \"one\" added.\nACTUATOR n°1 - \"two\" added.\nACTUATOR n°1 - \"two\"\nWIRE n°0 - \"one\"\n");
    free_list(main->list);
    free(main);
    free(args_add);
}

Test(disp, wrong_args, .init = redirect_all_std)
{
    main_t *main = my_calloc(sizeof(main_t), 1);
    char **args_add = malloc(sizeof(char *) * 5);
    char **args_disp = malloc(sizeof(char *) * 1);
    int result = 0;

    args_disp[0] = "why?";
    args_disp[1] = NULL;
    args_add[0] = "WIRE";
    args_add[1] = "one";
    args_add[2] = "ACTUATOR";
    args_add[3] = "two";
    args_add[4] = NULL;
    add(&main, args_add);
    result = disp(&main, args_disp);
    cr_assert_eq(result, 84);
    free_list(main->list);
    free(main);
    free(args_add);
}

Test(sort, basic_use_case, .init = redirect_all_std)
{
    main_t *main = my_calloc(sizeof(main_t), 1);
    char **args_add = malloc(sizeof(char *) * 5);
    char **args_disp = malloc(sizeof(char *) * 1);
    char **args_sort = malloc(sizeof(char *) * 2);
    int result = 0;

    args_sort[0] = "TYPE";
    args_sort[1] = NULL;
    args_disp[0] = NULL;
    args_add[0] = "WIRE";
    args_add[1] = "one";
    args_add[2] = "ACTUATOR";
    args_add[3] = "two";
    args_add[4] = NULL;
    add(&main, args_add);
    sort(&main, args_sort);
    disp(&main, args_disp);
    cr_assert_stdout_eq_str("WIRE n°0 - \"one\" added.\nACTUATOR n°1 - \"two\" added.\nACTUATOR n°1 - \"two\"\nWIRE n°0 - \"one\"\n");
    free_list(main->list);
    free(main);
    free(args_add);
}

Test(sort, rev_sort, .init = redirect_all_std)
{
    main_t *main = my_calloc(sizeof(main_t), 1);
    char **args_add = malloc(sizeof(char *) * 5);
    char **args_disp = malloc(sizeof(char *) * 1);
    char **args_sort = malloc(sizeof(char *) * 3);
    int result = 0;

    args_sort[0] = "NAME";
    args_sort[1] = "-r";
    args_sort[2] = NULL;
    args_disp[0] = NULL;
    args_add[0] = "WIRE";
    args_add[1] = "one";
    args_add[2] = "ACTUATOR";
    args_add[3] = "two";
    args_add[4] = NULL;
    add(&main, args_add);
    sort(&main, args_sort);
    disp(&main, args_disp);
    cr_assert_stdout_eq_str("WIRE n°0 - \"one\" added.\nACTUATOR n°1 - \"two\" added.\nACTUATOR n°1 - \"two\"\nWIRE n°0 - \"one\"\n");
    free_list(main->list);
    free(main);
    free(args_add);
}

Test(sort, rev_sort_type, .init = redirect_all_std)
{
    main_t *main = my_calloc(sizeof(main_t), 1);
    char **args_add = malloc(sizeof(char *) * 10);
    char **args_disp = malloc(sizeof(char *) * 1);
    char **args_sort = malloc(sizeof(char *) * 3);
    int result = 0;

    args_sort[0] = "TYPE";
    args_sort[1] = "-r";
    args_sort[2] = NULL;
    args_disp[0] = NULL;
    args_add[0] = "WIRE";
    args_add[1] = "one";
    args_add[2] = "ACTUATOR";
    args_add[3] = "two";
    args_add[4] = "WIRE";
    args_add[5] = "three";
    args_add[6] = "ACTUATOR";
    args_add[7] = "four";
    args_add[8] = NULL;
    add(&main, args_add);
    sort(&main, args_sort);
    disp(&main, args_disp);
    cr_assert_stdout_eq_str("WIRE n°0 - \"one\" added.\nACTUATOR n°1 - \"two\" added.\nWIRE n°2 - \"three\" added.\nACTUATOR n°3 - \"four\" added.\nWIRE n°0 - \"one\"\nWIRE n°2 - \"three\"\nACTUATOR n°1 - \"two\"\nACTUATOR n°3 - \"four\"\n");
    free_list(main->list);
    free(main);
    free(args_add);
    free(args_disp);
    free(args_sort);
}

Test(sort, lotofsort, .init = redirect_all_std)
{
    main_t *main = my_calloc(sizeof(main_t), 1);
    char **args_add = malloc(sizeof(char *) * 9);
    char **args_disp = malloc(sizeof(char *) * 1);
    char **args_sort = malloc(sizeof(char *) * 3);
    char **args_sort_2 = malloc(sizeof(char *) * 2);
    char **args_sort_3 = malloc(sizeof(char *) * 2);
    int result = 0;

    args_sort[0] = "ID";
    args_sort[1] = "-r";
    args_sort_2[0] = "ID";
    args_sort_2[1] = NULL;
    args_sort_3[0] = "NAME";
    args_sort_3[1] = NULL;
    args_sort[2] = NULL;
    args_disp[0] = NULL;
    args_add[0] = "WIRE";
    args_add[1] = "one";
    args_add[2] = "ACTUATOR";
    args_add[3] = "two";
    args_add[4] = "WIRE";
    args_add[5] = "two";
    args_add[6] = "ACTUATOR";
    args_add[7] = "four";
    args_add[8] = NULL;
    add(&main, args_add);
    sort(&main, args_sort_2);
    sort(&main, args_sort_3);
    sort(&main, args_sort);
    disp(&main, args_disp);
    cr_assert_stdout_eq_str("WIRE n°0 - \"one\" added.\nACTUATOR n°1 - \"two\" added.\nWIRE n°2 - \"two\" added.\nACTUATOR n°3 - \"four\" added.\nACTUATOR n°3 - \"four\"\nWIRE n°2 - \"two\"\nACTUATOR n°1 - \"two\"\nWIRE n°0 - \"one\"\n");
    free_list(main->list);
    free(main);
    free(args_add);
}

Test(sort, example_in_pdf, .init = redirect_all_std)
{
    main_t *main = my_calloc(sizeof(main_t), 1);
    char **args_add = malloc(sizeof(char *) * 9);
    char **args_disp = malloc(sizeof(char *) * 1);
    char **args_sort = malloc(sizeof(char *) * 6);
    int result = 0;

    args_sort[0] = "TYPE";
    args_sort[1] = "-r";
    args_sort[2] = "NAME";
    args_sort[3] = "ID";
    args_sort[4] = "-r";
    args_sort[5] = NULL;
    args_disp[0] = NULL;
    args_add[0] = "WIRE";
    args_add[1] = "usb";
    args_add[2] = "WIRE";
    args_add[3] = "type-c";
    args_add[4] = "WIRE";
    args_add[5] = "usb";
    args_add[6] = "ACTUATOR";
    args_add[7] = "button";
    args_add[8] = NULL;
    add(&main, args_add);
    sort(&main, args_sort);
    disp(&main, args_disp);
    cr_assert_stdout_eq_str("WIRE n°0 - \"usb\" added.\nWIRE n°1 - \"type-c\" added.\nWIRE n°2 - \"usb\" added.\nACTUATOR n°3 - \"button\" added.\nWIRE n°1 - \"type-c\"\nWIRE n°2 - \"usb\"\nWIRE n°0 - \"usb\"\nACTUATOR n°3 - \"button\"\n");
    free_list(main->list);
    free(main);
    free(args_add);
}

Test(sort, wrong_args_r, .init = redirect_all_std)
{
    main_t *main = my_calloc(sizeof(main_t), 1);
    char **args_add = malloc(sizeof(char *) * 5);
    char **args_disp = malloc(sizeof(char *) * 1);
    char **args_sort = malloc(sizeof(char *) * 2);
    int result = 0;

    args_sort[0] = "-r";
    args_sort[1] = NULL;
    args_disp[0] = NULL;
    args_add[0] = "WIRE";
    args_add[1] = "one";
    args_add[2] = "ACTUATOR";
    args_add[3] = "two";
    args_add[4] = NULL;
    add(&main, args_add);
    result = sort(&main, args_sort);
    cr_assert_eq(result, 84);
    free_list(main->list);
    free(main);
    free(args_add);
}

Test(sort, wrong_args, .init = redirect_all_std)
{
    main_t *main = my_calloc(sizeof(main_t), 1);
    char **args_add = malloc(sizeof(char *) * 5);
    char **args_disp = malloc(sizeof(char *) * 1);
    char **args_sort = malloc(sizeof(char *) * 2);
    int result = 0;

    args_sort[0] = "fake";
    args_sort[1] = NULL;
    args_disp[0] = NULL;
    args_add[0] = "WIRE";
    args_add[1] = "one";
    args_add[2] = "ACTUATOR";
    args_add[3] = "two";
    args_add[4] = NULL;
    add(&main, args_add);
    sort(&main, args_sort);
    disp(&main, args_disp);
    cr_assert_stdout_eq_str("WIRE n°0 - \"one\" added.\nACTUATOR n°1 - \"two\" added.\nACTUATOR n°1 - \"two\"\nWIRE n°0 - \"one\"\n");
    free_list(main->list);
    free(main);
    free(args_add);
}

Test(sort, no_args, .init = redirect_all_std)
{
    main_t *main = my_calloc(sizeof(main_t), 1);
    char **args_add = malloc(sizeof(char *) * 5);
    char **args_disp = malloc(sizeof(char *) * 1);
    char **args_sort = malloc(sizeof(char *) * 1);
    int result = 0;

    args_sort[0] = NULL;
    args_disp[0] = NULL;
    args_add[0] = "WIRE";
    args_add[1] = "one";
    args_add[2] = "ACTUATOR";
    args_add[3] = "two";
    args_add[4] = NULL;
    add(&main, args_add);
    result = sort(&main, args_sort);
    cr_assert_eq(result, 84);
    free_list(main->list);
    free(main);
    free(args_add);
}
