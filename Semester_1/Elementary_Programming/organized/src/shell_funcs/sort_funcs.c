/*
** EPITECH PROJECT, 2025
** sort funcs
** File description:
** a file that contain the sort checking funcs
*/

#include <stdio.h>
#include "my.h"
#include "materials.h"

int type_cmp_func(void *one, void *two, char **args, int i)
{
    int cmp_val = 0;

    if (args[i] != NULL && my_strcmp(args[i], "-r") == 0) {
        cmp_val = rev_type_cmp_func(one, two, args, i);
        ++i;
    } else {
        cmp_val = my_strcmp(((materials_t *)one)->type,
            ((materials_t *)two)->type);
    }
    if (cmp_val == 0 && args[i] != NULL)
        return (cmp_func(one, two, args, i));
    if (cmp_val >= 0)
        return (0);
    return (1);
}

int name_cmp_func(void *one, void *two, char **args, int i)
{
    int cmp_val = 0;

    if (args[i] != NULL && my_strcmp(args[i], "-r") == 0) {
        cmp_val = rev_name_cmp_func(one, two, args, i);
        ++i;
    } else {
        cmp_val = my_strcmp(((materials_t *)one)->name,
            ((materials_t *)two)->name);
    }
    if (cmp_val == 0 && args[i] != NULL)
        return (cmp_func(one, two, args, i));
    if (cmp_val >= 0)
        return (0);
    return (1);
}

int id_cmp_func(void *one, void *two, char **args, int i)
{
    int cmp_val = 0;

    if (args[i] != NULL && my_strcmp(args[i], "-r") == 0) {
        cmp_val = rev_id_cmp_func(one, two, args, i);
        ++i;
    } else {
        cmp_val = ((materials_t *)one)->unique_id -
            ((materials_t *)two)->unique_id;
    }
    if (cmp_val == 0 && args[i] != NULL)
        return (cmp_func(one, two, args, i));
    if (cmp_val > 0)
        return (0);
    return (1);
}
