/*
** EPITECH PROJECT, 2026
** bs_minishell
** File description:
** my_strlen
*/

int my_strlen(char *str)
{
    int nb = 0;

    if (!str)
        return -1;
    for (int i = 0; str[i] != '\0'; i++){
        nb++;
    }
    return nb;
}
