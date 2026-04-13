/*
** EPITECH PROJECT, 2026
** main
** File description:
** robot factory main
*/

#include <stdlib.h>
#include <stdio.h>
#include "macro.h"
#include "my.h"
#include "op.h"
#include "struct.h"

int write_commands(FILE *file, char **values, ins_t *instructions, int current)
{
    int result = SUCCESS;

    for (int j = 1; values[j] && values[j][0] != COMMENT_CHAR; ++j) {
        if (values[j][0] == REG_CHAR)
            result = write_reg(file, values[j]);
        if (values[j][0] == DIRECT_CHAR && values[j][1] != LABEL_CHAR)
            result = write_dir(file, values[j], values[0]);
        if (values[j][0] != DIRECT_CHAR && values[j][0] != REG_CHAR)
            result = write_ind(file, values[j]);
        if (values[j][0] == DIRECT_CHAR && values[j][1] == LABEL_CHAR)
            result = write_index(file, values[j], instructions, current);
        if (result == ERROR)
            return ERROR;
    }
    return SUCCESS;
}

int write_file(ins_t *instructions, FILE *file)
{
    header_t *header = my_calloc(sizeof(header_t), 1);
    int size = 0;

    if (!instructions || !file || !instructions->name || !instructions->comment) {
        free(header);
        return ERROR;
    }
    for (int i = 0; instructions->sizes && instructions->sizes[i] != -1; ++i)
        size += instructions->sizes[i];
    header->magic = __bswap_32(COREWAR_EXEC_MAGIC);
    for (int i = 0; instructions->name && instructions->name[i]; ++i)
        header->prog_name[i] = instructions->name[i];
    swap_endian(&size, 4);
    header->prog_size = size;
    for (int i = 0; instructions->comment[i]; ++i)
        header->comment[i] = instructions->comment[i];
    fwrite(header, sizeof(header_t), 1, file);
    free(header);
    return SUCCESS;
}

int write_the_rest(ins_t *instructions, FILE *file, int success_of_header)
{
    if (success_of_header == ERROR)
        return ERROR;
    if (!instructions->sizes)
        return (SUCCESS);
    for (int i = 0; instructions->commands[i]; ++i) {
        if (write_cmd_cod_byte(instructions->commands[i], file) == ERROR)
            return ERROR;
        if (write_commands(file,
                instructions->commands[i], instructions, i) == ERROR)
            return ERROR;
    }
    return SUCCESS;
}

static int write_help(int return_value)
{
    my_putstr("USAGE\n");
    my_putstr("./robot-factory file_name[.s]\n");
    my_putstr("DESCRITPION\n");
    my_putstr("file_name file in assembly language to be converted ");
    my_putstr("into file_name.cor, an executable in the Virtual Machine.\n");
    return return_value;
}

static int error_handling(char argc, char **argv)
{
    if (argc != 2)
        return (write_help(ERROR));
    if (my_strcmp(argv[1], "-h") == 0)
        return (write_help(0));
    if (argv[1][my_strlen(argv[1]) - 2] != '.' ||
        argv[1][my_strlen(argv[1]) - 1] != 's')
        return ERROR;
    return SUCCESS;
}

static char *get_file(char *file_name)
{
    char *result = NULL;
    int stock = -1;
    int len = my_strlen(file_name);

    for (int i = 0; file_name[i] != END_CHAR; ++i) {
        if (file_name[i] == '/')
            stock = i;
    }
    ++stock;
    result = my_calloc(sizeof(char), ((len - stock) + 3));
    my_strcat(result, &file_name[stock]);
    result[len - stock - 1] = 'c';
    result[len - stock] = 'o';
    result[len - stock + 1] = 'r';
    return result;
}

int find_pos_of_index(char *str)
{
    for (int i = 0; str[i]; ++i)
        if (str[i] == ':')
            return i;
    return FAIL;
}

int main(int argc, char **argv)
{
    ins_t *instructions = NULL;
    FILE *file = NULL;
    int return_value = 0;
    char *file_name = NULL;

    if (error_handling(argc, argv) != SUCCESS)
        return ERROR;
    instructions = parsing(argv[1]);
    if (instructions == NULL)
        return ERROR;
    file_name = get_file(argv[1]);
    file = fopen(file_name, "w");
    free(file_name);
    if (file == NULL)
        return ERROR;
    return_value = write_the_rest(instructions, file,
        write_file(instructions, file));
    free_instructions(instructions, file);
    return return_value;
}
