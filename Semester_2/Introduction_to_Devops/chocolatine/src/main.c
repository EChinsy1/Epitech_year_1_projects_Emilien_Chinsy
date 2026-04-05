/*
** EPITECH PROJECT, 2026
** pcube
** File description:
** matchsticks
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "my.h"

static void final_printer(int matches, int line, int who)
{
    int coding_style_breakeraaaaaaaaaaaaaa = 0;
    if (who == 0)
        write(1, "Player removed ", 15);
    else
        write(1, "AI removed ", 11);
    my_put_nbr(matches);
    write(1, " Match(es) from line ", 21);
    my_put_nbr(line);
    write(1, "\n", 1);
    write(1, "\n", 1);
}

int *draw_start(int num_lines, int lines[])
{
    for (int i = 0; i < (num_lines + 1) * 2 - 1; ++i)
        write(1, "*", 1);
    write(1, "\n", 1);
    for (int i = 0; i < num_lines; ++i) {
        write(1, "*", 1);
        for (int x = 0; x < num_lines - i - 1; ++x)
            write(1, " ", 1);
        for (int j = 0; j < lines[i]; ++j)
            write(1, "|", 1);
        for (int y = 0; y < (num_lines * 2 - lines[i] - (num_lines - i)); ++y)
            write(1, " ", 1);
        write(1, "*\n", 2);
    }
    for (int i = 0; i < (num_lines + 1) * 2 - 1; ++i)
        write(1, "*", 1);
    write(1, "\n", 1);
    return (0);
}

static int get_target(int **lines, int num_lines)
{
    size_t size;
    char *buffer = NULL;
    int num = 0;

    getline(&buffer, &size, stdin);
    while (is_num(buffer) == 0 || buffer[0] == '0' ||
        my_getnbr(buffer) > num_lines || buffer[0] == '\n' ||
        (*lines)[my_getnbr(buffer) - 1] == 0) {
        if (buffer[my_strlen(buffer) - 1] != '\n')
            return (-1);
        if (is_num(buffer) == 0)
            write(1, "Error: invalid input (positive number expected)\n", 48);
        else
            write(1, "Error: this line is out of range\n", 33);
        write(1, "Line: ", 6);
        getline(&buffer, &size, stdin);
    }
    num = my_getnbr(buffer);
    free(buffer);
    return (num);
}

static void print_match_errors(char *buffer,
    int **lines, int target, int max_remove)
{
    if (buffer[0] == '0') {
        write(1, "Error: you have to remove at least one match\n", 45);
        return;
    }
    if (is_num(buffer) == 0 || buffer[0] == '\n') {
        write(1, "Error: invalid input (positive number expected)\n", 48);
        return;
    }
    if (my_getnbr(buffer) > max_remove) {
        write(1, "Error: you cannot remove more than ", 35);
        my_put_nbr(max_remove);
        write(1, " matches per turn\n", 18);
        return;
    }
    if ((*lines)[target - 1] < my_getnbr(buffer)) {
        write(1, "Error: not enough matches on this line\n", 39);
        return;
    }
}

static int get_matches(int **lines, int max_remove, int target)
{
    size_t size;
    char *buffer = NULL;
    int num = 0;

    write(1, "Matches: ", 9);
    getline(&buffer, &size, stdin);
    while (is_num(buffer) == 0 || buffer[0] == '0'
        || my_getnbr(buffer) > max_remove ||
        (*lines)[target - 1] < my_getnbr(buffer) || buffer[0] == '\n') {
        if (buffer[my_strlen(buffer) - 1] != '\n')
            return (-1);
        print_match_errors(buffer, lines, target, max_remove);
        write(1, "Matches: ", 9);
        getline(&buffer, &size, stdin);
    }
    num = my_getnbr(buffer);
    free(buffer);
    return (num);
}

static int input_user(int **lines, int num_lines, int max_remove, int *total)
{
    int target = 0;
    int matches = 0;

    write(1, "Your turn:\n", 11);
    write(1, "Line: ", 6);
    target = get_target(lines, num_lines);
    if (target == -1)
        return (target);
    matches = get_matches(lines, max_remove, target);
    if (matches == -1)
        return (matches);
    (*lines)[target - 1] -= matches;
    *total -= matches;
    final_printer(matches, target, 0);
    return (0);
}

static void ai_input(int **lines, int num_lines, int max_remove, int *total)
{
    unsigned int target = (random() % num_lines) + 1;
    unsigned int matches = 0;
    int i = 0;

    write(1, "AI's turn:\n", 11);
    if ((*lines)[target - 1] <= 0) {
        while ((*lines)[i] == 0)
            ++i;
        target = i + 1;
    }
    if (max_remove < (*lines)[target - 1])
        matches = (random() % max_remove) + 1;
    else
        matches = (random() % ((*lines)[target - 1])) + 1;
    (*lines)[target - 1] -= matches;
    *total -= matches;
    final_printer(matches, target, 1);
    draw_start(num_lines, *lines);
}

static int write_free_n_return(int step, int *lines)
{
    if (step == 2) {
        free(lines);
        return (0);
    } else if (step == 0) {
        write(1, "You lost, too bad...\n", 21);
        free(lines);
        return (2);
    } else {
        write(1, "I lost... snif... but I'll get you next time!!\n", 47);
        free(lines);
        return (1);
    }
}

int matchsticks(char **argv, int total)
{
    int num_lines = my_getnbr(argv[1]);
    int max_remove = my_getnbr(argv[2]);
    int *lines = calloc(sizeof(int), num_lines + 1);

    for (int i = 0; i < num_lines; ++i) {
        total += i * 2 + 1;
        lines[i] = i * 2 + 1;
    }
    draw_start(num_lines, lines);
    while (total > 0) {
        if (input_user(&lines, num_lines, max_remove, &total) == -1)
            return (write_free_n_return(2, lines));
        draw_start(num_lines, lines);
        if (total <= 0)
            return (write_free_n_return(0, lines));
        ai_input(&lines, num_lines, max_remove, &total);
        if (total <= 0)
            return (write_free_n_return(1, lines));
    }
    return (0);
}

int main(int argc, char **argv)
{
    int total = 0;

    if (argc != 3)
        return (84);
    for (int i = 1; i < argc; ++i) {
        if (is_num(argv[i]) == 0 || argv[i][0] == '0')
            return (84);
    }
    srand(time(NULL));
    return (matchsticks(argv, total));
}
