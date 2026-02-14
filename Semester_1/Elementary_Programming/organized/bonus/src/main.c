/*
** EPITECH PROJECT, 2025
** main
** File description:
** main
*/

#include <stdlib.h>
#include <unistd.h>
#include "my.h"
#include "shell.h"

int main(int argc, char **argv)
{
    main_t *element = my_calloc(sizeof(main_t), 1);
    int return_value = 0;

    if (element == NULL)
        return (ERROR);
    element->biggest = 0;
    return_value = workshop_shell(&element);
    if (return_value == ERROR) {
        my_printf("It seems you had an issue with the program, we have saved");
        my_printf(" your list under a file called savefile.\n");
        my_printf("You can get it back");
        my_printf(" by restarting organized and writing parse savefile\n");
        sort(&element, ((char *[3]){"ID", "-r", NULL}));
        create_save_file(element->list);
    }
    free_list(element->list);
    free(element);
    return (return_value);
}
