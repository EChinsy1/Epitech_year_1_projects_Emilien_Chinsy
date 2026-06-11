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
    #include "macros.h"

int array_len(char **array);
int my_strlen(char const *str);
int print_env(args_t *args, char **command_array);
int exit_func(args_t *args, char **command_array);
int my_strcmp(char const *str1, char const *str2);
int my_strncmp(char const *str1, char const *str2, int num);
int my_strcat(char *str1, char *str2);
int my_strncat(char *str1, char *str2, int num);
char **my_str_to_word_array(char *str, char *delim, args_t *args);
int find_equal(char *value);
int find_tab(char *value);
char *find_in_env(char *value, args_t *args);
char *find_in_history(char *value, args_t *args);
void free_word_array(char **word_array);
void *my_calloc(int size, int len);
char *my_strdup(char *str);
char *my_itao(unsigned int n);
int my_putstr(int fd, char *str);
void free_word_array(char **word_array);
char *get_directory_exec(args_t *args, char **command_array);
int cd_func(args_t *args, char **command_array);
int my_str_isprintable(char const *str);
int setenv_func(args_t *args, char **command_array);
int set_func(args_t *args, char **command_array);
int unsetenv_func(args_t *args, char **command_array);
int get_size_of_char_star_star(char **tab);
int find_value_in_char_star_star(char **haystack, char *needle);
char **modify_env(args_t *args, char *new_variable, char *new_value);
int execute_each_function_tree(tree_t **tree, args_t *args);
void free_not_end(args_t *args);
char ***parse_stuff(char *str, char *delim);
tree_t **parse_trees(char *str, args_t *args);
void insert_tree(tree_t **tree, char **value, char *symbol, size_t index);
void init_tree(tree_t **tree, char **value, char *symbol, size_t index);
void infixe(tree_t *tree);
void infixe_free(tree_t *tree);
int count_commands(tree_t *tree);
void display_signal(args_t **args, tree_t *tree, int status, pid_t pid);
int broken_pipe_handling(int count, int status, tree_t *tree, args_t **args);
int infixe_redirections(tree_t *tree);
int minishell(int argc, char **argv, char **env);
char **apply_globbings(char **word_array);
int is_int(const char *str);
char **remove_extra(char **word_array);
tree_t **validate_trees(tree_t **tree_array, args_t *args);
void free_tree_not_end(args_t **args);
void free_the_tree(args_t **args);
void my_array_free(int count, ...);
char **insert_in_word_array(char **array, char **insert, int index);
void write_console_message(void);
args_t create_args(int argc, char **argv, char **env);
int shrek(args_t *args, char **command_array);

//pipe functions
void pipe_closer(int count, int pfildes[][2]);
int activate_correct_pipes(int i, int count, int pfildes[][2]);
int my_pipe(args_t *args, char **command_array);

//history functions
int history(char *command, history_list_t *history);
int history_funct(args_t *args, UNUSED char**cmd);
history_list_t *init_history(void);
int check_exclamation_mark(char **buffer, history_list_t *history,
    size_t *size);
int alias_funct(args_t *args, char **command_array);
int check_alias(char **buffer, alias_t **alias, size_t *s);

//backticks
char **backticks(char **word_array, args_t *args,
    char **word_array_to_free, tree_t **tree_array);
char **my_backtick_str_to_word_array(char *str, int len, ...);


//autocomplete
void autocomplete(char *buffer, args_t **args, int *where, int *size);

//scripting
int scripting(char *file_name, int argc, char **argv, char **env);

void free_list(history_list_t *history);
void exexcution(args_t *args);
#endif
