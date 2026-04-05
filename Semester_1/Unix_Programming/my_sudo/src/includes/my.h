/*
** EPITECH PROJECT, 2025
** my.h
** File description:
** my.h
*/

#ifndef MY_H_
    #define MY_H_
    #include <unistd.h>
    #include <stdio.h>
    #include <errno.h>
    #include <stdlib.h>
    #include <string.h>
    #include <crypt.h>
    #include <termios.h>
    #include <stdarg.h>

int get_user_id(char *name, int num_of_flags);
int get_group_id(char *name, int num_of_flags);
    #include "struct.h"
int print_help(int argc);
void free_flags(fnf_t **flags);
char *get_id(user_t *user);
list_t *get_all_groups(char *name);
void print_list(list_t *list);
int line_contains(char *line, char *to_check);
int check_groups(user_t *user, char *name);
int is_in(char *line, char *to_check);
char *get_real_password(char *name);
int get_password(char *user_name, char **buffer);
int check_password(char *user_name, int counter, user_t *user);
char *my_add_nbr(int nb);
fnf_t **parse(int argc, char **argv);
int size_of_list_t(list_t *list);
void free_list(list_t *list);

#endif
