/*
** EPITECH PROJECT, 2026
** bs_minishell
** File description:
** my_string
*/

#ifndef MY_STRING
    #define MY_STRING
    #include <stddef.h>

int my_strlen(char *str);
char **my_str_to_wordarr(char *, char);
void free_wordarr(char **);
void put_wordarr(char **);
char *my_strdup(char *);
int my_lenwordarr(char **);
int my_strcmp(char *, char *);
char **my_wordarr_dup(char **);
int my_strncmp(char *, char *, int);
char *my_strcat(char *, char *);
char *my_strncat(char *, char *, int);
void *my_calloc(size_t, size_t);
char *my_strndup(char *, int);
int len_deli(char *, char);
int my_getnbr(char const *);
int my_len_nbr(int);
int mini_printf(char *, ...);
int is_number(char *str);
#endif /* MY_STRING */
