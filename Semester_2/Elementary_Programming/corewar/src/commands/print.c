/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** File with the main corewar instructions
*/

#include "corewar.h"
#include "my.h"

int print_func(champs_t ***champ, int champ_index,
    int **arg_and_types, UNUSED unsigned char **virt_machine)
{
    if (arg_and_types[0][0] > REG_NUMBER || arg_and_types[0][0] <= 0
        || arg_and_types[1][0] != REG_BYTE)
        return (1);
    if ((*champ)[champ_index]->registers[arg_and_types[0][0]] == 42)
        my_putchar('*');
    else
        my_put_nbr_base_x(
            (*champ)[champ_index]->registers[arg_and_types[0][0]]);
    return (0);
}
