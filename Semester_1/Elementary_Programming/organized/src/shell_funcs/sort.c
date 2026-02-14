/*
** EPITECH PROJECT, 2025
** sort
** File description:
** sort
*/

#include <stdio.h>
#include "my.h"
#include "arg_and_sort_func.h"
#include "materials.h"
#include "list.h"

int cmp_func(void *one, void *two, char **args, int i)
{
    int j = 0;

    if (args[i] == NULL)
        return (IDENTICAL);
    while (SORT_FUNCS[j].arg != NULL) {
        if (my_strcmp(SORT_FUNCS[j].arg, args[i]) == IDENTICAL)
            return (SORT_FUNCS[j].cmp_func(one, two, args, i + 1));
        ++j;
    }
    return (IDENTICAL);
}

linked_list_t *merge_list(linked_list_t *one,
    linked_list_t *two,
    char **args)
{
    linked_list_t *sorted = NULL;

    if (one == NULL)
        return (two);
    else if (two == NULL)
        return (one);
    if (cmp_func(((materials_t *)one->data),
            ((materials_t *)two->data), args, 0) == 1) {
        sorted = one;
        sorted->next = merge_list(one->next, two, args);
    } else {
        sorted = two;
        sorted->next = merge_list(one, two->next, args);
    }
    return (sorted);
}

void split_list(linked_list_t *list,
    linked_list_t **front,
    linked_list_t **back)
{
    linked_list_t *fast;
    linked_list_t *slow;

    slow = list;
    fast = list->next;
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    *front = list;
    *back = slow->next;
    slow->next = NULL;
}

int merge_sort(linked_list_t **data, char **args)
{
    linked_list_t *list = *data;
    linked_list_t *front;
    linked_list_t *back;

    if ((list == NULL) || (list->next == NULL))
        return (0);
    split_list(list, &front, &back);
    merge_sort(&front, args);
    merge_sort(&back, args);
    *data = merge_list(front, back, args);
    return (SUCCESS);
}

static int check_arg(char *arg)
{
    int j = 0;

    while (SORT_FUNCS[j].arg != NULL) {
        if (my_strcmp(SORT_FUNCS[j].arg, arg) == 0 ||
            my_strcmp(arg, "-r") == 0)
            return (1);
        ++j;
    }
    return (0);
}

int sort(void *data, char **args)
{
    int i = 0;

    if (args[i] != NULL)
        if (my_strcmp(args[i], "-r") == 0)
            return (ERROR);
    while (args[i] != NULL) {
        if (check_arg(args[i]) != 1)
            return (ERROR);
        ++i;
    }
    if (i == 0) {
        my_printf("no args\n");
        return (ERROR);
    }
    return (merge_sort(&((*(main_t **)data)->list), args));
}
