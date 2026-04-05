/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** my.h
*/

#ifndef MY_H_
    #define MY_H_

    #include "arguments.h"

int my_strlen(char *str);
int print_env(args_t *args, char **command_array);
int exit_func(args_t *args, char **command_array);
int my_strcmp(char *str1, char *str2);
int my_strncmp(char *str1, char *str2, int num);
int my_strcat(char *str1, char *str2);
int my_strncat(char *str1, char *str2, int num);
char **my_str_to_word_array(char *str, char *delim);
void *my_calloc(int size, int len);
char *my_strdup(char *str);
int my_putstr(int fd, char *str);
void free_word_array(char **word_array);
char *get_directory_exec(args_t *args, char **command_array);
int cd_func(args_t *args, char **command_array);
int my_str_isprintable(char const *str);
int setenv_func(args_t *args, char **command_array);
int unsetenv_func(args_t *args, char **command_array);
int get_size_of_char_star_star(char **tab);
int find_value_in_char_star_star(char **haystack, char *needle);
char **modify_env(args_t *args, char *new_variable, char *new_value);
int execute_each_function(args_t *args);
void free_not_end(args_t *args);
char ***parse_stuff(char *str, char *delim);

#endif
