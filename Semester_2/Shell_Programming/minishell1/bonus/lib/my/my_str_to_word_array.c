/*
** EPITECH PROJECT, 2025
** my_str_to_word_array
** File description:
** write a function that splits a string into word
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "my.h"

void free_word_array(char **word_array)
{
    if (word_array == NULL)
        return;
    for (int i = 0; word_array[i]; ++i) {
        free(word_array[i]);
    }
    free(word_array);
}

int in_delim(char *delim, char needle)
{
    int i = 0;

    while (delim[i] != '\0') {
        if (delim[i] == needle) {
            return (1);
        }
        ++i;
    }
    return (0);
}

int get_num_of_words(char *str, char *delim)
{
    int i = 0;
    int num = 1;
    int last = 0;

    if (str == NULL)
        return (-1);
    while (str[i] != '\0' && in_delim(delim, str[i]) == 1)
        ++i;
    while (str[i] != '\0') {
        if (in_delim(delim, str[i]) == 1 && str[i] != '\n' && last == 0) {
            ++num;
            last = 1;
        }
        if (in_delim(delim, str[i]) == 0 && str[i] != '\n' && str[i] != '\0')
            last = 0;
        ++i;
    }
    if (last == 1)
        num = num - 1;
    return (num);
}

char **remove_extras(char **word_array, int words)
{
    word_array[words] = NULL;
    if (word_array[words - 1][my_strlen(word_array[words - 1]) - 1] == '\n')
        word_array[words - 1][my_strlen(word_array[words - 1]) - 1] = '\0';
    return (word_array);
}

char **my_str_to_word_array(char *str, char *delim)
{
    int words = get_num_of_words(str, delim);
    char **word_array = my_calloc(sizeof(char *), words + 1);
    int start = 0;
    int end = 0;

    if (words == -1)
        return (NULL);
    for (int i = 0; i < words; ++i) {
        while (in_delim(delim, str[start]) == 1 && str[start] != '\0')
            ++start;
        end = start;
        while (in_delim(delim, str[end]) == 0 && str[end] != '\0')
            ++end;
        if (end != start) {
            word_array[i] = my_calloc(sizeof(char), (end - start + 1));
            my_strncat(word_array[i], &str[start], end - start);
        }
        start = end;
    }
    return (remove_extras(word_array, words));
}
