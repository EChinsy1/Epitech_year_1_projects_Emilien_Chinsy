/*
** EPITECH PROJECT, 2025
** save
** File description:
** a function that is called
** when the program ends to save the linked list
** of the current program
*/

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include "macros.h"
#include "materials.h"
#include "my.h"
#include "list.h"

static void write_in_fd(int fd, linked_list_t *list)
{
    char *type = ((materials_t *)list->data)->type;
    char *name = ((materials_t *)list->data)->name;

    write(fd, type, strlen(type));
    write(fd, " ", 1);
    write(fd, name, strlen(name));
    write(fd, "\n", 1);
}

int create_save_file(linked_list_t *list)
{
    int fd = open("savefile", (O_CREAT | O_APPEND | O_RDWR), 00664);
    int killfd = open("savefile", (O_CREAT | O_TRUNC | O_RDWR), 00664);
    linked_list_t *element = list;
    char *type = NULL;
    char *name = NULL;

    if (fd < 0 || killfd < 0)
        return (ERROR);
    write(killfd, "", 0);
    close(killfd);
    while (element) {
        write_in_fd(fd, element);
        element = element->next;
    }
    close(fd);
    return (SUCCESS);
}

int save(void *data, char **args)
{
    int num_of_args = get_len_of_args(args);

    if (num_of_args != 0)
        return (ERROR);
    return (create_save_file(((*(main_t **)data)->list)));
}
