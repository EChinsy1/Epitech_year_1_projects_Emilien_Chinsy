/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** cd
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include "my.h"
#include "arguments.h"

static int check_path(char *path)
{
    struct stat sb;
    int is_dir = 0;

    if (lstat(path, &sb) == -1)
        return (-1);
    is_dir = S_ISREG(sb.st_mode);
    if (is_dir != 0) {
        my_putstr(2, path);
        my_putstr(2, ": Not a directory.\n");
    }
    return (is_dir);
}

int move_dirs(args_t *args, char *path, char **command_array)
{
    char *buf = NULL;
    int result = 0;
    size_t size = 0;
    char *old_dir = getcwd(buf, size);
    char *curr_dir = NULL;
    int check = check_path(path);

    if (check != 0)
        return (check);
    result = chdir(path);
    curr_dir = getcwd(buf, size);
    if (result == 0) {
        args->env = modify_env(args, "PWD", curr_dir);
        args->env = modify_env(args, "OLDPWD", old_dir);
        free(args->old_dir);
        args->old_dir = my_strdup(old_dir);
    }
    free(curr_dir);
    free(old_dir);
    return (result);
}

static int cd_no_args(args_t *args, char **command_array)
{
    if (my_strcmp(args->home_dir, "none") == 0) {
        my_putstr(2, "cd: No home directory.\n");
    } else
        move_dirs(args, args->home_dir, command_array);
    return (0);
}

static int is_only_points(args_t *args, char *str, char **command_array)
{
    int i = 0;

    while (str[i] != '\0') {
        if (str[i] == '.') {
            ++i;
        } else
            return (1);
    }
    for (; i > 1; --i)
        move_dirs(args, "..", command_array);
    return (0);
}

static int cd_minus(args_t *args, char **command_array)
{
    if (my_strncmp(command_array[1], "-",
            my_strlen(command_array[1])) != 0)
        return (1);
    if (my_strcmp(args->old_dir, "none") == 0)
        my_putstr(2, ": No such file or directory.\n");
    move_dirs(args, args->old_dir, command_array);
    return (0);
}

static int cd_with_args(args_t *args, char **command_array)
{
    if (is_only_points(args, command_array[1], command_array) == 0)
        return (0);
    if (cd_minus(args, command_array) == 0)
        return (0);
    if (access(command_array[1], F_OK) == 0) {
        return (move_dirs(args, command_array[1], command_array));
    } else {
        write(2, "cd: File does not exist\n", 24);
        return (1);
    }
}

int cd_func(args_t *args, char **command_array)
{
    size_t size = 100;

    if (command_array[1] == NULL)
        return (cd_no_args(args, command_array));
    if (command_array[2] != NULL) {
        write(2, "cd: usage[target_dir]\n", 22);
        return (1);
    }
    return (cd_with_args(args, command_array));
}
