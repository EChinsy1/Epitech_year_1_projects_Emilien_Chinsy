/*
** EPITECH PROJECT, 2025
** main
** File description:
** main
*/

#include <stdio.h>
#include <stdlib.h>
#include "my.h"
#include "shell.h"

int main(int argc, char **argv)
{
    main_t *workshop = my_calloc(sizeof(main_t), 1);
    int return_value = 0;

    if (workshop == NULL)
        return (ERROR);
    workshop->biggest = 0;
    return_value = workshop_shell(&workshop);
    free_list(workshop->list);
    free(workshop);
    return (return_value);
}
