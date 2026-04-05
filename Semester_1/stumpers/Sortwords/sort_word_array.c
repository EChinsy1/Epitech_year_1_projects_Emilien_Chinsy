/*
** EPITECH PROJECT, 2026
** stumper
** File description:
** stumper
*/

#include <stdlib.h>
#include <unistd.h>
#include "my.h"

static int my_strlen(char *str)
{
    int i = 0;

    while (str[i] != '\0')
        ++i;
    return (i);
}

int get_num_of_words(char *str)
{
    int i = 0;
    int num = 1;
    int last = 0;

    while (str[i] != '\0') {
        if ((str[i] == ' ' || str[i] == '\t') && last == 0) {
            ++num;
            last = 1;
        }
        if (str[i] != ' ')
            last = 0;
        ++i;
    }
    return (num);
}

static char *my_strncat(char *src, char *dest, int n)
{
    int len_dest = my_strlen(dest);
    int i = 0;

    while (i < n) {
        dest[len_dest + i] = src[i];
        ++i;
    }
    return (dest);
}

char **my_str_to_word_array(char *str)
{
    int num_of_words = get_num_of_words(str);
    char **word_array = my_calloc(sizeof(char *), num_of_words + 2);
    int start = 0;
    int end = 0;

    word_array[num_of_words] = NULL;
    for (int i = 0; i < num_of_words; ++i) {
        while ((str[start] == ' ' || str[start] == '\t') && str[start] != '\0')
            ++start;
        end = start;
        while ((str[end] != ' ' && str[end] != '\t') && str[end] != '\0')
            ++end;
        word_array[i] = my_calloc(sizeof(char), (end - start + 2));
        my_strncat(&str[start], word_array[i], end - start);
        start = end;
    }
    return (word_array);
}

static int cmp_case_unsensitive(char char1, char char2)
{
    int result = 0;

    if (char1 >= 65 && char1 <= 90)
        char1 += 32;
    if (char2 >= 65 && char2 <= 90)
        char2 += 32;
    if (char1 > char2)
        return (1);
    if (char2 > char1)
        return (-1);
    return (0);
}

static int my_strcmp(char *str1, char *str2)
{
    int len1 = my_strlen(str1);
    int len2 = my_strlen(str2);
    int i = 0;
    int cmp = 0;

    while (str1[i] != '\0' && str2[i] != '\0') {
        if (i == len1)
            return (1);
        if (i == len2)
            return (-1);
        cmp = cmp_case_unsensitive(str1[i], str2[i]);
        if (cmp != 0)
            return (cmp);
        ++i;
    }
    return (0);
}

void swap(char **str1, char **str2)
{
    char *temp = NULL;

    if (my_strcmp(*str1, *str2) == 1) {
        temp = *str1;
        *str1 = *str2;
        *str2 = temp;
    }
}

char **sort_word_array(char **word_array, int size)
{
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j) {
            swap(&word_array[i], &word_array[j]);
        }
    return (word_array);
}

void free_word_array(char **word_array)
{
    int i = 0;

    while (word_array[i] != NULL) {
        free(word_array[i]);
        ++i;
    }
    free(word_array);
}
