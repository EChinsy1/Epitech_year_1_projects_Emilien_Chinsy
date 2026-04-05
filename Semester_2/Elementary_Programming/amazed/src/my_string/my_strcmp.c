/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** my_strcmp
*/

int my_strcmp(char const *s1, char const *s2)
{
    int index = 0;

    if (!s1 || !s2)
        return -2;
    while (s1[index] != '\0'){
        if (s2[index] == '\0')
            return (1);
        if (s1[index] > s2[index])
            return (1);
        if (s1[index] < s2[index])
            return (-1);
        index++;
    }
    if (s2[index] == '\0')
        return (0);
    return (-1);
}
