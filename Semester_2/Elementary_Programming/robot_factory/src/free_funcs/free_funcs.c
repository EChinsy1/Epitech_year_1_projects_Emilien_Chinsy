/*
** EPITECH PROJECT, 2026
** main
** File description:
** robot factory main
*/

#include <stdlib.h>
#include <stdio.h>
#include "my.h"
#include "struct.h"

ins_t *free_and_return(ins_t *instructions, char *buffer, FILE *file)
{
    free(buffer);
    fclose(file);
    return (instructions);
}

static void free_intermediary(ins_t *instructions)
{
    for (int i = 0; instructions->commands && instructions->commands[i]; ++i) {
        for (int j = 0; instructions->commands[i][j]; ++j)
            free(instructions->commands[i][j]);
        free(instructions->commands[i]);
    }
    if (instructions->commands)
        free(instructions->commands);
    for (int i = 0; instructions->indexes && instructions->indexes[i]; ++i) {
        free(instructions->indexes[i]->name);
        free(instructions->indexes[i]->value);
        free(instructions->indexes[i]);
    }
}

ins_t *free_instructions(ins_t *instructions, FILE *file)
{
    if (!instructions)
        return (NULL);
    if (instructions->name)
        free(instructions->name);
    if (instructions->comment)
        free(instructions->comment);
    if (instructions->sizes)
        free(instructions->sizes);
    free_intermediary(instructions);
    if (instructions->indexes)
        free(instructions->indexes);
    if (file)
        fclose(file);
    free(instructions);
    return (NULL);
}
