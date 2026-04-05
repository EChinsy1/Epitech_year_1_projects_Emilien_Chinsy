/*
** EPITECH PROJECT, 2026
** etipech
** File description:
** etipech
*/

#include "../include/lib.h"
#include <stdlib.h>
#include "my.h"

int check_l_flag(char *s, int nb_arg)
{
    for (int i = 0; s[i]; i++){
        if (s[i] == 'a' || s[i] == 'd' || s[i] == 'L' || s[i] == 'F'){
            nb_arg++;
            continue;
        }
        if (s[i] == '-')
            continue;
        return (0);
    }
    return (nb_arg);
}

char **create_tab(int ac, char **av, char **tab_arg, int nb_arg)
{
    int y = 1;
    int onsenfou = 0;

    tab_arg = my_big_calloc(sizeof(char *), (nb_arg + 1));
    for (int i = 0; i < nb_arg; i++){
        while (check_l_flag(av[y], onsenfou) == 0)
            ++y;
        if (av[y][0] == '\0')
            y++;
        if (y > ac)
            return tab_arg;
        if (av[y][0] == '-') {
            tab_arg[i] = my_strchardup(av[y], 1);
            av[y]++;
        }
        if (av[y][0] != '-')
            tab_arg[i] = my_strchardup(av[y], 0);
        av[y]++;
    }
    return tab_arg;
}

char **create_dir(int ac, char **av, char **tab_arg, int nb_arg)
{
    int i = 0;
    int y = 1;
    int onsenfou = 0;

    tab_arg = my_big_calloc(sizeof(char *), (nb_arg + 1));
    for (; i < nb_arg; i++){
        while (check_l_flag(av[y], onsenfou) == 1)
            ++y;
        if (av[y][0] == '\0')
            y++;
        if (y > ac)
            return tab_arg;
        if (av[y][0] != '-')
            tab_arg[i] = my_strdup(av[y]);
        y++;
    }
    return tab_arg;
}

int check_arg(int ac, char **av, int nb_arg, int *nb_tab)
{
    for (int y = 1; y < ac; y++){
        if (check_l_flag(av[y], nb_arg)){
            nb_arg = check_l_flag(av[y], nb_arg);
            continue;
        } else {
            ++(*nb_tab);
        }
    }
    return nb_arg;
}

int main(int ac, char **av)
{
    char **tab_arg = NULL;
    char **tab_dir = NULL;
    int nb_arg = 0;
    int nb_dir = 0;

    if (ac > 1){
        nb_arg = check_arg(ac, av, nb_arg, &nb_dir);
        if (nb_arg < 0)
            return (84);
        tab_arg = create_tab(ac, av, tab_arg, nb_arg);
        tab_dir = create_dir(ac, av, tab_dir, nb_dir);
        pre_tree(tab_arg, tab_dir);
    }
    return (0);
}
