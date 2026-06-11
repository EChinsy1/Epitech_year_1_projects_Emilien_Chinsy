/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** Autocompletion
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <glob.h>
#include "my.h"

void print_found(char **found, args_t *args, char *copy)
{
    if (copy != NULL)
        free(copy);
    if (found == NULL || found[0] == NULL)
        return;
    printf("\n");
    if (found == NULL)
        return;
    for (int i = 0; found[i] != NULL; ++i) {
        printf("%s\t", found[i]);
    }
    printf("\n");
    write_console_message();
    write(1, args->buffer, strlen(args->buffer));
}

static char *create_final_value(char **word_array, char *final_value)
{
    for (int j = 0; word_array[j]; ++j) {
        strcat(final_value, word_array[j]);
        strcat(final_value, " ");
    }
    return (final_value);
}

char *get_the_rest(char *value, args_t **args, char *copy)
{
    char **word_array = my_backtick_str_to_word_array(copy, 1, ' ');
    int i = 0;
    int total_len = 0;
    char *final_value = NULL;

    if (word_array == NULL)
        return (NULL);
    for (; word_array[i]; ++i)
        total_len += strlen(word_array[i]) + 2;
    free(word_array[i - 1]);
    word_array[i - 1] = strdup(value);
    final_value = calloc(sizeof(char), total_len * 2 + 2);
    if (!final_value) {
        free_word_array(word_array);
        return (NULL);
    }
    final_value = create_final_value(word_array, final_value);
    free_word_array(word_array);
    free(copy);
    return (final_value);
}

void update_and_show(char *value, args_t **args, char *copy, int *size)
{
    char *result = get_the_rest(value, args, copy);

    free((*args)->buffer);
    (*args)->buffer = result;
    *size = strlen((*args)->buffer);
    if ((*args)->buffer == NULL)
        return;
    write(STDIN_FILENO, "\r", 1);
    for (int i = 0; i < (*size + (*args)->size_of_cwd); ++i)
        write(STDIN_FILENO, " ", 1);
    write(STDIN_FILENO, "\r", 1);
    write_console_message();
    write(STDIN_FILENO, result, strlen(result));
}

char *get_buffer(char *buffer, char **copy)
{
    char *true_buffer = calloc(strlen(buffer) + 2, sizeof(char));
    char **word_array = NULL;
    int size = 0;

    word_array = my_backtick_str_to_word_array(buffer, 1, ' ');
    if (!word_array || word_array[0] == NULL ||
        buffer[strlen(buffer) - 1] == ' ' || !true_buffer) {
        free(*copy);
        *copy = NULL;
        if (true_buffer)
            free(true_buffer);
        if (word_array != NULL)
            free_word_array(word_array);
        return (strdup("*"));
    }
    for (; word_array[size]; ++size);
    strcat(true_buffer, word_array[size - 1]);
    strcat(true_buffer, "*");
    free_word_array(word_array);
    return (true_buffer);
}

void autocomplete(char *buffer, args_t **args, int *where, int *size)
{
    char **found = NULL;
    glob_t gstruct = {0};
    char *copy = strdup(buffer);
    char *true_buffer = get_buffer(buffer, &copy);
    int r = 0;

    if (!true_buffer)
        return;
    r = glob(true_buffer, GLOB_ERR, NULL, &gstruct);
    free(true_buffer);
    if (r == 0) {
        if (get_size_of_char_star_star(gstruct.gl_pathv) == 1
            && buffer[strlen(buffer) - 1] != ' ') {
            update_and_show(gstruct.gl_pathv[0], args, copy, size);
            *where = strlen((*args)->buffer);
        } else
            print_found(gstruct.gl_pathv, *args, copy);
        free_word_array(gstruct.gl_pathv);
    } else
        print_found(gstruct.gl_pathv, *args, copy);
}
