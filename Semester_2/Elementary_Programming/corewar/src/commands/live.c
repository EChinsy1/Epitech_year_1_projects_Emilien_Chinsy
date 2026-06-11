/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** File with the main corewar instructions
*/

#include "corewar.h"
#include "my.h"

int live_func(champs_t ***champ, int UNUSED champ_index,
    int **arg_and_types, UNUSED unsigned char **virt_machine)
{
    for (int i = 0; (*champ)[i]; ++i) {
        if ((*champ)[i]->player_id == arg_and_types[0][0]) {
            (*champ)[i]->alive = 1;
            my_dprintf(1, "The player %d(%s)is alive.\n",
                (*champ)[i]->player_id, (*champ)[i]->name);
        }
    }
    return (0);
}
