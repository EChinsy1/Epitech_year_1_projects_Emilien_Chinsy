/*
** EPITECH PROJECT, 2025
** flag l printing
** File description:
** a file that holds the function that will be used to print
** when the l flag is put
*/

#include "my.h"
#include "time.h"

char get_file_type(struct stat *sb)
{
    switch (sb->st_mode & S_IFMT) {
        case S_IFLNK:
            return ('l');
        case S_IFBLK:
            return ('B');
        case S_IFIFO:
            return ('p');
        case S_IFDIR:
            return ('d');
        case S_IFSOCK:
            return ('s');
        case S_IFCHR:
            return ('c');
        default:
            return ('-');
    }
}

static void show_total(file_t *items)
{
    file_t *current = items;
    unsigned int total = 0;
    char *file_path;
    struct stat sb;

    while (current){
        file_path = my_calloc(sizeof(char),
            my_strlen(current->path) + my_strlen(current->name) + 2);
        my_strcpy(file_path, current->path);
        my_strcat(file_path, current->name);
        if (lstat(file_path, &sb) != -1)
            total += sb.st_blocks;
        free(file_path);
        current = current->next;
    }
    my_printf("total: %u\n", total / 2);
}

static void fill_perms(struct stat *sb, char file_type)
{
    char *rwx[] = {"---", "--x", "-w-", "-wx",
        "r--", "r-x", "rw-", "rwx"};
    char *bits = my_calloc(sizeof(char), 11);
    int mode = (sb->st_mode);

    bits[0] = file_type;
    my_strcpy(&bits[1], rwx[(mode >> 6) & 7]);
    my_strcpy(&bits[4], rwx[(mode >> 3) & 7]);
    my_strcpy(&bits[7], rwx[(mode & 7)]);
    if (mode & S_ISUID)
        bits[3] = (mode & S_IXUSR) ? 's' : 'S';
    if (mode & S_ISGID)
        bits[6] = (mode & S_IXGRP) ? 's' : 'l';
    if (mode & S_ISVTX)
        bits[9] = (mode & S_IXOTH) ? 't' : 'T';
    bits[10] = '\0';
    my_printf("%s", bits);
    free(bits);
}

void print_time(struct stat *sb)
{
    char *time = ctime(&sb->st_mtime);
    int i = 1;
    int j = 0;
    char *final_time;

    while (time[i - 1] != ' ')
        ++i;
    j = i;
    while (time[j - 1] != ':')
        ++j;
    while (time[j] != ':')
        ++j;
    final_time = my_calloc(sizeof(char), ((j - i) + 1));
    for (int y = 0; (y + i) < j; y++){
        final_time[y] = time[y + i];
    }
    final_time[j - i] = '\0';
    my_printf("%s ", final_time);
    free(final_time);
}

static void print_names(struct stat *sb)
{
    struct passwd *pw = getpwuid(sb->st_uid);
    struct group *gr = getgrgid(sb->st_gid);

    if (pw != NULL) {
        my_printf("%s ", pw->pw_name);
    } else {
        my_printf("%d ", sb->st_uid);
    }
    if (gr != NULL) {
        my_printf("%s ", gr->gr_name);
    } else {
        my_printf("%d ", sb->st_gid);
    }
}

static void show_link(char *path)
{
    char buff[PATH_MAX];
    int link_len;

    link_len = readlink(path, buff, sizeof(buff) - 1);
    if (link_len != -1){
        buff[link_len] = '\0';
        my_printf("-> %s", buff);
    }
}

void show_stats(struct stat *sb, char *name, char *path)
{
    char file_type = get_file_type(sb);
    int test = 0;

    fill_perms(sb, file_type);
    my_printf(" %d ", sb->st_nlink);
    print_names(sb);
    my_printf("%ld ", sb->st_size);
    print_time(sb);
    my_printf("%s", name);
    if ((sb->st_mode & S_IFMT) == S_IFLNK)
        show_link(path);
    my_printf("\n");
}

static void item_printer_l(file_t *items, char *path)
{
    struct stat sb;
    int i = 0;
    file_t *current = items;
    char *file_path;

    show_total(items);
    while (current){
        file_path = my_calloc(sizeof(char),
            my_strlen(current->path) + my_strlen(current->name) + 2);
        my_strcpy(file_path, current->path);
        my_strcat(file_path, current->name);
        if (lstat(file_path, &sb) != -1)
            show_stats(&sb, current->name, file_path);
        free(file_path);
        current = current->next;
    }
}

int print_the_items_l(file_t *items,
    char *path,
    int numpaths,
    char_list_t *flags)
{
    if (numpaths > 1 || flag_x_exists('R', flags) == 1){
        write(1, path, my_strlen(path) - 1);
        my_printf(":\n");
    }
    item_printer_l(items, path);
    return (0);
}
