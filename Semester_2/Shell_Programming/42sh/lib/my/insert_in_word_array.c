/*
** EPITECH PROJECT, 2025
** my_str_to_word_array
** File description:
** write a function that splits a string into word
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my.h"
#include "arguments.h"
#include "macros.h"

static int count_word(char **array)
{
    int i = 0;

    while (array[i] != NULL)
        i++;
    return i;
}

static int copy_until_index(char **dst, char **src, int index)
{
    int i = 0;

    while (i < index) {
        dst[i] = strdup(src[i]);
        i++;
    }
    return i;
}

static int copy_insert(char **dst, char **insert, int start)
{
    int j = 0;

    while (insert[j]) {
        dst[start + j] = strdup(insert[j]);
        j++;
    }
    return j;
}

static void copy_after(char **dst, char **src, int i, int k)
{
    while (src[i]) {
        dst[k] = strdup(src[i]);
        k++;
        i++;
    }
}

char **insert_in_word_array(char **array, char **insert, int index)
{
    int src_wc = count_word(array);
    int insert_wc = count_word(insert);
    char **new_array = calloc(src_wc + insert_wc, sizeof(char *));
    int k;

    k = copy_until_index(new_array, array, index);
    k += copy_insert(new_array, insert, k);
    copy_after(new_array, array, index + 1, k);
    new_array[src_wc + insert_wc - 1] = NULL;
    free_word_array(array);
    return new_array;
}
/*
int main(int argc, char **argv)
{
    char *array_1[5] = {"test", "phrase", "de", "con"};
    char *array_2[4] = {"i", "hope", "lmao"};
    char **array_result = insert_in_word_array(array_1, array_2, 2);

    for (int i = 0; array_result[i]; i++){
        printf("word %d = [%s]\n", i, array_result[i]);
    }
    return 0;
}
*/
