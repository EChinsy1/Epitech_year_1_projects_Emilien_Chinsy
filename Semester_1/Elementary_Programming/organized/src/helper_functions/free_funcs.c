/*
** EPITECH PROJECT, 2025
** bs
** File description:
** bs
*/

#include <stdlib.h>
#include "my.h"
#include "shell.h"
#include "materials.h"
#include "list.h"

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
