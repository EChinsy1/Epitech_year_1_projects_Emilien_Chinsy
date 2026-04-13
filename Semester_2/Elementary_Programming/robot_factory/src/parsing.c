/*
** EPITECH PROJECT, 2025
** robot_factory
** File description:
** parsing
*/

#include <linux/limits.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "op.h"
#include "macro.h"
#include "struct.h"
#include "my.h"

static ins_t *set_index(ins_t *instructions, char *value, int *step, int i)
{
    idx_t *new_index = NULL;
    int j = 0;

    if (i == FAIL)
        return instructions;
    new_index = my_calloc(sizeof(idx_t), 1);
    new_index->line = *step;
    new_index->value = my_strdup(&value[i + 1]);
    while (value[i] != ':')
        ++i;
    new_index->name = my_calloc(sizeof(char), (i + 1));
    my_strncat(new_index->name, value, i);
    while (instructions->indexes[j] != NULL) {
        if (my_strcmp(instructions->indexes[j]->name, new_index->name) == 0)
            return (NULL);
        ++j;
    }
    instructions->indexes[j] = new_index;
    return instructions;
}

static ins_t *set_argument(ins_t *instructions, int pos_of_index,
    char **word_array, int *step)
{
    int i = 0;

    if (instructions == NULL)
        return NULL;
    if (word_array == NULL)
        return (NULL);
    while (word_array[i])
        ++i;
    instructions->commands[*step - 2] = my_calloc(sizeof(char **), (i + 1));
    for (int j = 0; word_array[j]; ++j) {
        if (j == 0 && pos_of_index != FAIL)
            instructions->commands[*step - 2][j] =
                my_strdup(&word_array[j][pos_of_index + 1]);
        else
            instructions->commands[*step - 2][j] = my_strdup(word_array[j]);
        free(word_array[j]);
    }
    free(word_array);
    return instructions;
}

static ins_t *validate_arguments(ins_t *instructions, int *step,
    int index)
{
    int type = 0;
    int ind = -1;
    int size = 0;
    int stop = 0;

    for (int i = 1; instructions->commands[*step - 2][i]; ++i) {
        if (instructions->commands[*step - 2][i][0] == COMMENT_CHAR)
            stop = 1;
        ind = is_index_func(instructions->commands[*step - 2][0]);
        type = which_type(instructions->commands[*step - 2][i],
            &size, ind, stop);
        if (type == FAIL && stop != 1)
            return free_instructions(instructions, NULL);
        if ((op_tab[index].type[i - 1] & type) != type && stop != 1)
            return free_instructions(instructions, NULL);
        if (i > MAX_ARGS_NUMBER && stop != 1)
            return free_instructions(instructions, NULL);
    }
    size += 1;
    if (has_coding_byte(instructions->commands[*step - 2][0]) == SUCCESS)
        size += 1;
    instructions->sizes[(*step - 2)] = size;
    (*step)++;
    return instructions;
}

static ins_t *validate_command(ins_t *instructions, int *step)
{
    int index = 0;
    int num_args = 1;

    if (instructions == NULL)
        return NULL;
    while (index < 16 && (my_strcmp(instructions->commands
                [*step - 2][0], op_tab[index].mnemonique) != SUCCESS))
        ++index;
    if (index == 16)
        return (free_instructions(instructions, NULL));
    for (; instructions->commands[*step - 2][num_args] &&
        instructions->commands[*step - 2][num_args][0]
        != COMMENT_CHAR; ++num_args);
    if (num_args - 1 != op_tab[index].nbr_args)
        return free_instructions(instructions, NULL);
    return validate_arguments(instructions, step, index);
}

char *delete_char(char *buffer, char ch)
{
    int i = 0;
    int j = 0;
    int is_found = 0;
    int len = my_strlen(buffer);

    if (buffer == NULL || len <= 1)
        return (NULL);
    for (; i < len; i++) {
        if (buffer[i] != ch || is_found > 0) {
            buffer[j] = buffer[i];
            ++j;
        }
        if (buffer[i] == ch)
            ++is_found;
    }
    buffer[j] = '\0';
    return buffer;
}

