/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** repeat
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "arguments.h"
#include "scripting.h"
#include "my.h"

/*for foreach and if, make a foreach that gets everything
  and calls the actual foreach with each line.*/

static int contains_char(char *str, char c)
{
    int count = 0;

    for (int i = 0; str[i]; ++i)
        if (str[i] == c)
            ++count;
    return (count);
}

static char *remove_backslash_r(char *buffer)
{
    if (buffer[strlen(buffer) - 2] == '\r')
        buffer[strlen(buffer) - 2] = '\0';
    if (buffer[strlen(buffer) - 2] == '\n')
        buffer[strlen(buffer) - 2] = '\0';
    if (buffer[strlen(buffer) - 1] == '\n')
        buffer[strlen(buffer) - 1] = '\0';
    return (buffer);
}

static char **get_conditions(char *str, char **name, args_t *args)
{
    char **conditions = NULL;
    char **word_array = my_str_to_word_array(str, " ", args);

    if (get_size_of_char_star_star(word_array) != 3)
        return NULL;
    *name = strdup(word_array[1]);
    word_array[2][0] = ' ';
    word_array[2][strlen(word_array[2]) - 1] = '\0';
    conditions = backticks(my_str_to_word_array(word_array[2], " ", args),
        args, word_array, NULL);
    free_word_array(word_array);
    return (conditions);
}

static void free_after_exec_foreach(char **conditions,
    char **fake_command_array, char *name)
{
    if (conditions)
        free_word_array(conditions);
    free_word_array(fake_command_array);
    free(name);
}

int exec_foreach(char **foreach_values, args_t *args, FILE *file)
{
    char **conditions = NULL;
    char *name = NULL;
    char **fake_command_array = calloc(sizeof(char *), 3);

    if (foreach_values == NULL || (contains_char(foreach_values[0], '(') !=
            contains_char(foreach_values[0], ')')) ||
        (contains_char(foreach_values[0], ')') == 0))
        return (0);
    conditions = get_conditions(foreach_values[0], &name, args);
    for (int i = 0; conditions && conditions[i]; ++i) {
        fake_command_array[1] = calloc(sizeof(char),
            strlen(name) + strlen(conditions[i]) + 5);
        sprintf(fake_command_array[1], "%s=%s", name, conditions[i]);
        set_func(args, fake_command_array);
        for (int j = 1; foreach_values[j + 1]; ++j)
            exec(foreach_values[j], args);
        free(fake_command_array[1]);
    }
    free_after_exec_foreach(conditions, fake_command_array, name);
    return 0;
}

int foreach(char *buffer, args_t *args, FILE *file)
{
    char **foreach_values = calloc(sizeof(char *), 2);
    char *read = buffer;
    int size = 1;
    size_t getline_size = 0;

    foreach_values[0] = strdup(read);
    while (strncmp(read, "end", 3) != 0) {
        foreach_values = realloc(foreach_values, sizeof(char *) * (size + 2));
        if (getline(&read, &getline_size, file) < 0)
            return (84);
        read = remove_backslash_r(read);
        foreach_values[size] = strdup(read);
        foreach_values[size + 1] = NULL;
        ++size;
    }
    exec_foreach(foreach_values, args, file);
    free_word_array(foreach_values);
    free(read);
    return (1);
}
