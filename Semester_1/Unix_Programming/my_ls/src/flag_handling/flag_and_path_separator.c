/*
** EPITECH PROJECT, 2025
** flag and path separator
** File description:
** a file that handles parsing
*/

#include "my.h"
#include "struct.h"

static int is_flag(const char to_check, char_list_t *flags, list_t *paths)
{
    int i = 0;

    while (EACH_FLAG[i].flag){
        if (EACH_FLAG[i].flag == to_check){
            return (1);
        }
        i++;
    }
    my_printf("ls: invalid option -- %c\n", to_check);
    free_paths(paths);
    free_flags(flags);
    exit(EXIT_ERROR_);
}

int flag_x_exists(const char to_check, char_list_t *flags)
{
    char_list_t *current = flags;

    while (current){
        if (current->item == to_check)
            return (1);
        current = current->next;
    }
    return (0);
}

static int multiple_instances_of_flag(const char to_check,
    char_list_t *flags)
{
    char_list_t *current = flags;

    while (current) {
        if (current->item == to_check){
            return (0);
        }
        current = current->next;
    }
    return (1);
}

static void add_path(list_t **paths, char *item)
{
    list_t *new_path = my_calloc(sizeof(list_t), 1);

    if (!new_path)
        return;
    new_path->item = item;
    my_strcat(item, "\0");
    new_path->next = *paths;
    *paths = new_path;
}

static void add_flag(char_list_t **flags, char item)
{
    char_list_t *new_flag = my_calloc(sizeof(char_list_t), 1);

    if (!new_flag)
        return;
    new_flag->item = item;
    new_flag->next = *flags;
    *flags = new_flag;
}

void print_errors(char *path)
{
    char *buff;
    char *error_message = "my_ls: cannot open directory '";

    write(2, error_message, my_strlen(error_message));
    write(2, path, my_strlen(path));
    write(2, "': ", 3);
    buff = strerror(errno);
    write(2, buff, my_strlen(buff));
    write(2, "\n", 1);
}

static int check_valid_path(list_t **paths, char *path)
{
    DIR *open = NULL;
    struct stat sb;

    open = opendir(path);
    if (open == NULL){
        lstat(path, &sb);
        if ((sb.st_mode & S_IFMT) == S_IFREG){
            my_printf("%s\n", path);
            return (0);
        }
        print_errors(path);
        return (EXIT_ERROR_);
    }
    closedir(open);
    add_path(paths, path);
    return (0);
}

static void add_flags_ls(char_list_t **flags, list_t **paths, const char *flag)
{
    char flag_to_add;

    for (int i = 1; i < my_strlen(flag); ++i) {
        if (is_flag(flag[i], *flags, *paths) == 1 &&
            multiple_instances_of_flag(flag[i], *flags) == 1) {
            flag_to_add = flag[i];
            add_flag(flags, flag_to_add);
        }
    }
}

int parsing(int argc, char **argv, char_list_t **flags, list_t **paths)
{
    int return_value = 0;

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            add_flags_ls(flags, paths, argv[i]);
        } else {
            return_value = check_valid_path(paths, argv[i]);
        }
    }
    return (return_value);
}
