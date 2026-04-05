/*
** EPITECH PROJECT, 2026
** my_top
** File description:
** a file to get the num of users
*/

#include <utmp.h>
#include "my_top.h"

int my_getnumusers(void)
{
    FILE *file;
    int num_of_users = 0;
    struct utmp usr;

    file = open_file(_PATH_UTMP);
    if (!file)
        return 0;
    while (fread((char *)&usr, sizeof(usr), 1, file) == 1) {
        if (*usr.ut_name && *usr.ut_line && *usr.ut_line != '~') {
            num_of_users++;
        }
    }
    fclose(file);
    return (num_of_users / 2);
}
