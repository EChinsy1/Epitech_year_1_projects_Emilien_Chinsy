/*
** EPITECH PROJECT, 2025
** File systems
** File description:
** setting up bootstrap first part
*/

#include "my.h"
#include <stdio.h>

int fs_open_file(char const *filepath)
{
    int fd;

    fd = open(filepath, O_RDONLY);
    if (fd < 0){
        exit(84);
    }
    return (fd);
}

static ssize_t error_handling(int fd, char *buff, int size)
{
    ssize_t bytes_read;

    if (fd < 0)
        exit(84);
    bytes_read = read(fd, buff, size);
    if (bytes_read < 0)
        exit(84);
    return (bytes_read);
}

static int free_when_error(char **arr, char *buff, int size, int fd)
{
    free(buff);
    for (int i = 0; i < size; ++i)
        free(arr[i]);
    free(arr);
    close(fd);
    return (84);
}

static ssize_t error_and_file_checker(int fd, char *buff, int size)
{
    ssize_t bytes_read = error_handling(fd, buff, size);

    for (int i = 0; i < size; ++i){
        if (buff[i] != '\n' && buff[i] != 'o' && buff[i] != '.'){
            return (-1);
        }
    }
    return (bytes_read);
}

static int find_nb_rows(char const *filepath)
{
    int i = 0;
    char buff[100];
    int fd = fs_open_file(filepath);
    ssize_t bytes_read;
    int nb_rows = 0;

    bytes_read = error_handling(fd, buff, 100);
    while (buff[i] != '\n')
        ++i;
    ++i;
    while (buff[i] != '\n'){
        ++nb_rows;
        ++i;
        if ((i % 100) == 0){
            bytes_read = error_handling(fd, buff, 100);
            i = 0;
        }
    }
    close(fd);
    return (nb_rows + 1);
}

char **load_file_in_mem(char const *filepath, int size, int *nb_rows)
{
    char **arr;

    (*nb_rows) = find_nb_rows(filepath);
    arr = load_2d_arr_from_file(filepath, *nb_rows, size, arr);
    search_and_replace(arr, *nb_rows, size);
    *nb_rows = *nb_rows - 1;
    return (arr);
}

static int update_pattern(int pattern_place, int len)
{
    if (pattern_place < (len - 1)) {
        return (pattern_place + 1);
    }
    return (0);
}

static ssize_t skip_first_num(int fd)
{
    ssize_t bytes_read;
    char buffer[1];

    bytes_read = error_handling(fd, buffer, 1);
    while (buffer[0] != '\n'){
        bytes_read = error_handling(fd, buffer, 1);
    }
    return (bytes_read);
}

char **load_2d_arr_from_file(char const *filepath,
    int const nb_rows,
    int const nb_cols,
    char **arr)
{
    int fd = fs_open_file(filepath);
    char *buff;
    ssize_t bytes_read = skip_first_num(fd);

    arr = my_calloc(sizeof(char *), (nb_cols + 1));
    for (int i = 0; i < nb_cols; ++i){
        buff = my_calloc(sizeof(char), (nb_rows + 1));
        bytes_read = error_and_file_checker(fd, buff, nb_rows);
        if (bytes_read == -1)
            exit(free_when_error(arr, buff, i, fd));
        if (buff[nb_rows - 1] != '\n')
            exit(84);
        arr[i] = my_calloc(sizeof(char), (nb_rows + 3));
        my_strncat(arr[i], buff, nb_rows - 1);
        free(buff);
    }
    arr[nb_cols] = NULL;
    close(fd);
    return (arr);
}

char **create_map_from_args(int size, char *pattern)
{
    char **map;
    int pattern_place = 0;

    map = my_calloc(sizeof(char *), (size + 1));
    for (int y = 0; y < size; ++y){
        map[y] = my_calloc(sizeof(char), (size + 1));
        for (int x = 0; x < size; ++x){
            map[y][x] = pattern[pattern_place];
            pattern_place = update_pattern(pattern_place, my_strlen(pattern));
        }
        map[y][size] = '\0';
    }
    map[size] = NULL;
    search_and_replace(map, size + 1, size);
    return (map);
}
