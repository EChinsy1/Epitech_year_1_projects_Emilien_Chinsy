/*
** EPITECH PROJECT, 2025
** struct file
** File description:
** a
*/

#ifndef STRUCT_FILE_
    #define STRUCT_FILE_

typedef struct file {
    char *name;
    char *path;
    struct file *next;
} file_t;

typedef struct linked_list {
    char *item;
    struct linked_list *next;
} list_t;

typedef struct char_linked_list {
    char item;
    struct char_linked_list *next;
} char_list_t;

#endif
