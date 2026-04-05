/*
** EPITECH PROJECT, 2026
** stumper
** File description:
** stumper
*/

#include <stdlib.h>
#include <unistd.h>
#include "my.h"

void *my_calloc(int size, int len)
{
    void *pointer = malloc(size * len);
    int i = 0;

    if (pointer) {
        for (i = 0; i < (len * size); ++i) {
            ((char *)pointer)[i] = 0;
        }
    }
    return (pointer);
}

static int my_strlen(char *str)
{
    int i = 0;

    while (str[i] != '\0')
        ++i;
    return (i);
}

int my_putchar(char c)
{
    write(1, &c, 1);
    return (0);
}

int my_putstr(char *str)
{
    int i = 0;

    while (str[i] != '\0') {
        if (str[i] != ' ')
            my_putchar(str[i]);
        ++i;
    }
    return (0);
}

int main(int argc, char **argv)
{
    char **word_array = NULL;
    int len_of_array = 0;

    if (argc > 2)
        return (ERROR);
    if (argc == 1) {
        return (SUCCESS);
    }
    word_array = my_str_to_word_array(argv[1]);
    len_of_array = get_num_of_words(argv[1]);
    word_array = sort_word_array(word_array, len_of_array);
    for (int i = len_of_array - 1; i > -1; --i) {
        my_putstr(word_array[i]);
        if (i != 0 && my_strlen(word_array[i]) >= 1)
            my_putchar(' ');
    }
    my_putchar('\n');
    free_word_array(word_array);
    return (SUCCESS);
}
