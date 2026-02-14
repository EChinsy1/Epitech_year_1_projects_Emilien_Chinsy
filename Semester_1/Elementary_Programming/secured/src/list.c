/*
** EPITECH PROJECT, 2026
** secured
** File description:
** secured
*/

#include <endian.h>
#include <stdlib.h>
#include <unistd.h>
#include "hashtable.h"
#include "my.h"

void free_list(list_t *list)
{
    list_t *current = list;
    list_t *next = NULL;

    if (!current)
        return;
    while (current) {
        next = current->next;
        free(current->value);
        free(current);
        current = next;
    }
}

void print_list(list_t *list)
{
    list_t *current = list;
    int i = 0;

    if (!current)
        return;
    while (current) {
        write(1, "> ", 2);
        my_put_nbr(current->hash);
        write(1, " - ", 3);
        write(1, current->value, my_strlen(current->value));
        my_putchar('\n');
        current = current->next;
        ++i;
    }
}

int list_add(list_t **list, char *value, int hash)
{
    list_t *new_element = malloc(sizeof(list_t) * 1);
    list_t *current = NULL;

    if (!new_element || !list)
        return (-1);
    current = *list;
    while (current) {
        if (current->hash == hash) {
            current->value = my_strdup(value);
            return (0);
        }
        current = current->next;
    }
    new_element->value = my_strdup(value);
    new_element->hash = hash;
    new_element->next = *list;
    *list = new_element;
    return (0);
}

int list_delete(list_t **list, int hash)
{
    list_t **current = list;
    list_t *temp = NULL;
    int deleted = 0;

    if (!current)
        return (84);
    while (*current) {
        if ((*current)->hash == hash) {
            temp = *current;
            *current = temp->next;
            free(temp->value);
            free(temp);
            deleted = 1;
            break;
        } else
            current = &(*current)->next;
    }
    if (deleted == 1)
        return (0);
    return (84);
}
