/*
** EPITECH PROJECT, 2025
** concat_params
** File description:
** a function that concatenates all paramters given to the main function
*/

#include <stdlib.h>
#include "my.h"

static int get_total_size(int argc, char **argv)
{
    int i = 0;
    int result = 0;
    int j = 0;

    while (i < argc){
        while (argv[i][j] != '\0'){
            j++;
            result++;
        }
        j = 0;
        i++;
    }
    return (result);
}

char *concat_params(int argc, char **argv)
{
    int total_size = get_total_size(argc, argv);
    char *new_str = malloc(sizeof(char) * (total_size + argc + 1));
    int i = 0;
    char newline[] = "\n";

    while (i < argc){
        my_strcat(new_str, argv[i]);
        my_strcat(new_str, newline);
        i++;
    }
    return (new_str);
}
