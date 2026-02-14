/*
** EPITECH PROJECT, 2025
** add
** File description:
** a file for the add function
*/

#include <stdio.h>
#include "my.h"
#include "materials.h"
#include "types.h"

int valid_type(char *type)
{
    int i = 0;

    while (types[i] != NULL) {
        if (my_strcmp(type, types[i]) == 0)
            return (1);
        ++i;
    }
    return (0);
}

int add_item(void *data, char **args)
{
    linked_list_t *new_list = my_calloc(sizeof(linked_list_t), 1);
    materials_t *new = my_calloc(sizeof(materials_t), 1);

    if (new_list == NULL || new == NULL)
        return (ERROR);
    new->type = my_strdup(args[0]);
    new->name = my_strdup(args[1]);
    new->unique_id = (*(main_t **)data)->biggest;
    (*(main_t **)data)->biggest = (*(main_t **)data)->biggest + 1;
    new_list->data = new;
    new_list->next = (*(main_t **)data)->list;
    (*(main_t **)data)->list = new_list;
    my_printf("%s n°%d - \"%s\" added.\n", ((materials_t *)new)->type,
        ((materials_t *)new)->unique_id, ((materials_t *)new)->name);
    return (SUCCESS);
}

int add(void *data, char **args)
{
    int len = 0;

    if (args[0] == NULL)
        return (ERROR);
    len = get_len_of_args(args);
    if (len % 2 != 0 || len == 0)
        return (ERROR);
    for (int i = 0; i < len; i = i + 2) {
        if (valid_type(args[i]) == 1)
            add_item(data, &args[i]);
        else {
            my_printf("%s is not a valid type\n", args[i]);
            return (ERROR);
        }
    }
    return (SUCCESS);
}
