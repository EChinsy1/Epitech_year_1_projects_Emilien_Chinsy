/*
** EPITECH PROJECT, 2025
** organized
** File description:
** file containing the sort function
*/

#include <stdio.h>
#include <stdlib.h>
#include "my_top.h"

static void split(procs_t *start, procs_t **first, procs_t **second)
{
    procs_t *fast = start->next;
    procs_t *slow = start;

    while (fast != NULL){
        fast = fast->next;
        if (fast != NULL){
            slow = slow->next;
            fast = fast->next;
        }
    }
    *first = start;
    *second = slow->next;
    slow->next = NULL;
}

static int compare_elems(procs_t *first, procs_t *second)
{
    return (first->virt_mem < second->virt_mem);
}

static procs_t *merge_sort(procs_t *first, procs_t *second)
{
    procs_t *temp = NULL;

    if (first == NULL)
        return second;
    if (second == NULL)
        return first;
    if (compare_elems(first, second) == 0){
        temp = first;
        temp->next = merge_sort(first->next, second);
    } else {
        temp = second;
        temp->next = merge_sort(first, second->next);
    }
    return temp;
}

static void handle_sorting(procs_t **start)
{
    procs_t *first_entry = *start;
    procs_t *first = NULL;
    procs_t *second = NULL;

    if (first_entry != NULL && first_entry->next != NULL){
        split(first_entry, &first, &second);
        handle_sorting(&first);
        handle_sorting(&second);
        *start = merge_sort(first, second);
    }
}

int sort(procs_t **head)
{
    procs_t *entry = *head;

    handle_sorting(&entry);
    *head = entry;
    return 0;
}
