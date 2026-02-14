/*
** EPITECH PROJECT, 2025
** my.h
** File description:
** the header file for all the prototypes of functions in the lib
*/

#ifndef MY_H_
    #define MY_H_

    #include <stddef.h>
int my_getnbr(char const *str);
int my_put_nbr(int nb);
char *my_revstr(char *str);
char *my_strcat(char *dest, char const *src);
int my_strcmp(char const *s1, char const *s2);
char *my_strcpy(char *dst, char const *src);
char *my_strdup(char const *src);
int my_strlen(char const *str);
char *my_strncat(char *dest, char const *src, int nb);
int my_strncmp(char const *s1, char const *s2, int n);
char *my_strncpy(char *dest, char const *src, int n);
void *my_calloc(size_t length, size_t size);
void my_putchar(char c);

#endif
