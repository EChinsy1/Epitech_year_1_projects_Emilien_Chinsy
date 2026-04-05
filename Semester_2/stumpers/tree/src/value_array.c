/*
** EPITECH PROJECT, 2026
** value_array
** File description:
** value_array
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include "lib.h"
#include "my.h"

void swap(char **val1, char **val2)
{
    char *temp = NULL;

    if (my_strcmp(*val1, *val2) > 0) {
        temp = *val1;
        *val1 = *val2;
        *val2 = temp;
    }
}

char **sort(char **value_array)
{
    for (int i = 0; value_array[i]; ++i) {
        for (int j = i + 1; value_array[j]; ++j) {
            swap(&value_array[i], &value_array[j]);
        }
    }
    return (value_array);
}

static char **fill_value_array(char *name, int i, int depth)
{
    DIR *dir = opendir(name);
    char **value_array = malloc(sizeof(char *) * (i + 1));
    struct dirent *indir = NULL;

    if (!dir)
        return (NULL);
    if (depth == 0) {
        my_putstr(name);
        my_putstr("\n");
    }
    indir = readdir(dir);
    for (int j = 0; indir; ++j) {
        value_array[j] = my_strdup(indir->d_name);
        indir = readdir(dir);
    }
    value_array[i] = NULL;
    closedir(dir);
    return (value_array);
}

char **get_all_values(char *name, int depth)
{
    DIR *dir = opendir(name);
    struct dirent *indir = NULL;
    char **value_array = NULL;
    int i = 0;

    if (!dir)
        return (NULL);
    indir = readdir(dir);
    for (; indir; ++i)
        indir = readdir(dir);
    closedir(dir);
    value_array = fill_value_array(name, i, depth);
    return (sort(value_array));
}

void free_value_array(char **value_array)
{
    int i = 0;

    while (value_array[i]) {
        free(value_array[i]);
        ++i;
    }
    free(value_array);
}
