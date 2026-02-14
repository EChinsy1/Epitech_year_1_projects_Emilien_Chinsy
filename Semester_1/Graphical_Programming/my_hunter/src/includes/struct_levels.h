/*
** EPITECH PROJECT, 2025
** levels
** File description:
** a struct containing levels because I don't have time to parse a file
*/

#ifndef LEVELS_H_
    #define LEVELS_H_

    #include "my.h"
    #include "struct_elements.h"

typedef struct levels{
    int total_size;
    int level_speed;
    int num_of_normals;
    int num_of_evils;
    int num_of_supersonics;
    char *level_text;
} levels_t;

static const struct levels EACH_LEVEL[] = {
    {3, 3, 3, 0, 0,
        "Farmer, the birds are migrating, it's time to defend your grain."},
    {7, 4, 7, 0, 0,
        "They seem more resilient this year. Be careful."},
    {3, 3, 0, 3, 0,
         "The birds have mutated farmer! these ones look stronger and evil."},
    {6, 4, 3, 3, 0, "They just keep coming!"},
    {10, 5, 7, 3, 0, "They seem to really want your grain!"},
    {3, 1, 0, 0, 3,
        "Holy Macaroni! they even have supersonic birds!"},
    {6, 4, 3, 0, 3, "I don't get why there are so many coming here."},
    {9, 5, 3, 3, 3, "Why are they working together? They should be ennemies."},
    {29, 5, 15, 10, 4, "Brace yourself farmer, a huge final wave is coming."}};
#endif
