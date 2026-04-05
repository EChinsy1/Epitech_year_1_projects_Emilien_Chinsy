/*
** EPITECH PROJECT, 2026
** my_top
** File description:
** header file containing the uid_n_user typedef
*/

#ifndef UID_N_USER_H
    #define UID_N_USER_H

typedef struct uid_n_user {
    int uid;
    char *user;
    struct uid_n_user *next;
} uid_n_user_t;

#endif
