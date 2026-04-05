/*
** EPITECH PROJECT, 2025
** type_checker
** File description:
** functions that will be used for color printing
*/

#include "my.h"

int is_fifo(struct stat *sb)
{
    if ((sb->st_mode & S_IFMT) == S_IFIFO)
        return (1);
    return (0);
}

int is_device(struct stat *sb)
{
    if ((sb->st_mode & S_IFMT) == S_IFBLK)
        return (1);
    if ((sb->st_mode & S_IFMT) == S_IFCHR)
        return (1);
    return (0);
}

int is_dir(struct stat *sb)
{
    if ((sb->st_mode & S_IFMT) == S_IFDIR)
        return (1);
    return (0);
}

int is_link(struct stat *sb)
{
    if ((sb->st_mode & S_IFMT) == S_IFLNK)
        return (1);
    return (0);
}

int is_exec(struct stat *sb)
{
    if ((sb->st_mode & S_IFMT) == S_IFREG){
        if (sb->st_mode & S_IXUSR)
            return (1);
    }
    return (0);
}
