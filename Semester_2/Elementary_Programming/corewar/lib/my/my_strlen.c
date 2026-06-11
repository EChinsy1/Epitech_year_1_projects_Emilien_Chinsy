/*
** EPITECH PROJECT, 2025
** my_strlen
** File description:
** a reproduction of the library function strlen
*/

int my_strlen(char *str)
{
    int i = 0;

    if (str == ((void *)0))
        return (-1);
    while (str[i] != '\0')
        ++i;
    return (i);
}
