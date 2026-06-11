/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** File with the main corewar instructions
*/

#include "my.h"
#include "op.h"
#include "corewar.h"
#include <stdlib.h>

static int *cut_int_in_four(int val_to_add)
{
    int *values = my_calloc(sizeof(int), 4);
    int val = 0;

    if (!values)
        return NULL;
    for (int curr = 3; curr >= 0; --curr) {
        val = 0xff & (val_to_add);
        values[curr] = val;
        val_to_add = val_to_add >> 8;
    }
    return (values);
}

int st_func(champs_t ***champ, int champ_index,
    int **arg_and_types, unsigned char **virt_machine)
{
    int *values = NULL;

    if (arg_and_types[0][0] > REG_NUMBER || arg_and_types[0][0] <= 0 ||
        (arg_and_types[1][1] != IND_BYTE &&
            arg_and_types[1][1] != REG_BYTE) || arg_and_types[1][0] != REG_BYTE)
        return (1);
    if (arg_and_types[1][1] == IND_BYTE) {
        values = cut_int_in_four(((*champ)[champ_index]->registers
                [arg_and_types[0][0] - 1]));
        for (int curr = 0; curr < 4; ++curr)
            (*virt_machine)[((*champ)[champ_index]->PC + (arg_and_types[0][1]
                        + curr) % IDX_MOD) % MEM_SIZE] = values[curr];
        free(values);
    } else
        (*champ)[champ_index]->registers[arg_and_types[0][1] - 1] =
            (*champ)[champ_index]->registers[arg_and_types[0][0] - 1];
    return (0);
}
