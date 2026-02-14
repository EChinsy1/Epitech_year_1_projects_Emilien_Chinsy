/*
** EPITECH PROJECT, 2025
** my_str_to_word_array
** File description:
** write a function that splits a string into word
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "my.h"

static int my_char_isal(char const str)
{
    if ((str <= 90 && str >= 65) || (str <= 122 && str >= 97)){
        return (1);
    }
    return (0);
}

static int my_char_isnm(char const str)
{
    if (str <= 57 && str >= 48){
        return (1);
    }
    return (0);
}

static int get_number_of_words(char const *str)
{
    int i = 0;
    int num_of_words = 0;

    if (str[0] == '\0'){
        return (0);
    }
    while (str[i] != '\0'){
        if (my_char_isnm(str[i]) == 1 ||
            my_char_isal(str[i]) == 1 ||
            str[i] == '-'){
            num_of_words++;
        }
        i++;
    }
    return (num_of_words);
}

static int update_the_result(char **result, char *temp, int curr, int j)
{
    if (j == 0){
        free(temp);
        temp = NULL;
        return (curr);
    }
    result[curr] = my_strdup(temp);
    free(temp);
    temp = NULL;
    curr = curr + 1;
    return (curr);
}

static char *create_the_result(char *temp, char const *str, int i, int j)
{
    temp = my_calloc(sizeof(char), (j + 1));
    my_strncat(temp, &str[i], j);
    return (temp);
}

char **my_str_to_word_array(char const *str)
{
    char **result = my_calloc(sizeof(char*), (get_number_of_words(str) + 1));
    int i = 0;
    int j = 0;
    int curr = 0;
    int stop = 0;
    char *temp = NULL;

    result[get_number_of_words(str)] = 0;
    while (str[i] != '\0' && stop == 0){
        while (my_char_isnm(str[i + j]) == 1 || my_char_isal(str[i + j]) == 1
            || str[i + j] == '-' || str[i + j] == '.'){
            j++;
        }
        temp = create_the_result(temp, str, i, j);
        curr = update_the_result(result, temp, curr, j);
        if (str[i + j] == '\0'){
            stop = 1;
        }
        i = i + j + 1;
        j = 0;
    }
    return (result);
}
