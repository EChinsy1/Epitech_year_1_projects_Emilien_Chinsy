/*
** EPITECH PROJECT, 2025
** struct.h
** File description:
** linked lists :)
*/

#ifndef STRUCT_H_
    #define STRUCT_H_

typedef struct group_list {
    char *item;
    char *item_space;
    char *gid;
    char *gid_space;
    struct group_list *next;
} list_t;

typedef struct user {
    char *name;
    char *name_space;
    char *uid;
    char *uid_space;
    struct group_list *groups;
} user_t;

typedef struct flags_n_funcs {
    char flag;
    char *arg;
    int (*fptr)(char *value, int num_of_flags);
} fnf_t;

static const struct flags_n_funcs FLAGSNFUNCS[] = {
    {'u', NULL, &get_user_id},
    {'g', NULL, &get_group_id}};

#endif
