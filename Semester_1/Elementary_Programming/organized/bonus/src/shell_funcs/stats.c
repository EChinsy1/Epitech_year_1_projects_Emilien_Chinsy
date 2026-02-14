/*
** EPITECH PROJECT, 2025
** stats
** File description:
** a file that shows stats of the current project
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "my.h"
#include "materials.h"
#include "types.h"

int which_type_element(linked_list_t *current, int **num_each_type)
{
    int i = 0;

    while (i < (NUM_OF_TYPES - 1)) {
        if (strcmp(((materials_t *)current->data)->type, types[i]) == 0) {
            (*num_each_type)[i] += 1;
        }
        ++i;
    }
    return (0);
}

int get_num_items(void *data, int **num_each_type)
{
    linked_list_t *current = ((*(main_t **)data)->list);
    int num_items = 0;

    while (current != NULL) {
        num_items++;
        which_type_element(current, num_each_type);
        current = current->next;
    }
    return (num_items);
}

static void print_with_colors(int *num_of_each_type)
{
    printf("the list currently holds %d \x1b[01;32mactuators\x1b[0m\n"
        , num_of_each_type[0]);
    printf("the list currently holds %d \x1b[01;34mdevices\x1b[0m\n"
        , num_of_each_type[1]);
    printf("the list currently holds %d \x1b[01;31mwires\x1b[0m\n"
        , num_of_each_type[2]);
    printf("the list currently holds %d \x1b[01;36msensors\x1b[0m\n"
        , num_of_each_type[3]);
    printf("the list currently holds %d \x1b[01;35mprocessors\x1b[0m\n"
        , num_of_each_type[4]);
}

static int show_stats(void *data, char **args, int color)
{
    int *num_of_each_type = calloc(sizeof(int), NUM_OF_TYPES);

    printf("the next elements id is %d\n", ((*(main_t **)data)->biggest));
    printf("the list currently holds %d items\n",
        get_num_items(data, &num_of_each_type));
    if (color == 0) {
        printf("the list currently holds %d actuators\n", num_of_each_type[0]);
        printf("the list currently holds %d devices\n", num_of_each_type[1]);
        printf("the list currently holds %d wires\n", num_of_each_type[2]);
        printf("the list currently holds %d sensors\n", num_of_each_type[3]);
        printf("the list currently holds %d processors\n", num_of_each_type[4]);
    } else {
        print_with_colors(num_of_each_type);
    }
    free(num_of_each_type);
    return (0);
}

int stats(void *data, char **args)
{
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
    show_stats(data, args, color);
    return (SUCCESS);
}
