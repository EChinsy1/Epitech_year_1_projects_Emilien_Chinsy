/*
** EPITECH PROJECT, 2025
** del
** File description:
** del
*/

#include <stdio.h>
#include "my.h"
#include "materials.h"
#include "list.h"

static int compare_all_ids(char **ref, int compared)
{
    int len = get_len_of_args(ref);

    for (int i = 0; i < len; ++i) {
        if (my_getnbr(ref[i]) == compared) {
            return (1);
        }
    }
    return (0);
}

static int compare_id(char *ref, int compared)
{
    return (my_getnbr(ref) == compared);
}

static int delete_last(void *data, linked_list_t *element,
    linked_list_t *prev, char *arg)
{
    while (element->next) {
        while (compare_id(arg,
                ((materials_t *)element->data)->unique_id) == 1
            && element->next) {
            prev->next = element->next;
            free_list_element(element, 1);
            element = prev->next;
        }
        if (element->next) {
            prev = element;
            element = element->next;
        }
    }
    if (element) {
        if (compare_id(arg, ((materials_t *)element->data)->unique_id) == 1) {
            prev->next = NULL;
            free_list_element(element, 1);
        }
    }
    return (SUCCESS);
}

static int my_str_isnum(char *str)
{
    int len = my_strlen(str);

    for (int i = 0; i < len; ++i) {
        if ((str[i] < '0' || str[i] > '9'))
            return (0);
    }
    return (1);
}

static int all_args_exist(void *data, char **args)
{
    linked_list_t *element = (*(main_t **)data)->list;
    int num_of_dels = 0;

    while (element) {
        num_of_dels = num_of_dels + compare_all_ids(args,
            ((materials_t *)element->data)->unique_id);
        element = element->next;
    }
    return (num_of_dels);
}

static int check_args(char **args)
{
    int i = 0;

    while (args[i] != NULL) {
        if (my_str_isnum(args[i]) == 0)
            return (0);
        ++i;
    }
    return (1);
}

static int delete(void *data, char *arg)
{
    linked_list_t *element = (*(main_t **)data)->list;
    linked_list_t *nextt = NULL;

    while (compare_id(arg, ((materials_t *)element->data)->unique_id) == 1
        && element->next != NULL) {
        nextt = element->next;
        free_list_element(element, 1);
        (*(main_t **)data)->list = nextt;
        element = nextt;
    }
    if (compare_id(arg, ((materials_t *)element->data)->unique_id) == 1) {
        free_list_element(element, 1);
        (*(main_t **)data)->list = NULL;
        return (SUCCESS);
    }
    delete_last(data, element, nextt, arg);
    return (SUCCESS);
}

int del(void *data, char **args)
{
    int arg_checker = 0;
    int value = 0;

    if (check_args(args) == 0 || args[0] == NULL)
        return (ERROR);
    arg_checker = all_args_exist(data, args);
    if (arg_checker != get_len_of_args(args))
        return (ERROR);
    if ((*(main_t **)data)->list == NULL)
        return (0);
    for (int i = 0; args[i] != NULL; ++i) {
        value = delete(data, args[i]);
        if (value != SUCCESS)
            return (value);
    }
    return (SUCCESS);
}
