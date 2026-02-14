/*
** EPITECH PROJECT, 2025
** print types
** File description:
** print types
*/

#include <stdio.h>
#include "my.h"
#include "materials.h"

void print_actuators(void *material)
{
    printf("\x1b[01;32m%s\x1b[0m n°%d - \"%s\"\n",
        ((materials_t *)material)->type,
        ((materials_t *)material)->unique_id,
        ((materials_t *)material)->name);
}

void print_device(void *material)
{
    printf("\x1b[01;34m%s\x1b[0m n°%d - \"%s\"\n",
        ((materials_t *)material)->type,
        ((materials_t *)material)->unique_id,
        ((materials_t *)material)->name);
}

void print_processor(void *material)
{
    printf("\x1b[01;35m%s\x1b[0m n°%d - \"%s\"\n",
        ((materials_t *)material)->type,
        ((materials_t *)material)->unique_id,
        ((materials_t *)material)->name);
}

void print_sensor(void *material)
{
    printf("\x1b[01;36m%s\x1b[0m n°%d - \"%s\"\n",
        ((materials_t *)material)->type,
        ((materials_t *)material)->unique_id,
        ((materials_t *)material)->name);
}

void print_wire(void *material)
{
    printf("\x1b[01;31m%s\x1b[0m n°%d - \"%s\"\n",
        ((materials_t *)material)->type,
        ((materials_t *)material)->unique_id,
        ((materials_t *)material)->name);
}
