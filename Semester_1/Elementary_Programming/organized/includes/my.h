/*
** EPITECH PROJECT, 2025
** G-CPE-110 : Shell Boostrap
** File description:
** bootstrap.h
*/

#ifndef MY_H_
    #define MY_H_

    #include <sys/types.h>
    #include "macros.h"
    #include "list.h"

int my_printf(const char *format, ...);
int my_getnbr(char *str);
char *my_strdup(char const *src);
int my_strcmp(char const *one, char const *two);
void *my_calloc(size_t length, size_t size);
int my_strlen(char *str);
int get_len_of_args(char **args);
int disp(void *data, char **args);
int add(void *data, char **args);
int del(void *data, char **args);
int sort(void *data, char **args);
int cmp_func(void *one, void *two, char **args, int i);
int type_cmp_func(void *one, void *two, char **args, int i);
int rev_type_cmp_func(void *one, void *two, char **args, int i);
int name_cmp_func(void *one, void *two, char **args, int i);
int rev_name_cmp_func(void *one, void *two, char **args, int i);
int id_cmp_func(void *one, void *two, char **args, int i);
int rev_id_cmp_func(void *one, void *two, char **args, int i);
int del(void *data, char **args);
void free_list(void *data);
int valid_type(char *type);
void free_list_element(linked_list_t *current, int print);

static const char *const types[6] = {
    "ACTUATOR",
    "DEVICE",
    "WIRE",
    "SENSOR",
    "PROCESSOR",
    ((void *)0)};


#endif