ins_t *get_command(ins_t *instructions, char *buffer, int *step, FILE *file)
{
    char **word_array = NULL;
    int pos_of_index = 0;

    buffer = delete_char(buffer, '\t');
    instructions->commands = realloc(instructions->commands,
        (*step + 1) * sizeof(char **));
    instructions->commands[*step] = NULL;
    if (instructions->commands == NULL)
        return NULL;
    word_array = my_str_to_word_array(buffer, "\t ,");
    if (word_array == NULL || word_array[0] == NULL)
        return instructions;
    pos_of_index = find_pos_of_index(word_array[0]);
    instructions->sizes = realloc(instructions->sizes,
        (*step) * sizeof(int));
    instructions->sizes[*step - 1] = FAIL;
    instructions = set_index(instructions, buffer, step, pos_of_index);
    word_array = new_word_array(instructions, word_array, &pos_of_index, file);
    instructions = set_argument(instructions, pos_of_index, word_array, step);
    return validate_command(instructions, step);
}

static ins_t *get_comment(ins_t *instruction, int *step, char **word_array)
{
    (*step)++;
    word_array[0] = delete_char(word_array[0], '\t');
    if (my_strncmp(word_array[0], COMMENT_CMD_STRING,
            my_strlen(COMMENT_CMD_STRING) - 1) == SUCCESS
        && my_strlen(word_array[1]) <= COMMENT_LENGTH) {
        if (word_array[1] == NULL)
            instruction->comment = my_strdup("\0");
        else
            instruction->comment = my_strdup(word_array[1]);
    } else {
        return free_instructions(instruction, NULL);
    }
    return instruction;
}

static ins_t *get_name(ins_t *instruction, int *step, char **word_array)
{
    (*step)++;
    word_array[0] = delete_char(word_array[0], '\t');
    if (my_strncmp(word_array[0], NAME_CMD_STRING,
            my_strlen(NAME_CMD_STRING) - 1) == SUCCESS &&
        my_strlen(word_array[1]) <= PROG_NAME_LENGTH) {
        if (word_array[1] == NULL)
            instruction->name = my_strdup("\0");
        else
            instruction->name = my_strdup(word_array[1]);
    } else {
        return free_instructions(instruction, NULL);
    }
    return instruction;
}

ins_t *check_line(ins_t *instructions, char *buffer, int *step, FILE *file)
{
    char **word_array = NULL;

    if (buffer[0] == COMMENT_CHAR || buffer[0] == '\n')
        return instructions;
    if (*step >= 2)
        return get_command(instructions, buffer, step, file);
    word_array = remove_extra_spaces(my_str_to_word_array(buffer, "\t\""));
    if (*step == 1)
        instructions = get_comment(instructions, step, word_array);
    if (*step == 0)
        instructions = get_name(instructions, step, word_array);
    for (int i = 0; word_array && word_array[i]; ++i)
        free(word_array[i]);
    free(word_array);
    return instructions;
}

ins_t *parsing(char *file_name)
{
    FILE *file = fopen(file_name, "r");
    ins_t *instructions = NULL;
    char *buffer = NULL;
    size_t size;
    int step = 0;
    struct stat sb;

    if (file == NULL || stat(file_name, &sb) || sb.st_size == 0)
        return NULL;
    instructions = my_calloc(sizeof(ins_t), 2);
    instructions->indexes = my_calloc(sizeof(idx_t), 3);
    while (getline(&buffer, &size, file) >= 0) {
        if (buffer[0] != COMMENT_CHAR)
            instructions = check_line(instructions, buffer, &step, file);
        if (instructions == NULL)
            return free_and_return(instructions, buffer, file);
    }
    return free_and_return(instructions, buffer, file);
}
