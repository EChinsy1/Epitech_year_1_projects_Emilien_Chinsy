/*
** EPITECH PROJECT, 2025
** file validation
** File description:
** a file that will hold the function to validate the patterns
*/

#include "my.h"
#include <stdio.h>

int is_three_arg_valid(char const *num, char const *pattern, int *num_lines)
{
    int i = 0;
    int final_num = 0;

    if (num[0] == '-')
        return (0);
    final_num = my_getnbr(num);
    if (final_num == 0)
        return (0);
    if (my_strcmp(pattern, "") == 0)
        return (0);
    while (pattern[i] != '\0') {
        if (pattern[i] != '.' && pattern[i] != 'o')
            return (0);
        ++i;
    }
    *num_lines = final_num;
    return (final_num);
}

int validate_first_number(char const *file_path)
{
    char buff[20];
    int fd = open(file_path, O_RDONLY);
    ssize_t bytes_read;
    int i = 0;
    int num = 0;

    if (fd < 0)
        return (84);
    bytes_read = read(fd, buff, 20);
    if (bytes_read < 0){
        close(fd);
        return (84);
    }
    num = my_getnbr(buff);
    close(fd);
    return (num);
}

int is_file_valid(char const *file_path)
{
    struct stat sb;
    int num = 0;

    stat(file_path, &sb);
    if ((sb.st_mode & S_IFMT) != S_IFREG)
        return (0);
    num = validate_first_number(file_path);
    if (num == 0)
        return (0);
    return (num);
}
