/*
** EPITECH PROJECT, 2026
** 42sh backticks
** File description:
** handle backticks, the backticks replace the string inside them
** with what is in the stdin after their execution.
*/

#include <stdarg.h>
#include <stdlib.h>

static int is_word(char c, char *delims)
{
    for (int i = 0; delims[i] != 0; i++)
        if (c == delims[i])
            return 0;
    return 1;
}

static int amt_of_words(char *str, char *delims)
{
    int in_word = 0;
    int amt_of_words = 0;
    int index = 0;

    while (str[index] != 0){
        if (is_word(str[index], delims) != in_word){
            in_word = (in_word + 1) % 2;
            amt_of_words += in_word;
        }
        index++;
    }
    return amt_of_words;
}

static int word_len(char *str, char *delims)
{
    int len = 0;

    while (is_word(str[len], delims) && str[len] != 0)
        len++;
    return len;
}

static char *copy_word(char *str, int start_index, char *delims)
{
    char *copy = malloc(sizeof(char) *
        (word_len(&str[start_index], delims) + 1));
    int local_index = start_index;

    while (is_word(str[local_index], delims) && str[local_index] != 0){
        copy[local_index - start_index] = str[local_index];
        local_index++;
    }
    copy[local_index - start_index] = 0;
    return copy;
}

static char *get_delims(va_list list, int len)
{
    char *delims = calloc(len + 1, sizeof(char));

    for (int i = 0; i < len; i++)
        delims[i] = (char)va_arg(list, int);
    va_end(list);
    return delims;
}

char **my_backtick_str_to_word_array(char *str, int len, ...)
{
    va_list args;
    char *delims = NULL;
    char **split_string = NULL;
    int array_index = 0;
    int str_index = 0;

    va_start(args, len);
    delims = get_delims(args, len);
    split_string = calloc(sizeof(char *), (amt_of_words(str, delims) + 1));
    while (str[str_index] != 0 && array_index < amt_of_words(str, delims)){
        while (is_word(str[str_index], delims) != 1 && str[str_index] != 0)
            str_index++;
        split_string[array_index] = copy_word(str, str_index, delims);
        while (is_word(str[str_index], delims) && str[str_index] != 0)
            str_index++;
        array_index++;
    }
    free(delims);
    return split_string;
}
