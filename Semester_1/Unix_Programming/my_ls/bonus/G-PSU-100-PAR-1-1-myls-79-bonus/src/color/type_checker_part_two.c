/*
** EPITECH PROJECT, 2025
** type_checker
** File description:
** functions that will be used for color printing
*/

#include "my.h"

int is_sticky_and_ow(struct stat *sb)
{
    int mode = (sb->st_mode);

    if (mode & S_IWOTH)
        if (mode & S_ISVTX)
            return (1);
    return (0);
}

int is_not_sticky_and_ow(struct stat *sb)
{
    int mode = (sb->st_mode);

    if (mode & S_IWOTH)
        if (!(mode & S_ISVTX))
            return (1);
    return (0);
}

int is_sticky_and_not_ow(struct stat *sb)
{
    int mode = (sb->st_mode);

    if (mode & S_ISVTX)
        if (!(mode & S_IWOTH))
            return (1);
    return (0);
}

int is_sock(struct stat *sb)
{
    int mode = (sb->st_mode);

    if ((mode & S_IFMT) == S_IFSOCK)
        return (1);
    return (0);
}
