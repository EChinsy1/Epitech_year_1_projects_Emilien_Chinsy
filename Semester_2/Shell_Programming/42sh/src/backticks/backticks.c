/*
** EPITECH PROJECT, 2026
** 42sh backticks
** File description:
** handle backticks, the backticks replace the string inside them
** with what is in the stdin after their execution.
*/

#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include "arguments.h"
#include "macros.h"
#include "redirections.h"
#include "my.h"

static void find_backtick_in_string(char *str, int *start, int *end)
{
    int found_one = 0;

    for (int i = 0; str[i]; ++i) {
        if (str[i] == '`' && found_one == 1) {
            *end = i;
            return;
        }
        if (str[i] == '`' && found_one == 0) {
            *start = i;
            found_one = 1;
        }
    }
}

static char **add_value_left(int pos[2], int i, char **word_array, char *hold)
{
    char *new_value_1 = NULL;

    new_value_1 = calloc(sizeof(char), pos[0] + 1 + strlen(word_array[i]));
    if (new_value_1 == NULL)
        return (NULL);
    strncat(new_value_1, hold, pos[0]);
    strcat(new_value_1, word_array[i]);
    free(word_array[i]);
    word_array[i] = new_value_1;
    return (word_array);
}

static char **add_values_to_sides(char **word_array, int i,
    char *hold, int size_of_temp)
{
    char *new_value_2 = NULL;
    int pos[2] = {-1};

    find_backtick_in_string(hold, &pos[0], &pos[1]);
    if (pos[0] != 0)
        word_array = add_value_left(pos, i, word_array, hold);
    if (pos[1] != strlen(hold) - 1) {
        new_value_2 = calloc(sizeof(char),
            strlen(hold) - pos[1] + 1 + strlen(word_array[size_of_temp]));
        if (new_value_2 == NULL)
            return (NULL);
        strcat(new_value_2, word_array[size_of_temp]);
        strcat(new_value_2, &hold[pos[1] + 1]);
        free(word_array[size_of_temp]);
        word_array[size_of_temp] = new_value_2;
    }
    free(hold);
    return (word_array);
}

static char **add_in_word_array(char **word_array, int i, args_t *args)
{
    FILE *fd = fopen(BACKTICK_FILE, "r");
    struct stat sb;
    char *buffer = NULL;
    char **word_array_temp = NULL;
    char *hold = strdup(word_array[i]);
    int size_of_temp = 0;

    if (stat(BACKTICK_FILE, &sb) == -1)
        return (NULL);
    buffer = calloc(sizeof(char), (sb.st_size + 1000));
    fread(buffer, sb.st_size, 1, fd);
    word_array_temp = my_backtick_str_to_word_array(buffer, 1, '\n');
    size_of_temp = get_size_of_char_star_star(word_array_temp);
    word_array = insert_in_word_array(word_array, word_array_temp, i);
    word_array = add_values_to_sides(word_array, i, hold, size_of_temp);
    fclose(fd);
    free_word_array(word_array_temp);
    free(buffer);
    return (word_array);
}

static args_t *copy_args(args_t *args)
{
    args_t *return_args = calloc(sizeof(args_t), 1);
    char **new_env = NULL;
    int size = 0;

    return_args->buffer = NULL;
    for (int i = 0; args->env[i]; ++i)
        ++size;
    new_env = my_calloc(sizeof(char *), size + 1);
    for (int i = 0; args->env[i]; ++i)
        new_env[i] = my_strdup(args->env[i]);
    return_args->home_dir = my_strdup(args->old_dir);
    return_args->history = init_history();
    return_args->local = NULL;
    return_args->trees = NULL;
    return_args->env = new_env;
    return_args->last_command_return = 0;
    return_args->old_dir = strdup(args->old_dir);
    return (return_args);
}

static void run_command(args_t *real_args, char *command,
    char **word_array, int i)
{
    size_t s = 0;
    args_t *temp_args = NULL;
    int j = 0;

    temp_args = copy_args(real_args);
    temp_args->buffer = strdup(&command[1]);
    temp_args->buffer[strlen(temp_args->buffer) - 1] = '\0';
    free_not_end(real_args);
    free_word_array(word_array);
    free(command);
    if (check_exclamation_mark(&(temp_args->buffer),
            temp_args->history, &s) == ERROR)
        _exit(1);
    if (history(temp_args->buffer, temp_args->history) == ERROR)
        _exit(1);
    exexcution(temp_args);
    free_not_end(temp_args);
    free(temp_args);
    _exit(1);
}

static char **update_with_command(char **word_arrays[3], args_t *args,
    int i, tree_t **tree_array)
{
    pid_t pid = 0;
    int status = 0;

    pid = fork();
    if (pid == -1) {
        printf("tkt yaura de l'error handling un jour tkt je le jure\n");
    } else if (pid == 0 && redirection_bb(BACKTICK_FILE, ">>") == 0) {
        free_word_array(word_arrays[1]);
        free(tree_array);
        run_command(args, *word_arrays[2], word_arrays[0], i);
    } else {
        waitpid(pid, &status, 0);
        word_arrays[0] = add_in_word_array(word_arrays[0], i, args);
    }
    return (word_arrays[0]);
}

static char *find_backticks(char *str)
{
    char *command = NULL;
    int start[2] = {-1};
    int curr = 0;

    find_backtick_in_string(str, &start[0], &start[1]);
    if (start[0] == -1 || start[1] == -1)
        return (NULL);
    command = calloc(sizeof(char), start[1] - start[0] + 2);
    for (int i = start[0]; i <= start[1]; ++i) {
        command[curr] = str[i];
        ++curr;
    }
    return (command);
}

char **backticks(char **word_array, args_t *args,
    char **word_array_to_free, tree_t **tree_array)
{
    FILE *fd = NULL;
    char *command = NULL;

    if (word_array == NULL)
        return (word_array);
    fd = fopen(BACKTICK_FILE, "w");
    if (fd == NULL)
        return (word_array);
    fclose(fd);
    for (int i = 0; word_array[i] != NULL; ++i) {
        command = find_backticks(word_array[i]);
        if (command != NULL) {
            word_array = update_with_command((
                    (char **[3]){word_array, word_array_to_free, &command}),
                args, i, tree_array);
            free(command);
        }
    }
    return (word_array);
}
