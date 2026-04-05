/*
** EPITECH PROJECT, 2026
** my.h
** File description:
** my.h
*/

#ifndef MY_H_
    #define MY_H_

    #define ERROR 84
    #define SUCCESS 0
char **sort_word_array(char **word_array, int size);
int my_putchar(char c);
void free_word_array(char **word_array);
char **my_str_to_word_array(char *str);
int get_num_of_words(char *str);
void *my_calloc(int size, int length);

#endif
