/*
** EPITECH PROJECT, 2026
** my_h_
** File description:
** my_h_
*/

#ifndef MY_H_
    #define MY_H_

    #include "struct.h"
int tree(char *name, int depth, char **arg_array, nb_t *num_of_values);
int pre_tree(char **arg_array, char **dest_array);
char **get_all_values(char *name, int depth);
void free_value_array(char **value_array);
char **sort(char **value_array);
char *my_fake_calloc(int size, int size_2);
char **my_big_calloc(int size, int size_2);

#endif
