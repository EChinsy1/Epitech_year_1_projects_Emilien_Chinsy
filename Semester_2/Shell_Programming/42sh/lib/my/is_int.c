/*
** EPITECH PROJECT, 2026
** is_int
** File description:
** is int
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int is_int(const char *str)
{
    char *temp = strdup(str);
    int i = 0;

    if (temp == NULL)
        return -1;
    if (temp[strlen(temp) - 1] == '\n')
        temp[strlen(temp) - 1] = '\0';
    if (temp[0] == '-')
        i++;
    for (; temp[i] != '\0'; i++) {
        if (temp[i] < '0' || temp[i] > '9') {
            free(temp);
            return -1;
        }
    }
    free(temp);
    return 0;
}
