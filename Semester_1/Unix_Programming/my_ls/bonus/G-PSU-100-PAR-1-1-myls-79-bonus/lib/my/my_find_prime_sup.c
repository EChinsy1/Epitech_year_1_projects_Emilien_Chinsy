/*
** EPITECH PROJECT, 2025
** my_find_prime_sup
** File description:
** task 7 day 5, I have to find the smallest,
**  prime number from the target
*/

#include "my.h"

static int my_is_prime_07(int nb)
{
    for (int i = 3; i < nb / 2; i = i + 2){
        if (nb % i == 0){
            return (1);
        }
    }
    return (0);
}

int my_find_prime_sup(int nb)
{
    if (nb % 2 == 0){
        return (nb);
    }
    for (int i = nb; i < 2147483647; i = i + 2){
        if (my_is_prime_07(i) == 1){
            return (i);
        }
    }
    return (0);
}
