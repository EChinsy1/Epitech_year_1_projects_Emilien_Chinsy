/*
** EPITECH PROJECT, 2026
** my_top
** File description:
** file to get the value to fill the MiB Mem and MiB Swap columns.
*/

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include "mem_struct.h"
#include "my_top.h"

void fill_mem_part(mem_struct_t *memory_info, FILE *file)
{
    char *buffer = NULL;
    char *value = NULL;
    size_t size = 0;

    getline(&buffer, &size, file);
    value = strtok(buffer, " ");
    memory_info->MemTotal = strtold(strtok(NULL, " "), NULL);
    getline(&buffer, &size, file);
    value = strtok(buffer, " ");
    memory_info->MemFree = strtold(strtok(NULL, " "), NULL);
    getline(&buffer, &size, file);
    value = strtok(buffer, " ");
    memory_info->avail_mem = strtold(strtok(NULL, " "), NULL);
    getline(&buffer, &size, file);
    value = strtok(buffer, " ");
    memory_info->buff_cache = strtold(strtok(NULL, " "), NULL);
    memory_info->MemUsed = (memory_info->MemTotal - memory_info->avail_mem);
    free(buffer);
}

void fill_swap_part(mem_struct_t *memory_info, FILE *file)
{
    char *buffer = NULL;
    char *value = NULL;
    size_t size = 0;

    getline(&buffer, &size, file);
    value = strtok(buffer, " ");
    memory_info->buff_cache += strtold(strtok(NULL, " "), NULL);
    for (int i = 0; i < 10; i++)
        getline(&buffer, &size, file);
    value = strtok(buffer, " ");
    memory_info->SwapTotal = atof(strtok(NULL, " "));
    getline(&buffer, &size, file);
    value = strtok(buffer, " ");
    memory_info->SwapFree = atof(strtok(NULL, " "));
    memory_info->SwapUsed = (memory_info->SwapTotal - memory_info->SwapFree);
    for (int i = 0; i < 10; i++)
        getline(&buffer, &size, file);
    value = strtok(buffer, " ");
    memory_info->buff_cache += atof(strtok(NULL, " "));
    free(buffer);
}

void convert_values(mem_struct_t *memory_info, int cycle)
{
    memory_info->MemTotal = memory_info->MemTotal / pow(1024, cycle);
    memory_info->MemFree = memory_info->MemFree / pow(1024, cycle);
    memory_info->MemUsed = memory_info->MemUsed / pow(1024, cycle);
    memory_info->avail_mem = memory_info->avail_mem / pow(1024, cycle);
    memory_info->SwapTotal = memory_info->SwapTotal / pow(1024, cycle);
    memory_info->SwapFree = memory_info->SwapFree / pow(1024, cycle);
    memory_info->SwapUsed = memory_info->SwapUsed / pow(1024, cycle);
    memory_info->buff_cache = memory_info->buff_cache / pow(1024, cycle);
}

mem_struct_t *my_getmemvalues(int cycle)
{
    FILE *file = 0;
    size_t size = 0;
    mem_struct_t *memory_info = malloc(sizeof(mem_struct_t) * 1);

    file = open_file("/proc/meminfo");
    if (file == NULL || memory_info == NULL)
        return (NULL);
    fill_mem_part(memory_info, file);
    fill_swap_part(memory_info, file);
    convert_values(memory_info, cycle);
    fclose(file);
    return (memory_info);
}
