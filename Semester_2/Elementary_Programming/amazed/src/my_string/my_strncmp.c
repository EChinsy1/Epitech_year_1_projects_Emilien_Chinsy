/*
** EPITECH PROJECT, 2026
** minishell
** File description:
** my_strncmp
*/

int my_strncmp(char const *s1, char const *s2, int n)
{
    int index = 0;

    if (!s1 || !s2 || n < 1)
        return -2;
    for (; index < n && s1[index] != '\0'; index++){
        if (s2[index] == '\0'){
            return (1);
        }
        if (s1[index] > s2[index]){
            return (1);
        }
        if (s1[index] < s2[index]){
            return (-1);
        }
    }
    if (s2[index] == '\0')
        return (0);
    return (-1);
}
