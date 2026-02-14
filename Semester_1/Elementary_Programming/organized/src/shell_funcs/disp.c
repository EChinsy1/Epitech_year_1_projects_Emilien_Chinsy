/*
** EPITECH PROJECT, 2025
** disp
** File description:
** disp
*/

#include "macros.h"
#include "my.h"
#include "materials.h"
#include "list.h"

void material_printer(void *material)
{
    my_printf("%s n°%d - \"%s\"\n", ((materials_t *)material)->type,
        ((materials_t *)material)->unique_id, ((materials_t *)material)->name);
}

int disp(void *data, char **args)
{
    linked_list_t *element;
    int num_of_args = get_len_of_args(args);

    if (!((*(main_t **)data)->list))
        return (0);
    if (num_of_args != 0)
        return (ERROR);
    element = (*(main_t **)data)->list;
    while (element) {
        material_printer(element->data);
        element = element->next;
    }
    return (SUCCESS);
}
