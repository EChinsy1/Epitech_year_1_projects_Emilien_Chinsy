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

static int get_size_of_champ(champs_t ***champ)
{
    int i = 0;

    while ((*champ)[i]) {
        ++i;
    }
    return (i);
}

int fork_func(champs_t ***champ, int champ_index,
    int **arg_and_types, UNUSED unsigned char **virt_machine)
{
    int size = get_size_of_champ(champ);

    (*champ) = realloc((*champ), sizeof(champs_t **) * (size + 2));
    if (!(*champ))
        return FAILURE;
    (*champ)[size + 1] = NULL;
    (*champ)[size] = my_calloc(sizeof(champs_t), 1);
    if (!(*champ)[size])
        return FAILURE;
    (*champ)[size]->PC = (*champ)[champ_index]->PC +
        (arg_and_types[0][0] % IDX_MOD) % MEM_SIZE;
    (*champ)[size]->name = my_strdup((*champ)[champ_index]->name);
    (*champ)[size]->comment = my_strdup((*champ)[champ_index]->comment);
    (*champ)[size]->player_id = (*champ)[champ_index]->player_id;
    (*champ)[size]->carry = (*champ)[champ_index]->carry;
    (*champ)[size]->alive = (*champ)[champ_index]->alive;
    (*champ)[size]->wait = -1;
    for (int i = 0; i < REG_NUMBER; ++i)
        (*champ)[size]->registers[i] = (*champ)[champ_index]->registers[i];
    return (0);
}
