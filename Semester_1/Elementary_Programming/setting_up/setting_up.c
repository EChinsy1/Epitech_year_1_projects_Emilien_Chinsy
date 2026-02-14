/*
** EPITECH PROJECT, 2025
** main
** File description:
** main
*/

#include "my.h"

static int show_then_free(char **map, int size, int len)
{
    for (int i = 0; i < size; ++i){
        if (write(1, map[i], len) != len)
            return (84);
        write(1, "\n", 1);
    }
    for (int i = 0; i < size; ++i){
        free(map[i]);
    }
    free(map);
    return (0);
}

int setting_up(int argc, char **argv)
{
    char **map;
    int num_lines = 0;
    int num_col = 0;

    if (argc < 2 || argc > 3)
        return (84);
    if (argc == 2) {
        num_lines = is_file_valid(argv[1]);
        if (num_lines == 0)
            return (84);
        map = load_file_in_mem(argv[1], num_lines, &num_col);
    }
    if (argc == 3){
        num_lines = is_three_arg_valid(argv[1], argv[2], &num_col);
        if (num_lines == 0 && argv[1][0] != '0')
            return (84);
        map = create_map_from_args(num_lines, argv[2]);
    }
    return (show_then_free(map, num_lines, num_col));
}
