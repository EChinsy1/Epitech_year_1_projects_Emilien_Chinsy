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
char **my_str_to_word_array(char *str);
int get_len_of_args(char **args);
int disp(void *data, char **args);
int add(void *data, char **args);
int del(void *data, char **args);
int sort(void *data, char **args);
int save(void *data, char **args);
int cmp_func(void *one, void *two, char **args, int i);
int type_cmp_func(void *one, void *two, char **args, int i);
int rev_type_cmp_func(void *one, void *two, char **args, int i);
int name_cmp_func(void *one, void *two, char **args, int i);
int rev_name_cmp_func(void *one, void *two, char **args, int i);
int id_cmp_func(void *one, void *two, char **args, int i);
int rev_id_cmp_func(void *one, void *two, char **args, int i);
int empty(void *data, char **args);
int del(void *data, char **args);
int parse(void *data, char **args);
int stats(void *data, char **args);
int help(void *data, char **args);
void free_list(void *data);
int valid_type(char *type);
void print_actuators(void *material);
void print_device(void *material);
void print_processor(void *material);
void print_sensor(void *material);
void print_wire(void *material);
void free_word_array(char **word_array);
void free_list_element(linked_list_t *current, int print);
void material_printer(void *material, int color);
int create_save_file(linked_list_t *list);

#endif
