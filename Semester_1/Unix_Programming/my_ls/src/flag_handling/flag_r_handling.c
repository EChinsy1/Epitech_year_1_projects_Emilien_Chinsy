/*
** EPITECH PROJECT, 2025
** flag-r
** File description:
** a file that will hold the functions that handle the R flag
*/

#include "my.h"

static int ignore_curr_and_prev_directory(char *dir)
{
    if (my_strcmp(dir, ".") == 0 || my_strcmp(dir, "..") == 0){
        return (0);
    }
    return (1);
}

int get_num_of_flags(char_list_t *flags)
{
    char_list_t *current = flags;
    int i = 0;

    while (current){
        current = current->next;
        i++;
    }
    return (i);
}

int get_num_of_paths(list_t *paths)
{
    list_t *current = paths;
    int i = 0;

    while (current){
        current = current->next;
        i++;
    }
    return (i);
}

static int check_valid_path_r(char *path)
{
    DIR *open = NULL;
    struct stat sb;

    open = opendir(path);
    if (open == NULL){
        lstat(path, &sb);
        if ((sb.st_mode & S_IFMT) == S_IFREG){
            my_printf("%s\n", path);
            return (84);
        }
        print_errors(path);
        return (84);
    }
    closedir(open);
    return (1);
}

static char *make_fake_flags(char_list_t *flags)
{
    int num_of_flags = get_num_of_flags(flags);
    char *new_flags = my_calloc(sizeof(char *), num_of_flags + 2);
    int i = 0;
    char_list_t *current = flags;

    new_flags[0] = '-';
    for (; i < num_of_flags; i++){
        new_flags[i + 1] = current->item;
        current = current->next;
    }
    new_flags[i + 1] = '\0';
    return (new_flags);
}

static int go_to_next_path(char *path, char_list_t *flags, list_t *paths)
{
    list_t *new_path = my_calloc(sizeof(list_t), 1);

    new_path->item = path;
    new_path->next = NULL;
    if (check_valid_path_r(path) != 1){
        free(new_path);
        my_putchar('\n');
        return (84);
    }
    if (flag_x_exists('d', flags)){
        show_each_name(new_path, flags);
    } else {
        my_ls(flags, new_path, 1);
    }
    free(new_path);
    return (0);
}

int go_to_new_paths(char *path,
    file_t *items,
    char_list_t *flags,
    list_t *paths)
{
    int i = 0;
    struct stat info;
    char *test = "";
    file_t *current = items;
    char *path_complete;

    while (current) {
        path_complete = my_calloc(sizeof(char),
            (my_strlen(current->path) + my_strlen(current->name) + 2));
        my_strcpy(path_complete, current->path);
        my_strcat(path_complete, current->name);
        stat(path_complete, &info);
        if ((info.st_mode & S_IFMT) == S_IFDIR &&
            ignore_curr_and_prev_directory(current->name) == 1){
            go_to_next_path(path_complete, flags, paths);
        }
        current = current->next;
        free(path_complete);
    }
    return (0);
}
