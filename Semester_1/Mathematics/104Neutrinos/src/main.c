/*
** EPITECH PROJECT, 2025
** main
** File description:
** maion
*/

#include <string.h>
#include "my.h"

int main(int ac, char **av)
{
    if (ac == 2 && strcmp(av[1], "-h") == 0) {
        h_flag();
        return 0;
    }
    if (error_handling(ac, av) == 84)
        return 84;
    main_loop(ac, av);
    return 0;
}
