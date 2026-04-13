/*
** EPITECH PROJECT, 2025
** struct.h
** File description:
** the structure for the function pointers
*/

#ifndef STRUCTS_
    #define STRUCTS_

typedef struct function_holder {
    char flag;
    char *(*fptr)(va_list args, char **other_args, char *buffer);
} func_holder_t;

const struct function_holder EACH_FUNCTION[] = {
    {'d', &my_pivot_add_nbr},
    {'i', &my_pivot_add_nbr},
    {'s', &my_pivot_addstr},
    {'c', &my_pivot_addchar},
    {'%', &my_add_percent},
    {'f', &my_pivot_add_float},
    {'F', &my_pivot_add_float},
    {'e', &my_pivot_add_scientific},
    {'E', &my_pivot_add_scientific_maj},
    {'u', &my_pivot_add_nbr_u},
    {'o', &my_pivot_add_nbr_o},
    {'X', &my_pivot_add_nbr_x_maj},
    {'x', &my_pivot_add_nbr_x},
    {'g', &my_pivot_add_g},
    {'G', &my_pivot_add_g_maj},
    {'a', &my_pivot_add_nbr_a},
    {'A', &my_pivot_add_nbr_a_maj},
    {'p', &my_pivot_add_ptr_address}};

#endif
