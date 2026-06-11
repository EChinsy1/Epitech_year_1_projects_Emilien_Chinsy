/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** File with the main corewar instructions
*/

#include <stdlib.h>
#include <stdio.h>
#include "corewar.h"
#include "my.h"

static void help_message(void)
{
    my_putstr("USAGE\n./corewar [-dump nbr_cycle] [[-n prog_number]"
        " [-a load_address] prog_name] ...\n"
        "DESCRIPTION\n"
        "-dump nbr_cycle dumps the state of the virtual machine"
        " after the nbr_cycle execution\n"
        "-n prog_number sets the next program’s number."
        " By default, the first free number in the parameter order\n"
        "-a load_address sets the next program’s loading address."
        " When no address is specified, optimize the addresses"
        " so that the processes are as far away from each other as possible."
        " The addresses are MEM_SIZE modulo\n");
}

static int error_handling(args_t *args)
{
    if (args->nbr_cycle == FLAG_FAIL)
        return FAILURE;
    if (args->nb_files < 1) {
        my_puterr("Error: No champion file found.\n");
        return FAILURE;
    }
    return SUCCESS;
}

int corewar(int ac, char **av)
{
    args_t args = arguments(av);
    champs_t **champions = NULL;
    unsigned char *virt_machine = my_calloc(sizeof(char), MEM_SIZE);

    if (ac == 2 && my_strcmp(av[1], "-h") == 0) {
        help_message();
        return SUCCESS;
    }
    if (error_handling(&args) == FAILURE || !virt_machine)
        return FAILURE;
    if (args.nb_files == 1)
        my_putstr("This champion is alone in the arena,"
            " consider finding him some friends :(\n");
    champions = get_champions(&args, &virt_machine);
    if (!champions)
        return FAILURE;
    gameplay(champions, virt_machine, &args);
    free(args.files);
    return SUCCESS;
}
