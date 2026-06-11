/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** Utils for gameplay
*/

#include <stdlib.h>
#include "corewar.h"
#include "op.h"
#include "my.h"

static int get_needed_size(int coding_bit, int command)
{
    if (coding_bit == REG_BYTE)
        return (T_REG);
    if (coding_bit == DIR_BYTE) {
        if (is_index[command].is_index == 0)
            return (DIR_SIZE);
        else
            return (IND_SIZE);
    }
    if (coding_bit == IND_BYTE)
        return (IND_SIZE);
    return 0;
}

static int get_arg_values(int coding_bit, int command,
    unsigned char *virt_machine, int *curr_index)
{
    int value = 0;
    int size = get_needed_size(coding_bit, command);

    for (int i = 0; i < size; ++i) {
        value = (value << 8) + virt_machine[*curr_index];
        ++(*curr_index);
    }
    if (size == 2)
        return (int)(short)value;
    return (int)value;
}

static int *get_cod_bits(int coding_byte, int command)
{
    int num_args = op_tab[command].nbr_args;
    int *coding_bits = my_calloc(sizeof(int), num_args + 1);
    int temp = 0;

    if (!coding_bits)
        return NULL;
    for (int i = 0; i < (4 - num_args); ++i)
        coding_byte = coding_byte >> 2;
    for (int curr = num_args - 1; curr >= 0; --curr) {
        temp = 3 & (coding_byte);
        coding_bits[curr] = temp;
        coding_byte = coding_byte >> 2;
    }
    return (coding_bits);
}

static int get_cod_byte(unsigned char *virt_machine, int *index, int command)
{
    for (int i = 0; coding_byte_size[i].name != NULL; ++i)
        if (coding_byte_size[i].index == command)
            return coding_byte_size[i].size;
    (*index)++;
    return (virt_machine[*index - 1]);
}

static void set_wait(champs_t ***champs, int *idx[2], int cmd)
{
    if ((*champs)[(*idx[1])]->wait == -1) {
        if (cmd < 17 && cmd > 0)
            (*champs)[(*idx[1])]->wait = op_tab[cmd].nbr_cycles - 1;
    } else
        (*champs)[(*idx[1])]->wait = (*champs)[(*idx[1])]->wait - 1;
}

void get_instr_args(int *idx[2], int cmd,
    unsigned char **vm, champs_t ***champs)
{
    int *coding_bits = NULL;
    int *args = NULL;

    if ((*champs)[(*idx[1])]->wait == 1) {
        args = my_calloc(sizeof(int), op_tab[cmd].nbr_args + 1);
        if (!args)
            return;
        coding_bits = get_cod_bits(get_cod_byte(*vm, idx[0], cmd), cmd);
        for (int cur = 0; cur < op_tab[cmd].nbr_args; ++cur)
            args[cur] = get_arg_values(coding_bits[cur], cmd, *vm, idx[0]);
        if (cmd < 17 && cmd > 0)
            cmd_fct[cmd].fptr(champs, (*idx[1]),
                ((int *[2]){args, coding_bits}), vm);
        free(coding_bits);
        free(args);
        (*champs)[(*idx[1])]->wait = -1;
        return;
    }
    set_wait(champs, idx, cmd);
}
