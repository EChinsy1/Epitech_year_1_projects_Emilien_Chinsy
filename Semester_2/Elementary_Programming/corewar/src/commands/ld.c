/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** File with the main corewar instructions
*/

#include <stdio.h>
#include "corewar.h"

int ld_func(champs_t ***champ, int champ_index,
    int **arg_and_types, unsigned char **virt_machine)
{
    int value = 0;

    if (arg_and_types[0][1] > REG_NUMBER ||
        arg_and_types[0][1] <= 0 || (arg_and_types[1][0] != IND_BYTE &&
            arg_and_types[1][0] != DIR_BYTE) || arg_and_types[1][1] != REG_BYTE)
        return (1);
    if (arg_and_types[1][0] == IND_BYTE) {
        for (int i = 0; i < REG_SIZE; ++i)
            value = (value << 8) | (*virt_machine)[((*champ)[champ_index]->PC
                    + (arg_and_types[0][0] + i) % IDX_MOD) % MEM_SIZE];
        (*champ)[champ_index]->registers[arg_and_types[0][1] - 1] = value;
    } else {
        (*champ)[champ_index]->registers[arg_and_types[0][1] - 1] =
            arg_and_types[0][0];
    }
    if ((*champ)[champ_index]->registers[arg_and_types[0][1] - 1] == 0)
        (*champ)[champ_index]->carry = 1;
    else
        (*champ)[champ_index]->carry = 0;
    return (0);
}
