/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** File with the main corewar instructions
*/

#include "op.h"
#include "corewar.h"

int sub_func(champs_t ***champ, int champ_index,
    int **arg_and_types, UNUSED unsigned char **virt_machine)
{
    if (arg_and_types[0][0] > REG_NUMBER || arg_and_types[0][0] <= 0
        || arg_and_types[0][1] >
        REG_NUMBER || arg_and_types[0][1] <= 0 ||
        arg_and_types[0][2] > REG_NUMBER ||
        arg_and_types[0][2] <= 0 || arg_and_types[1][0] != REG_BYTE ||
        arg_and_types[1][1] != REG_BYTE || arg_and_types[1][2] != REG_BYTE)
        return (1);
    ((*champ)[champ_index]->registers[arg_and_types[0][2] - 1]) =
        ((*champ)[champ_index]->registers[arg_and_types[0][1] - 1]) -
        ((*champ)[champ_index]->registers[arg_and_types[0][0] - 1]);
    if (((*champ)[champ_index]->registers[arg_and_types[0][2] - 1]) == 0)
        (*champ)[champ_index]->carry = 1;
    else
        (*champ)[champ_index]->carry = 0;
    return (0);
}
