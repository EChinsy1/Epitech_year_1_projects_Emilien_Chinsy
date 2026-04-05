/*
** EPITECH PROJECT, 2026
** amazed
** File description:
** file containing a function to free int arrays
*/

#include <stdlib.h>

void free_int_array(int **array)
{
    int index = 0;

    if (!array)
        return;
    while (array[index] != NULL){
        free(array[index]);
        index++;
    }
    free(array);
}
