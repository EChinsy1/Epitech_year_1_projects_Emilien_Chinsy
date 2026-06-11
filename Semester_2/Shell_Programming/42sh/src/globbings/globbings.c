/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** globbings
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <glob.h>
#include "my.h"

char **insert_at_index(char **word_array, char **found, int index, int j)
{
    int size = get_size_of_char_star_star(word_array);

    if (size == -1)
        return (NULL);
    if (found[j + 1] != NULL) {
        word_array = realloc(word_array, (size + 2) * sizeof(char *));
        word_array[size + 1] = NULL;
        for (int i = size; i > index; --i)
            word_array[i] = word_array[i - 1];
        word_array[index] = strdup(found[j]);
        free(found[j]);
        return (word_array);
    } else {
        word_array = realloc(word_array, (size + 2) * sizeof(char *));
        word_array[size + 1] = NULL;
        free(word_array[index]);
        word_array[index] = strdup(found[j]);
        free(found[j]);
        return (word_array);
    }
}

int has_glob(char *word)
{
    for (int i = 0; word[i]; ++i) {
        if (HAS_GLOB(word[i]))
            return (1);
    }
    return (0);
}

static int print_error(char *value, int r)
{
    if (r == GLOB_NOMATCH)
        fprintf(stderr, "%s: No match.\n", value);
    else
        fprintf(stderr, "Idk what that error means\n");
    return (0);
}

char **globs(char **word_array, int *i)
{
    char **found = NULL;
    glob_t gstruct = {0};
    int r = 0;

    r = glob(word_array[*i], GLOB_ERR, NULL, &gstruct);
    if (r != 0) {
        print_error(word_array[*i], r);
        free_word_array(word_array);
        return (NULL);
    } else {
        found = gstruct.gl_pathv;
        for (int j = 0; found[j]; ++j) {
            word_array = insert_at_index(word_array, found, *i, j);
            *i += 1;
        }
        free(found);
        return (word_array);
    }
}

char **apply_globbings(char **word_array)
{
    for (int i = 0; word_array && word_array[i]; ++i) {
        if (has_glob(word_array[i]) == 1)
            word_array = globs(word_array, &i);
    }
    return (word_array);
}
