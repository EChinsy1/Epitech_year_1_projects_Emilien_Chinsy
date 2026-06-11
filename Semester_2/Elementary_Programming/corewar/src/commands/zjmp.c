/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** File with the main corewar instructions
*/

#include "corewar.h"

int zjmp_func(champs_t ***champ, int champ_index,
    int **arg_and_types, UNUSED unsigned char **virt_machine)
{
    if ((*champ)[champ_index]->carry == 1) {
        (*champ)[champ_index]->PC = ((*champ)[champ_index]->PC +
            arg_and_types[0][0]) % MEM_SIZE;
    }
    return (0);
}
