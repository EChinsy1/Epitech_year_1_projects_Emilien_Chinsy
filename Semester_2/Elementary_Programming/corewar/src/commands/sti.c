/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** File with the main corewar instructions
*/

#include <stdlib.h>
#include "op.h"
#include "corewar.h"
#include "my.h"

static int get_value(champs_t *champ, int argument,
    int argument_type, unsigned char **virt_machine)
{
    int val = 0;

    if (argument_type == REG_BYTE) {
        if (argument == 0 || argument > REG_NUMBER)
            return (-1);
        val = (champ->registers[argument - 1]);
    } else if (argument_type == IND_BYTE) {
        val = (*virt_machine)[(champ->PC + (argument) % IDX_MOD) % MEM_SIZE];
    } else
        val = argument;
    return (val);
}

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

static int free_and_return(int *values)
{
    free(values);
    return (0);
}

int sti_func(champs_t ***champ, int champ_index,
    int **arg_and_types, unsigned char **virt_machine)
{
    int val_1 = 0;
    int val_2 = 0;
    int *values = NULL;

    if (arg_and_types[1][0] != REG_BYTE ||
        arg_and_types[1][1] <= ELS_BYTE || arg_and_types[1][1] > IND_BYTE ||
        arg_and_types[1][2] <= ELS_BYTE || arg_and_types[1][2] > IND_BYTE)
        return (1);
    val_1 = get_value((*champ)[champ_index], arg_and_types[0][1],
        arg_and_types[1][1], virt_machine);
    val_2 = get_value((*champ)[champ_index], arg_and_types[0][2],
        arg_and_types[1][2], virt_machine);
    if (val_1 == -1 || val_2 == -1)
        return (0);
    values = cut_int_in_four(((*champ)[champ_index]->
            registers[arg_and_types[0][0] - 1]));
    for (int curr = 0; curr < 4; ++curr)
        (*virt_machine)[(((*champ)[champ_index]->PC + (val_1 + val_2 + curr)
                    % IDX_MOD) % MEM_SIZE)] = values[curr];
    return (free_and_return(values));
}
