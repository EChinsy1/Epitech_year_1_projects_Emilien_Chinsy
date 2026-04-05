/*
** EPITECH PROJECT, 2026
** my_top
** File description:
** subfile for my_top
*/

#include <stdlib.h>
#include <string.h>
#include "my_top.h"
#include "process_struct.h"
#include "uid_and_user_struct.h"

int my_str_isnum(char const *str)
{
    int i = 0;

    while (str[i] != '\0'){
        if (str[i] <= 57 && str[i] >= 48){
            i++;
        } else {
            return (0);
        }
    }
    return (1);
}

void free_procs(procs_t *procs)
{
    procs_t *current = procs;
    procs_t *next = NULL;

    if (current == NULL)
        return;
    while (current) {
        next = current->next;
        free(current->name);
        free(current->user);
        free(current);
        current = next;
    }
}

static void free_users(uid_n_user_t *users)
{
    uid_n_user_t *current = users;
    uid_n_user_t *next = NULL;

    while (current){
        next = current->next;
        free(current->user);
        free(current);
        current = next;
    }
}

static int get_delay(char **av)
{
    int index = 0;

    while (av[index] != NULL){
        if (strcmp(av[index], "-d") == 0 && av[index + 1] != NULL)
            return (int)(10 * atof(av[index + 1]));
        index++;
    }
    return 30;
}

static int get_max_frames(char **av)
{
    int index = 0;

    while (av[index] != NULL){
        if (strcmp(av[index], "-n") == 0 && av[index + 1] != NULL)
            return atoi(av[index + 1]);
        index++;
    }
    return -1;
}

static char *get_user(char **av)
{
    int index = 0;

    while (av[index] != NULL){
        if (strcmp(av[index], "-U") == 0 && av[index + 1] != NULL)
            return av[index + 1];
        index++;
    }
    return NULL;
}

int my_top(int ac, char **av)
{
    uid_n_user_t *users = get_all_users();
    int delay = get_delay(av);
    int max_frames = get_max_frames(av);
    char *user_sort = get_user(av);
    cpu_stats_t *stats = malloc(sizeof(cpu_stats_t));

    init_stats(stats);
    init_screen(delay);
    screen_loop(max_frames, users, user_sort, stats);
    terminate_screen();
    free_users(users);
    free(stats);
    return 0;
}
