/*
** EPITECH PROJECT, 2026
** struct_cpu
** File description:
** file for my_top containing the cpu stats
** us = USage
** sy = SYstem
** ni = NIce
** id = ISle
** wa = ioWAit
** hi = Hardware Interrupt
** si = Software Interrupt
** st = STeal
*/

#ifndef STRUCT_CPU_H
    #define STRUCT_CPU_H

typedef struct cpu_stats {
    double us;
    double sy;
    double ni;
    double id;
    double wa;
    double hi;
    double si;
    double st;
    double total;
    double d_us;
    double d_sy;
    double d_ni;
    double d_id;
    double d_wa;
    double d_hi;
    double d_si;
    double d_st;
    double d_total;
} cpu_stats_t;

#endif
