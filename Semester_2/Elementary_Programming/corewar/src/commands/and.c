/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** File with the main corewar instructions
*/

#include "op.h"
#include "corewar.h"

static int get_value(champs_t *champ, int argument,
    int argument_type, unsigned char **virt_machine)
{
    int val = 0;

    if (argument_type == REG_BYTE) {
        if (argument > REG_NUMBER || argument <= 0)
            return (-1);
        val = (champ->registers[argument - 1]);
    } else if (argument_type == IND_BYTE) {
        val = (*virt_machine)[champ->PC + (argument) % IDX_MOD];
    } else
        val = argument;
    return (val);
}

int and_func(champs_t ***champ, int champ_index,
    int **arg_and_types, unsigned char **virt_machine)
{
    int val_1 = 0;
    int val_2 = 0;

    if (arg_and_types[1][0] <= ELS_BYTE || arg_and_types[1][0] > IND_BYTE ||
        arg_and_types[1][1] <= ELS_BYTE || arg_and_types[1][1] > IND_BYTE ||
        arg_and_types[1][2] != REG_BYTE || arg_and_types[0][2] > REG_NUMBER
        || arg_and_types[0][2] <= 0)
        return (1);
    val_1 = get_value((*champ)[champ_index], arg_and_types[0][0],
        arg_and_types[1][0], virt_machine);
    val_2 = get_value((*champ)[champ_index], arg_and_types[0][1],
        arg_and_types[1][1], virt_machine);
    ((*champ)[champ_index]->registers[arg_and_types[0][2] - 1]) = val_1 & val_2;
    if (((*champ)[champ_index]->registers[arg_and_types[0][2] - 1]) == 0) {
        (*champ)[champ_index]->carry = 1;
    } else
        (*champ)[champ_index]->carry = 0;
    return (0);
}
