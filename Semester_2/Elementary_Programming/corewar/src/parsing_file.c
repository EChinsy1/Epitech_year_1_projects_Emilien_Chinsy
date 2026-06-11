/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** File that parses the champion
*/

#include <stdio.h>
#include <stdlib.h>
#include "corewar.h"
#include "my.h"

static champs_t *init_champ(void)
{
    champs_t *champion = my_calloc(sizeof(champs_t), 1);

    if (!champion)
        return NULL;
    champion->name = NULL;
    champion->comment = NULL;
    champion->prog_size = -1;
    champion->player_id = -1;
    champion->PC = -1;
    champion->alive = 0;
    champion->carry = 0;
    champion->wait = -1;
    for (int i = 0; i <= REG_NUMBER; ++i)
        champion->registers[i] = 0;
    return champion;
}

static int get_champion_instruction(FILE *file,
    unsigned char **virt_machine, int *idx)
{
    unsigned char info = 0;
    int store = *idx;

    for (; fread(&info, sizeof(unsigned char), 1, file); ++*idx)
        (*virt_machine)[*idx] = info;
    return (store);
}

static void fill_header(champs_t *champion, header_t *header, int i)
{
    champion->name = my_strdup(header->prog_name);
    champion->comment = my_strdup(header->comment);
    champion->prog_size = __builtin_bswap32(header->prog_size);
    champion->player_id = i;
    champion->registers[0] = champion->player_id;
}

static champs_t *get_champion(args_t *args,
    unsigned char **virt_machine, int *idx, int i)
{
    champs_t *champion = init_champ();
    header_t header;
    int pos = 0;
    FILE *file = fopen(args->files[i].prog_name, "r");

    if (!file || !champion)
        return (my_dprintf(2, EROPEN, args->files[i].prog_name), NULL);
    fread(&header, sizeof(header_t), 1, file);
    if (__builtin_bswap32(header.magic) != COREWAR_EXEC_MAGIC)
        return (my_puterr("Error: Magic Exec Number does not correspond.\n"),
            fclose(file), NULL);
    fill_header(champion, &header, i);
    *idx = (args->files[i].load_address != -1) ?
        (args->files[i].load_address % MEM_SIZE) : *idx;
    pos = get_champion_instruction(file, virt_machine, idx);
    *idx += MEM_SIZE / args->nb_files - champion->prog_size;
    champion->PC = (args->files[i].load_address != -1) ?
        (args->files[i].load_address % MEM_SIZE) : pos;
    fclose(file);
    return champion;
}

champs_t **get_champions(args_t *args, unsigned char **virt_machine)
{
    int idx = 0;
    champs_t **champions = my_calloc(sizeof(champs_t *), args->nb_files + 1);

    if (!champions)
        return (my_puterr("Error: Malloc assertion failed.\n"), NULL);
    for (int i = 0; i < args->nb_files; ++i) {
        champions[i] = get_champion(args, virt_machine, &idx, i);
        if (!champions[i])
            return NULL;
        champions[i]->player_id =
            (args->files[i].prog_nb == -1) ? i + 1 : args->files[i].prog_nb;
        champions[i]->registers[0] = champions[i]->player_id;
        free(args->files[i].prog_name);
    }
    return champions;
}
