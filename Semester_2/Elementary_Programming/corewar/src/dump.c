/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** File with the main corewar instructions
*/

#include <stdlib.h>
#include "corewar.h"
#include "my.h"
#include "op.h"

static int get_size_of_num(int check_num)
{
    int size = 0;
    int num = check_num;

    while (num > 9) {
        num = num / 10;
        ++size;
    }
    ++size;
    return (size);
}

static int print_champ_name(champs_t **champs, int i)
{
    if (champs[i]->alive == -1)
        return (0);
    my_putstr("  ");
    my_putstr(champs[i]->name);
    my_putchar('(');
    my_put_nbr(champs[i]->player_id);
    my_putstr("): ");
    my_putstr("alive\n");
    return (1);
}

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

static void my_put_nbr_base_x_maj(int nb)
{
    unsigned int number = nb;
    char *buffer = my_calloc((size_of_num_base_x_maj(number) + 1),
        sizeof(char));
    int i = 0;
    char *base = "0123456789ABCDEF";

    if (!buffer)
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
    my_revstr(buffer);
    my_putstr(buffer);
    free(buffer);
}

static void print_header_memory(void)
{
    my_putstr("Memory:   ");
    for (int i = 0; i < 32; ++i) {
        if (i < 16)
            my_putchar('0');
        my_put_nbr_base_x_maj(i);
        my_putchar(' ');
    }
    my_putchar('\n');
    my_putstr("         ");
    for (int i = 0; i < 32; ++i)
        my_putstr(" --");
    my_putchar('\n');
}

static void print_reg(champs_t **champs, int i)
{
    int counter = 0;

    for (int x = 0; x < REG_NUMBER; ++x) {
        my_putstr("    ");
        my_putchar('r');
        my_put_nbr(x + 1);
        if (x < 9)
            my_putchar(' ');
        my_putstr(": ");
        for (int j = size_of_num_base_x_maj(champs[i]->registers[x]);
            j < 8; ++j)
            my_putchar('0');
        my_put_nbr_base_x(champs[i]->registers[x]);
        ++counter;
        if (counter == 6) {
            my_putchar('\n');
            counter = 0;
        }
    }
    my_putchar('\n');
}

static void write_numbers(unsigned char *vm, int i)
{
    for (int x = 0; x < 32; ++x) {
        for (int j = size_of_num_base_x_maj(vm[x + i]); j < 2; ++j)
            my_putchar('0');
        my_put_nbr_base_x(vm[x + i]);
        my_putchar(' ');
    }
}

static void print_memory(unsigned char *vm)
{
    my_putchar('\n');
    print_header_memory();
    for (int i = 0; i < MEM_SIZE;) {
        for (int j = size_of_num_base_x_maj(i); j < 8; ++j)
            my_putchar('0');
        my_put_nbr_base_x_maj(i);
        my_putstr(": ");
        write_numbers(vm, i);
        my_putchar('\n');
        i += 32;
    }
}

void dump(champs_t **champs, unsigned char *vm, int cycles)
{
    my_putstr("Cycle: ");
    my_put_nbr(cycles);
    my_putchar('\n');
    my_putstr("Registers:\n");
    for (int i = 0; champs[i]; ++i) {
        if (print_champ_name(champs, i) == 0)
            continue;
        print_reg(champs, i);
        my_putstr("    ");
        my_putstr("PC : ");
        for (int j = get_size_of_num(champs[i]->PC); j < 8; ++j)
            my_putchar('0');
        my_put_nbr(champs[i]->PC);
        my_putstr("    ");
        my_putstr("carry: ");
        my_put_nbr(champs[i]->carry);
        my_putchar('\n');
    }
    print_memory(vm);
}
