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

int my_strlen(char const *str);
int print_env(args_t *args, char **command_array);
int exit_func(args_t *args, char **command_array);
int my_strcmp(char const *str1, char const *str2);
int my_strncmp(char const *str1, char const *str2, int num);
int my_strcat(char *str1, char *str2);
int my_strncat(char *str1, char *str2, int num);
char **my_str_to_word_array(char *str, char *delim, args_t *args);
void *my_calloc(int size, int len);
char *my_strdup(char *str);
char *my_itao(unsigned int n);
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
int execute_each_function_tree(tree_t **tree, args_t *args);
void free_not_end(args_t *args);
char ***parse_stuff(char *str, char *delim);
tree_t **parse_trees(char *str, args_t *args);
void insert_tree(tree_t **tree, char **value, char *symbol);
void init_tree(tree_t **tree, char **value, char *symbol);
void infixe(tree_t *tree);
int redirection_s(char *file, char *call);
int redirection_ss(char *end, char *call);
int redirection_b(char *file, char *call);
int redirection_bb(char *file, char *call);
int redirection_b_n_err(char *file, char *call);
void infixe_free(tree_t *tree);
int count_commands(tree_t *tree);
void display_signal(args_t **args, tree_t *tree, int status, char *name);
tree_t **validate_tree(tree_t **trees, int index, args_t *args);
int broken_pipe_handling(int count, int status, tree_t *tree, args_t **args);


//pipe functions
void pipe_closer(int count, int pfildes[][2]);
int activate_correct_pipes(int i, int count, int pfildes[][2]);

//history functions
int add_to_history(args_t *args, char *command);

#endif
