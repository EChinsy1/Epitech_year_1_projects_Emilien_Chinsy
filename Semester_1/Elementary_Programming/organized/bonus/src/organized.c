/*
** EPITECH PROJECT, 2025
** bs
** File description:
** bs
*/

#include <string.h>
#include <stdlib.h>
#include "my.h"
#include "materials.h"
#include "shell.h"
#include "types_and_colors.h"

void free_list_element(linked_list_t *current, int print)
{
    if (print == 1)
        my_printf("%s n°%d - \"%s\" deleted.\n",
            ((materials_t *)current->data)->type,
            ((materials_t *)current->data)->unique_id,
            ((materials_t *)current->data)->name);
    free(((materials_t *)current->data)->name);
    free(((materials_t *)current->data)->type);
    free(current->data);
    free(current);
}

void free_list(void *data)
{
    linked_list_t *current = (linked_list_t *)data;
    linked_list_t *next = NULL;

    while (current) {
        next = current->next;
        free_list_element(current, 0);
        current = next;
    }
}

void material_printer(void *material, int color)
{
    int i = 0;

    if (color == 0) {
        my_printf("%s n°%d - \"%s\"\n", ((materials_t *)material)->type,
            ((materials_t *)material)->unique_id,
            ((materials_t *)material)->name);
        return;
    }
    while (TYPES_N_COLORS[i].type) {
        if (strcmp(TYPES_N_COLORS[i].type,
                ((materials_t *)material)->type) == 0) {
            TYPES_N_COLORS[i].fptr(material);
        }
        ++i;
    }
    return;
}

int disp(void *data, char **args)
{
    linked_list_t *element;
    int num_of_args = get_len_of_args(args);
    int color = 0;

    if (!((*(main_t **)data)->list) || num_of_args > 1) {
        return (ERROR);
    }
    if (num_of_args == 1) {
        if (strcmp(args[0], "-c") == 0)
            color = 1;
        else
            return (ERROR);
    }
    element = (*(main_t **)data)->list;
    while (element) {
        material_printer(element->data, color);
        element = element->next;
    }
    return (SUCCESS);
}
