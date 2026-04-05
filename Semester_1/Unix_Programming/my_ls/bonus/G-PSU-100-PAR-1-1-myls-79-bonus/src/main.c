/*
** EPITECH PROJECT, 2025
** tes
** File description:
** test
*/

#include "my.h"
#include "struct_file.h"

void free_paths(list_t *paths)
{
    list_t *current = paths;
    list_t *next = NULL;

    while (current) {
        next = current->next;
        free(current);
        current = next;
    }
}

void free_flags(char_list_t *flags)
{
    char_list_t *current = flags;
    char_list_t *next = NULL;

    while (current) {
        next = current->next;
        free(current);
        current = next;
    }
}

void free_items(file_t *head)
{
    file_t *current = head;
    file_t *next = NULL;

    while (current) {
        next = current->next;
        free(current->path);
        free(current->name);
        free(current);
        current = next;
    }
}

void show_each_name(list_t *paths, char_list_t *flags)
{
    list_t *current = paths;
    struct stat sb;
    char *path;

    while (current) {
        if (flag_x_exists('l', flags)){
            path = my_calloc(sizeof(char), (my_strlen(current->item) + 2));
            my_strcpy(path, current->item);
            add_slash(path);
            lstat(path, &sb);
            show_stats(&sb, current->item, path);
            free(path);
            path = NULL;
        } else {
            my_putstr(current->item);
            my_putchar('\n');
        }
        current = current->next;
    }
}

static list_t *reverse_list(list_t *paths)
{
    list_t *current = paths;
    list_t *prev = NULL;
    list_t *next;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    return prev;
}

int main(int const argc, char **argv)
{
    char_list_t *flags = NULL;
    list_t *paths = NULL;
    int return_value = 0;

    if (argc < 2) {
        return (EXIT_ERROR_);
    } else
        return_value = parsing(argc, argv, &flags, &paths);
    if (flag_x_exists('d', flags)){
        show_each_name(paths, flags);
    } else {
        my_ls(flags, paths, 0);
    }
    free_flags(flags);
    free_paths(paths);
    return (return_value);
}
