/*
** EPITECH PROJECT, 2025
** my.h
** File description:
** the include file
*/

#ifndef MY_H
    #define MY_H

    #include <dirent.h>
    #include <fcntl.h>
    #include <stdint.h>
    #include <sys/stat.h>
    #include <stdio.h>
    #include <errno.h>
    #include <stdlib.h>
    #include <time.h>
    #include <pwd.h>
    #include <grp.h>
    #include <unistd.h>
    #include "struct_file.h"
    #include <string.h>
    #include <linux/limits.h>

    #define EXIT_ERROR_ 84
int parsing(int const argc, char **argv, char_list_t **flags, list_t **paths);
int my_printf(char *format, ...);
void *my_calloc(size_t length, size_t size);
int my_strlen(char const *str);
char *my_strcat(char *dest, char const *src);
char *my_strncat(char *dest, char const *src, int n);
int my_show_word_array(char *const *tab);
int my_strcmp(char const *s1, char const *s2);
int my_strncmp(char const *s1, char const *s2, int n);
char *my_strdup(char const *src);
char *my_strlowcase(char *str);
char *my_strcpy(char *dst, char const *src);
void my_putchar(char c);
int my_putstr(char const *str);
int my_str_isalpha(char const *str);
int my_str_isnum(char const *str);
int flag_x_exists(const char to_check, char_list_t *flags);
int print_the_items_R(char **items, char *path, char *flags);
int go_to_new_paths(char *path,
    file_t *items,
    char_list_t *flags,
    list_t *paths);
int my_ls(char_list_t *flags, list_t *paths, int r_running);
int main(int argc, char **argv);
int print_the_items_l(file_t *items, char *path, int numpaths,
    char_list_t *flags);
char *my_revstr(char *str);
void free_flags(char_list_t *flags);
void free_paths(list_t *paths);
void free_items(file_t *head);
int get_num_of_flags(char_list_t *flags);
int get_num_of_paths(list_t *paths);
char *add_slash(char *path);
void show_stats(struct stat *sb, char *name, char *path);
void sort_the_items_t(file_t *items);
void show_each_name(list_t *paths, char_list_t *flags);
void print_errors(char *path);
int is_exec(struct stat *sb);
int is_dir(struct stat *sb);
int is_link(struct stat *sb);
int is_device(struct stat *sb);
int is_fifo(struct stat *sb);
int is_sock(struct stat *sb);
int is_sticky_and_ow(struct stat *sb);
int is_not_sticky_and_ow(struct stat *sb);
int is_sticky_and_not_ow(struct stat *sb);
void print_dir(char *name);
void print_device(char *name);
void print_link(char *name);
void print_exec(char *name);
void print_fifo(char *name);
void print_sock(char *name);
void print_sticky_and_ow(char *name);
void print_not_sticky_and_ow(char *name);
void print_sticky_and_not_ow(char *name);
void print_with_colors(char *name, char *path_complete);
int my_str_isnumalpha(char const *str);
void print_with_colors_l(char *name, char *path);

#endif
