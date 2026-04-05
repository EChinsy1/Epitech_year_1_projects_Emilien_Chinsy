/*
** EPITECH PROJECT, 2026
** my_top
** File description:
** header file containing the mem_struct typedef
*/

#ifndef MEM_STRUCT_H
    #define MEM_STRUCT_H

typedef struct mem_struct {
    double MemTotal;
    double MemFree;
    double MemUsed;
    double buff_cache;
    double SwapTotal;
    double SwapFree;
    double SwapUsed;
    double avail_mem;
} mem_struct_t;

#endif
