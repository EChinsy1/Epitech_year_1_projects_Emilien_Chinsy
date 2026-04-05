/*
** EPITECH PROJECT, 2026
** amazed
** File description:
** my_len_nbr
*/

int my_len_nbr(int nb)
{
    int len = 0;

    while (nb > 9){
        nb = nb / 10;
        len++;
    }
    len++;
    return len;
}
