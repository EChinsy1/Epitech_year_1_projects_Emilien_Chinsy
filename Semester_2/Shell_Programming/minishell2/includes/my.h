/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** my.h
*/

#ifndef MY_H_
    #define MY_H_

    #include "arguments.h"
    #include "tree.h"

//helpers
int get_size_of_char_star_star(char **tab);
int find_value_in_char_star_star(char **haystack, char *needle);
int count_commands(tree_t *tree);

//lib functions
int my_strlen(char *str);
int my_strcmp(char const *str1, char const *str2);
int my_strncmp(char const *str1, char const *str2, int num);
int my_strcat(char *str1, char *str2);
int my_strncat(char *str1, char *str2, int num);
char **my_str_to_word_array(char *str, char *delim);
void *my_calloc(int size, int len);
char *my_strdup(char *str);
int my_putstr(int fd, char *str);
int my_str_isprintable(char const *str);

//builtins
int unsetenv_func(args_t *args, char **command_array);
char **modify_env(args_t *args, char *new_variable, char *new_value);
int setenv_func(args_t *args, char **command_array);
int print_env(args_t *args, char **command_array);
int exit_func(args_t *args, char **command_array);
int cd_func(args_t *args, char **command_array);

//frees
void free_word_array(char **word_array);
void free_not_end(args_t *args);

//executions
char *get_directory_exec(args_t *args, char **command_array);
int execute_each_function_tree(tree_t **tree, args_t *args);

//parser | binary tree
tree_t **parse_trees(char *str, args_t *args);
void insert_tree(tree_t **tree, char **value, char *symbol);
void init_tree(tree_t **tree, char **value, char *symbol);
void infixe(tree_t *tree);
void infixe_free(tree_t *tree);
tree_t **validate_tree(tree_t **trees, int index, args_t *args);

//redirections
int redirection_s(char *file);
int redirection_ss(char *end);
int redirection_b(char *file);
int redirection_bb(char *file);

//signal
void display_signal(args_t **args, tree_t *tree, int status, char *name);

//pipe functions
void pipe_closer(int count, int pfildes[][2]);
int activate_correct_pipes(int i, int count, int pfildes[][2]);
int broken_pipe_handling(int count, int status, tree_t *tree, args_t **args);


#endif
