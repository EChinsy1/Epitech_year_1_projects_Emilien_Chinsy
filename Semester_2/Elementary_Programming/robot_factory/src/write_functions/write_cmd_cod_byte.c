/*
** EPITECH PROJECT, 2025
** write_cmd_cod_byte
** File description:
** writes a command opcode and codingbyte
*/

#include <unistd.h>
#include <stdlib.h>
#include "op.h"
#include "my.h"
#include "macro.h"
#include "struct.h"

static args_type_t which_type_direct(char *str, int *size, int index)
{
    if (str[1] == END_CHAR || (str[1] != LABEL_CHAR
            && is_all_digits(&str[1]) == ERROR))
        return FAIL;
    if (str[1] == LABEL_CHAR && str[2] == END_CHAR)
        return FAIL;
    if (is_index[index].is_index == SUCCESS)
        *size += DIR_SIZE;
    else
        *size += IND_SIZE;
    return T_DIR;
}

args_type_t which_type(char *str, int *size, int index, int stop)
{
    if (stop == 1)
        return (0);
    if (str[0] == DIRECT_CHAR)
        return which_type_direct(str, size, index);
    if (str[0] == REG_CHAR) {
        if (str[1] == END_CHAR || is_all_digits(&str[1]) == ERROR
            || my_getnbr(&str[1]) > REG_NUMBER)
            return FAIL;
        *size += T_REG;
        return T_REG;
    }
    if (str[0] == LABEL_CHAR || is_all_digits(str) == SUCCESS) {
        *size += IND_SIZE;
        return T_IND;
    }
    return FAIL;
}

int is_index_func(char *cmd)
{
    for (int i = 0; is_index[i].is_index != -1; ++i) {
        if (my_strcmp(cmd, is_index[i].name) == SUCCESS) {
            return i;
        }
    }
    return FAIL;
}

int is_all_digits(char *str)
{
    int i = 0;

    while (str[i] != END_CHAR) {
        if (str[i] < '0' || str[i] > '9')
            return ERROR;
        i++;
    }
    return SUCCESS;
}

static char convert_val(char *str)
{
    if (str[0] == DIRECT_CHAR)
        return T_DIR;
    if (str[0] == REG_CHAR)
        return T_REG;
    if (str[0] == LABEL_CHAR || is_all_digits(str) == SUCCESS)
        return LABEL_CASE;
    return SUCCESS;
}

static char get_coding_byte(int nbr_args, char **array)
{
    char result = 0;

    for (int i = 0; i < nbr_args; i++) {
        result = result | (convert_val(array[i + 1]) << (6 - i * 2));
    }
    return result;
}

int has_coding_byte(char *cmd)
{
    if (my_strcmp("live", cmd) == SUCCESS ||
        my_strcmp("zjmp", cmd) == SUCCESS ||
        my_strcmp("fork", cmd) == SUCCESS ||
        my_strcmp("lfork", cmd) == SUCCESS)
        return ERROR;
    return SUCCESS;
}

static int check_and_write(char *cmd, char **array, int i, FILE *file)
{
    char coding;

    if (my_strcmp(cmd, op_tab[i].mnemonique) == SUCCESS) {
        fwrite(&(op_tab[i].code), 1, 1, file);
        if (has_coding_byte(op_tab[i].mnemonique) == SUCCESS) {
            coding = get_coding_byte(op_tab[i].nbr_args, array);
            fwrite(&coding, 1, 1, file);
        }
        return SUCCESS;
    }
    return ERROR;
}

int write_cmd_cod_byte(char **array, FILE *file)
{
    int i = 0;

    if (array == NULL)
        return ERROR;
    while (op_tab[i].mnemonique != 0) {
        if (check_and_write(array[0], array, i, file) == SUCCESS)
            return SUCCESS;
        i++;
    }
    write(1, "No such command\n", 17);
    return ERROR;
}
