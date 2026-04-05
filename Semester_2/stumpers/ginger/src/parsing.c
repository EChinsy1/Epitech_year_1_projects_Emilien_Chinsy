/*
** EPITECH PROJECT, 2026
** parsing.c
** File description:
** parsing for duo stumper 2
*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

static int is_int(char const *str)
{
    for (int i = 0; str[i] != '\0'; i++){
        if (str[i] < '0' || str[i] > '9')
            return 84;
    }
    return 0;
}

static int get_map_size(unsigned char const *str)
{
    int size_x = 0;
    int size_y = 0;
    int temp = 0;
    int i = 0;

    for (; str[i] != '\n'; i++);
    size_x = i;
    for (int i = 0; str[i] != '\0'; i++){
        if (str[i] == '\n' && size_x == temp){
            temp = 0;
            continue;
        }
        if (str[i] == '\n' && size_x != temp)
            return 84;
        if (str[i] != '\n')
            temp += 1;
    }
    return 0;
}

static unsigned char *open_map(char const *str)
{
    FILE *fd = fopen(str, "r");
    size_t len;
    struct stat sb;
    unsigned char *buf = NULL;

    stat(str, &sb);
    if (fd == NULL)
        return NULL;
    buf = calloc(sizeof(char), sb.st_size + 1);
    if (buf == NULL)
        return (NULL);
    len = fread(buf, sizeof(*buf), sb.st_size, fd);
    if (len == 0 || get_map_size(buf) == 84){
        fclose(fd);
        return NULL;
    }
    fclose(fd);
    return buf;
}

unsigned char *parsing(char **array)
{
    int idx_map = 0;
    int idx_moov = 0;
    unsigned char *map = NULL;

    for (int i = 0; array[i] != NULL; i++){
        if (array[i][0] == '-' && (array[i][1] != 'f' && array[i][1] != 'm'))
            return NULL;
        if (array[i][0] == '-' && array[i][1] == 'f'){
            idx_map = i + 1;
        }
        if (array[i][0] == '-' && array[i][1] == 'm'){
            idx_moov = i + 1;
        }
    }
    if (is_int(array[idx_moov]) == 84)
        return NULL;
    map = open_map(array[idx_map]);
    return map;
}
