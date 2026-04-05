/*
** EPITECH PROJECT, 2025
** helper_functions
** File description:
** helper_functions
*/

#include "my.h"

static int my_swap_str(char *stra, char *strb)
{
    char temp;

    temp = *stra;
    *stra = *strb;
    *strb = temp;
    return (0);
}

static char *my_revstr(char *str)
{
    int len = strlen(str) - 1;
    int i = 0;

    if (len <= 0){
        return (str);
    }
    if (len % 2 == 1){
        while (1 < (len + 1 - i)){
            my_swap_str(&str[len], &str[i]);
            len--;
            i++;
        }
    } else {
        while ((len - i) != 0){
            my_swap_str(&str[len], &str[i]);
            len--;
            i++;
        }
    }
    return (str);
}

static int size_of_num(int nb)
{
    int result = 0;
    long number = nb;

    if (number < 0){
        number = number * -1;
        result++;
    }
    if (number == 0){
        result++;
    }
    while (number > 0){
        result++;
        number = number / 10;
    }
    return (result);
}

char *my_add_nbr(int nb)
{
    char *buffer = calloc(((size_of_num(nb)) + 1), sizeof(int));
    int i = 0;
    int sign = 0;

    if (nb < 0){
        sign = 1;
        nb = nb * -1;
    }
    if (nb == 0){
        buffer[i] = ('0');
        i++;
    }
    while (nb > 0){
        buffer[i] = ((nb % 10) + '0');
        nb = nb / 10;
        i++;
    }
    my_revstr(buffer);
    return (buffer);
}
