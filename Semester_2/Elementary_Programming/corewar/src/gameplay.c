/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** File with the main corewar instructions
*/

#include <stdlib.h>
#include <stdint.h>
#include "corewar.h"
#include "my.h"
#include "op.h"

static void update_cycles(int *live_nbr, int *cycles_to_die)
{
    if (*live_nbr >= NBR_LIVE) {
        (*cycles_to_die) -= CYCLE_DELTA;
        *live_nbr = 0;
    }
}

static void update_live_nbr(int cmd, champs_t ***champs, int j, int *live_nbr)
{
    if (cmd == 1 && (*champs)[j]->wait == -1)
        (*live_nbr)++;
}

static void gameplay_loop(champs_t ***champs, unsigned char *virt_machine,
    int *live_nbr, int *cycles_to_die)
{
    unsigned int hold = 0;
    int i = 0;
    int cmd = 0;

    for (int j = 0; (*champs)[j]; ++j) {
        if ((*champs)[j]->alive == -1)
            continue;
        i = ((*champs)[j]->PC + 1) % MEM_SIZE;
        cmd = virt_machine[((*champs)[j]->PC) % MEM_SIZE];
        if (cmd == 0) {
            (*champs)[j]->PC += 1;
            continue;
        }
        hold = (*champs)[j]->PC;
        get_instr_args((int *[2]){&i, &j}, cmd, &virt_machine, champs);
        update_live_nbr(cmd, champs, j, live_nbr);
        if (hold == (*champs)[j]->PC && cmd != 9 && (*champs)[j]->wait == -1)
            (*champs)[j]->PC = i % MEM_SIZE;
        update_cycles(live_nbr, cycles_to_die);
    }
}

static void check_for_state(champs_t ***champs, int *end, int *num_alive)
{
    for (int j = 0; (*champs)[j]; ++j) {
        if ((*champs)[j]->alive == 1) {
            ++*num_alive;
            my_dprintf(1, "The player %d(%s)has won.\n",
                (*champs)[j]->player_id, (*champs)[j]->name);
        }
        *end = 1;
    }
    if (*num_alive == 0)
        my_putstr("No player has won.\n");
}

static int handle_death(champs_t ***champs, int *end)
{
    int ids_alive[10];
    int num_alive = 0;

    for (int i = 0; i < 10; ++i)
        ids_alive[i] = 0;
    for (int j = 0; (*champs)[j]; ++j) {
        if ((*champs)[j]->alive == 1) {
            ids_alive[(*champs)[j]->player_id] = 1;
        } else
            (*champs)[j]->alive = -1;
    }
    for (int i = 0; i < 10; ++i)
        if (ids_alive[i] == 1)
            ++num_alive;
    if (num_alive > 1)
        return (0);
    check_for_state(champs, end, &num_alive);
    return (0);
}

static void free_all(champs_t **champs, unsigned char *virt_machine)
{
    for (int i = 0; champs[i]; ++i) {
        free(champs[i]->name);
        free(champs[i]->comment);
        free(champs[i]);
    }
    free(champs);
    free(virt_machine);
}

static void win_in_between(champs_t ***champs)
{
    int num_alive = 0;

    for (int j = 0; (*champs)[j]; ++j) {
        if ((*champs)[j]->alive == 1) {
            ++num_alive;
            my_dprintf(1, "The player %d(%s)has won.\n",
                (*champs)[j]->player_id, (*champs)[j]->name);
        }
    }
    if (num_alive == 0)
        my_putstr("No player has won.\n");
}

static int end_func(int dump_value, int cycles,
    champs_t **champs, unsigned char *virt_machine)
{
    if (dump_value != -1 && cycles < dump_value)
        dump(champs, virt_machine, cycles);
    free_all(champs, virt_machine);
    return 0;
}

static void handle_cycles_to_die(champs_t ***champs, int *end, int *i)
{
    handle_death(champs, end);
    *i = 0;
    for (int j = 0; (*champs)[j]; ++j) {
        if ((*champs)[j]->alive != -1)
            (*champs)[j]->alive = 0;
    }
}

int gameplay(champs_t **champs, unsigned char *virt_machine, args_t *args)
{
    int i = 0;
    int cycles_to_die = CYCLE_TO_DIE;
    int end = 0;
    int cycles = 0;
    int live_nbr = 0;
    int dump_value = args->nbr_cycle;

    while (end != 1 && cycles_to_die > 0) {
        if (dump_value != -1 && cycles >= dump_value) {
            dump(champs, virt_machine, cycles);
            win_in_between(&champs);
            break;
        }
        ++cycles;
        gameplay_loop(&champs, virt_machine, &live_nbr, &cycles_to_die);
        ++i;
        if (i >= cycles_to_die)
            handle_cycles_to_die(&champs, &end, &i);
    }
    return (end_func(dump_value, cycles, champs, virt_machine));
}
