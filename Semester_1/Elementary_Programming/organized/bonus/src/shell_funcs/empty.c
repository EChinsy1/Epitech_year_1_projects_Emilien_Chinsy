/*
** EPITECH PROJECT, 2025
** del
** File description:
** del
*/

#include "my.h"
#include <stdio.h>

int empty(void *data, char **args)
{
    linked_list_t *element = NULL;
    linked_list_t *next = NULL;

    if (args[0] != NULL)
        return (ERROR);
    if ((*(main_t **)data)->list == NULL)
        return (0);
    element = (*(main_t **)data)->list;
    while (element != NULL && element->next != NULL) {
        next = element->next;
        free_list_element(element, 0);
        element = next;
    }
    if (element != NULL)
        free_list_element(element, 0);
    (*(main_t **)data)->list = NULL;
    return (SUCCESS);
}
