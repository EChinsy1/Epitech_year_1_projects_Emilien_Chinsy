/*
** EPITECH PROJECT, 2026
** pcube
** File description:
** matchsticks
*/

#include <unistd.h>

int is_num(char *str)
{
    if (str[0] == '\n')
        return (1);
    for (int i = 0; str[i]; ++i)
        if ((str[i] < '0' || str[i] > '9') && str[i] != '\n')
            return (0);
    return (1);
}

void my_putchar(char c)
{
    write(1, &c, 1);
}

int my_put_nbr(int nb)
{
    size_t temp = 0;

    if (nb > 9) {
        temp = nb % 10;
        my_put_nbr(nb / 10);
        my_putchar(temp + 48);
        return (0);
    } else {
        my_putchar(nb + 48);
        return (0);
    }
}

int my_getnbr(char const *str)
{
    long num = 0;
    int i = 0;

    for (int val = i; str[val] != '\0'; val++) {
        if ((((num * 10) + 8) > 2147483647)) {
            num = 0;
            break;
        }
        if (str[val] <= 57 && str[val] >= 48){
            num = num * 10 + (str[val] - 48);
        } else {
            break;
        }
    }
    return (num);
}

int my_strlen(char *str)
{
    int i = 0;

    while (str[i])
        ++i;
    return (i);
}
