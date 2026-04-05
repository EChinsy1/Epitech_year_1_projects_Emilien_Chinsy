/*
** EPITECH PROJECT, 2026
** bs_minishell
** File description:
** my_putnbr
*/

#include "prints.h"

int my_putnbr(int nb)
{
    if (nb < 0){
        my_putchar('-');
        nb = nb * - 1;
    }
    if (nb > 9){
        my_putnbr(nb / 10);
    }
    my_putchar((nb % 10) + '0');
    return 0;
}
