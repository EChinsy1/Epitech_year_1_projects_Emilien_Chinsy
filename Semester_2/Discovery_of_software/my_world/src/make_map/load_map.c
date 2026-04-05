/*
** EPITECH PROJECT, 2026
** myworld
** File description:
** buttons
*/

#include <SFML/Graphics/RenderWindow.h>
#include <SFML/Graphics/Types.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <stdlib.h>
#include "buttons.h"
#include "macros.h"
#include "game.h"
#include "my_world.h"

static int get_y(char *buffer)
{
    int i = 0;

    while (buffer[i] != '\n')
        ++i;
    return (i);
}

static int *get_size_x_and_y(int *size, char *buffer)
{
    int i = 0;
    int counter = 0;
    int temp = 0;

    size[1] = get_y(buffer);
    while (buffer[i] != '\0') {
        ++counter;
        if (buffer[i] == '-')
            ++i;
        if (buffer[i] == '\n') {
            size[0] += 1;
            temp = counter - 1;
            counter = 0;
        }
        if (buffer[i] == '\n' && temp != size[1])
            return (NULL);
        ++i;
    }
    return (size);
}

static int error_handling(char *name)
{
    struct stat sb;

    if (name == NULL)
        return (-1);
    stat(name, &sb);
    if ((sb.st_mode & S_IFMT) != S_IFREG)
        return (-1);
    return (sb.st_size);
}

static int *apply(int *size, int *curr, char *buffer)
{
    int *new_map_i = calloc(sizeof(int), size[1] + 1);

    new_map_i[size[1]] = -1;
    for (int j = 0; j < size[1]; ++j) {
        if (buffer[*curr] == '-')
            ++(*curr);
        new_map_i[j] = (int)(buffer[*curr] - 48);
        if (*curr > 0 && buffer[*curr - 1] == '-')
            new_map_i[j] *= -1;
        ++(*curr);
    }
    ++(*curr);
    return (new_map_i);
}

static int remake_map(game_t *game, int *size, char *buffer, char *name)
{
    int **new_map = calloc(sizeof(int *), size[0] + 1);
    int curr = 0;

    free_after_loop(game->map_2d, game);
    for (int i = 0; i < size[0]; ++i) {
        free(game->map[i]);
        new_map[i] = apply(size, &curr, buffer);
    }
    free(game->map);
    game->map = new_map;
    game->size_x = size[0];
    game->size_y = size[1];
    game->old_size_x = size[0];
    game->old_size_y = size[1];
    game->freed = 1;
    free(name);
    free(size);
    free(buffer);
    return (0);
}

int load(sfRenderWindow *window, game_t *game)
{
    int fd = 0;
    char *name = get_user_input("please enter the name of your save file.");
    int size_of_file = 0;
    char *buffer = NULL;
    int *size = calloc(sizeof(int), 3);

    if (strstr(name, ".legend") == NULL)
        return (-1);
    size_of_file = error_handling(name);
    if (size_of_file == -1)
        return (0);
    buffer = calloc(sizeof(char), size_of_file);
    fd = open(name, (O_RDONLY), 00664);
    if (fd < 0)
        return (-1);
    read(fd, buffer, size_of_file - 1);
    size = get_size_x_and_y(size, buffer);
    if (size == NULL)
        return (-1);
    return (remake_map(game, size, buffer, name));
}
