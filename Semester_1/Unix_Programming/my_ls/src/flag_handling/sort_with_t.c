/*
** EPITECH PROJECT, 2025
** sort with t
** File description:
** a file that contains what will be used to sort when flag t exists
*/

#include "my.h"

static int swap_t(file_t **a, file_t **b, long long time_a, long long time_b)
{
    char *temp_name = (*a)->name;
    char *temp_path = (*a)->path;

    if (time_a < time_b) {
        (*a)->name = (*b)->name;
        (*a)->path = (*b)->path;
        (*b)->name = temp_name;
        (*b)->path = temp_path;
        return (1);
    }
    return (0);
}

static char *create_file_path(file_t *file)
{
    char *file_path = my_calloc(sizeof(char),
        my_strlen(file->path) + my_strlen(file->name) + 2);

    my_strcpy(file_path, file->path);
    my_strcat(file_path, file->name);
    return (file_path);
}

static void compare_t(file_t *a, file_t *b, int *swapped)
{
    struct stat sb_a;
    struct stat sb_b;
    char *file_path_a = create_file_path(a);
    char *file_path_b = create_file_path(b);
    long long time_a = 0;
    long long time_b = 0;

    lstat(file_path_a, &sb_a);
    lstat(file_path_b, &sb_b);
    time_a = sb_a.st_mtime;
    time_b = sb_b.st_mtime;
    *swapped += swap_t(&a, &b, time_a, time_b);
    free(file_path_a);
    free(file_path_b);
}

void sort_the_items_t(file_t *items)
{
    int swapped = 1;
    int i;
    file_t *current;
    file_t *last = NULL;

    if (items == NULL)
        return;
    while (swapped) {
        swapped = 0;
        current = items;
        while (current->next != last) {
            compare_t(current, current->next, &swapped);
            current = current->next;
        }
        last = current;
    }
}
