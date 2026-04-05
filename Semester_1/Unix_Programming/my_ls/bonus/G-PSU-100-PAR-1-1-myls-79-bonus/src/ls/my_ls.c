/*
** EPITECH PROJECT, 2025
** tes
** File description:
** test
*/

#include "my.h"
#include "struct_file.h"
#include "struct_color.h"

void print_with_colors(char *name, char *path_complete)
{
    struct stat sb;
    int i = 0;

    lstat(path_complete, &sb);
    while (EACH_TYPE[i].check){
        if (EACH_TYPE[i].check(&sb) == 1){
            EACH_TYPE[i].apply(name);
            return;
        }
        ++i;
    }
    my_printf("%s", name);
}

static void item_printer(file_t *items, char_list_t *flags)
{
    file_t *current = items;
    char *path_complete;

    while (current) {
        path_complete = my_calloc(sizeof(char),
            (my_strlen(current->path) + my_strlen(current->name) + 2));
        my_strcpy(path_complete, current->path);
        my_strcat(path_complete, current->name);
        print_with_colors(current->name, path_complete);
        if (flag_x_exists('1', flags) && current->next != NULL)
            my_printf("\n");
        if (current->next != NULL && !flag_x_exists('1', flags))
            my_printf(" ");
        current = current->next;
        free(path_complete);
    }
    my_printf("\n");
}

static int print_the_items(file_t *items,
    char *path,
    char_list_t *flags,
    list_t *paths)
{
    int numpaths = get_num_of_paths(paths);

    if (flag_x_exists('l', flags) == 1){
        print_the_items_l(items, path, numpaths, flags);
        return (0);
    }
    if (numpaths > 1 || flag_x_exists('R', flags) == 1){
        write(1, path, my_strlen(path) - 1);
        my_printf(":\n");
    }
    item_printer(items, flags);
    return (0);
}

static int add_item(file_t **items, char *name, char *path)
{
    file_t *new_item = (file_t *)my_calloc(sizeof(file_t), 1);

    if (!new_item)
        return (0);
    new_item->name = my_calloc(sizeof(char), my_strlen(name) + 1);
    new_item->path = my_calloc(sizeof(char), my_strlen(path) + 1);
    my_strcpy(new_item->path, path);
    my_strcpy(new_item->name, name);
    new_item->next = *items;
    *items = new_item;
    return (0);
}

char *add_slash(char *path)
{
    if (path[my_strlen(path) - 1] != '/')
        my_strcat(path, "/");
    return (path);
}

static int store_the_items(char *path,
    file_t **items,
    DIR **open,
    char_list_t *flags)
{
    struct dirent *dir = NULL;

    path = add_slash(path);
    *open = opendir(path);
    if (*open == NULL)
        return (EXIT_ERROR_);
    dir = readdir(*open);
    while (dir != NULL){
        if (dir->d_name[0] != '.' || flag_x_exists('a', flags) == 1)
            add_item(items, dir->d_name, path);
        dir = readdir(*open);
    }
    return (0);
}

void swap(file_t *a, file_t *b, int *swapped)
{
    char *temp_name = a->name;
    char *temp_path = a->path;
    char *low_name = my_strlowcase(my_strdup(a->name));
    char *low_next_name =my_strlowcase(my_strdup(a->next->name));

    if (my_strcmp(low_name, low_next_name) > 0) {
        a->name = b->name;
        a->path = b->path;
        b->name = temp_name;
        b->path = temp_path;
        *swapped = 1;
    }
    free(low_name);
    free(low_next_name);
}

void sort_the_items(file_t *items)
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
            swap(current, current->next, &swapped);
            current = current->next;
        }
        last = current;
    }
}

static void sort_manager(char_list_t *flags, file_t **items)
{
    if (flag_x_exists('t', flags) && items != NULL) {
        sort_the_items_t(*items);
    } else
        sort_the_items(*items);
}

int my_ls(char_list_t *flags, list_t *paths, int r_running)
{
    file_t *items = NULL;
    DIR *open = NULL;
    list_t *current = paths;

    while (current){
        store_the_items(current->item, &items, &open, flags);
        if (items != NULL)
            sort_manager(flags, &items);
        print_the_items(items, current->item, flags, paths);
        if (current->next != NULL || r_running == 1)
            my_printf("\n");
        if (flag_x_exists('R', flags) && items != NULL)
            go_to_new_paths(paths->item, items, flags, paths);
        free_items(items);
        items = NULL;
        current = current->next;
        closedir(open);
    }
    return (0);
}
