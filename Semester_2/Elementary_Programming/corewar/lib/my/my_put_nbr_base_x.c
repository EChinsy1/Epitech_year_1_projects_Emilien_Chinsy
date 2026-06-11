/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** File with the main corewar instructions
*/

#include <stdlib.h>
#include "my.h"

static int size_of_num_base_x_maj(unsigned int nb)
{
    int result = 0;
    long number = nb;

    if (nb == 0)
        return (1);
    while (number > 0){
        result++;
        number = number / 16;
    }
    return (result);
}

static void write_nbr_base_x(char *buffer)
{
    my_revstr(buffer);
    my_putstr(buffer);
    free(buffer);
}

void my_put_nbr_base_x(int nb)
{
    unsigned int number = nb;
    char *buffer = my_calloc((size_of_num_base_x_maj(number) + 1),
        sizeof(char));
    int i = 0;
    char *base = "0123456789abcdef";

    if (!base)
        return;
    if (number == 0){
        buffer[i] = number + '0';
        i++;
    }
    while (number > 0){
        buffer[i] = base[(number % 16)];
        number = number / 16;
        i++;
    }
    buffer[i] = '\0';
    write_nbr_base_x(buffer);
}
