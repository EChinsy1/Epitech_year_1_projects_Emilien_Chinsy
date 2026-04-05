/*
** EPITECH PROJECT, 2026
** my_top
** File description:
** file containing functions to cycle through unit measurements
*/

#include "process_struct.h"
#include "display_info.h"

void cycle_proc_units(procs_t *procs, display_info_t *display_info)
{
    display_info->proc_unit = (display_info->proc_unit + 1) % 5;
}

void cycle_sys_units(procs_t *procs, display_info_t *display_info)
{
    display_info->sys_unit = (display_info->sys_unit + 1) % 6;
}
