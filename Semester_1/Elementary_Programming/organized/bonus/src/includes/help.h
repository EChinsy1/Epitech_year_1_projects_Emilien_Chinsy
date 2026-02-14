/*
** EPITECH PROJECT, 2025
** help
** File description:
** help
*/

#ifndef HELP_H_
    #define HELP_H_

void print_help_add(void);
void print_help_sort(void);
void print_help_del(void);
void print_help_disp(void);
void print_help_empty(void);
void print_help_parse(void);
void print_help_stats(void);
void print_help_help(void);
void print_help_all(void);
void print_help_save(void);

typedef struct func_and_help {
    char *name;
    void (*fptr)(void);
} fnh_t;

static const struct func_and_help FUNC_AND_HELP[] = {
    {"add", &print_help_add},
    {"sort", &print_help_sort},
    {"del", &print_help_del},
    {"disp", &print_help_disp},
    {"empty", &print_help_empty},
    {"parse", &print_help_parse},
    {"stats", &print_help_stats},
    {"help", &print_help_help},
    {"save", &print_help_save},
    {"all", &print_help_all},
    {((void *)0), ((void *)0)}
};

#endif  
