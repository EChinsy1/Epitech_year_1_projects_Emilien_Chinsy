/*
** EPITECH PROJECT, 2025
** write_cmd_cod_byte
** File description:
** writes a command opcode and codingbyte
*/

#include <endian.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include "op.h"
#include "my.h"
#include "macro.h"
#include "struct.h"

void swap_endian(void *data, size_t size)
{
    uint8_t *bytes = (uint8_t *)data;
    uint8_t tmp;

    for (size_t i = 0; i < size / 2; i++) {
        tmp = bytes[i];
        bytes[i] = bytes[size - 1 - i];
        bytes[size - 1 - i] = tmp;
    }
}

int write_reg(FILE *file, char *value)
{
    int number = my_getnbr(&value[1]);

    if (number > REG_NUMBER)
        return ERROR;
    fwrite(&number, T_REG, 1, file);
    return SUCCESS;
}

int write_dir(FILE *file, char *value, char *cmd)
{
    int number = my_getnbr(&value[1]);
    int index = -1;

    index = is_index_func(cmd);
    if (number == 0 && value[1] != '0')
        return ERROR;
    if (is_index[index].is_index == 0) {
        swap_endian(&number, DIR_SIZE);
        fwrite(&number, DIR_SIZE, 1, file);
    } else {
        swap_endian(&number, IND_SIZE);
        fwrite(&number, IND_SIZE, 1, file);
    }
    return SUCCESS;
}

int write_ind(FILE *file, char *value)
{
    int number = my_getnbr(value);

    if (number == 0 && value[1] != '0')
        return ERROR;
    swap_endian(&number, IND_SIZE);
    fwrite(&number, IND_SIZE, 1, file);
    return SUCCESS;
}

int write_index(FILE *file, char *value, ins_t *instructions, int current)
{
    int index = -1;
    int offset = 0;

    for (int i = 0; instructions->indexes[i]; ++i) {
        if (my_strcmp(instructions->indexes[i]->name, &value[2]) == SUCCESS)
            index = instructions->indexes[i]->line;
    }
    if (index == -1)
        return ERROR;
    index = index - 2;
    if (current < index)
        for (int i = current; i < index; ++i)
            offset += instructions->sizes[i];
    else {
        for (int i = current - 1; i >= index; --i)
            offset -= instructions->sizes[i];
    }
    swap_endian(&offset, IND_SIZE);
    fwrite(&offset, IND_SIZE, 1, file);
    return SUCCESS;
}
