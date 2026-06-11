/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** Main header file for corewar
*/

#ifndef MY_H_
    #define MY_H_

    #include <sys/types.h>
    #include "corewar.h"

//lib:
void my_putchar(char c);
char *my_revstr(char *str);
char *my_strncat(char *dest, char const *src, int nb);
char *my_strcat(char *dest, char const *src);
void my_putstr(char *str);
void my_puterr(char *str);
int my_dprintf(int fd, char const *str, ...);
int my_put_nbr(int nb);
char **my_str_to_word_array(char *str, char *delim);
int my_strcmp(char const *s1, char const *s2);
char *my_strstr(char *str, char const *to_find);
int my_getnbr(char const *str);
int my_strlen(const char *str);
char *my_strdup(char const *src);
void *my_calloc(size_t length, size_t size);
void *my_recalloc(void *ptr, size_t length, size_t size);
int my_strncmp(char const *s1, char const *s2, int n);
int my_strtoi(char const *str, char **endptr);
void my_str_free(int count, ...);
void my_array_free(int count, ...);
int gameplay(champs_t **champs, unsigned char *virt_machine, args_t *args);
void dump(champs_t **champs, unsigned char *vm, int cycles);

typedef struct is_index {
    char *name;
    char is_index;
} is_in_t;

//is_index
static const is_in_t is_index[] = {
    {"none", 0},
    {"live", 0},
    {"ld", 0},
    {"st", 0},
    {"add", 0},
    {"sub", 0},
    {"and", 0},
    {"or", 0},
    {"xor", 0},
    {"zjmp", 1},
    {"ldi", 1},
    {"sti", 1},
    {"fork", 1},
    {"lld", 0},
    {"lldi", 1},
    {"lfork", 1},
    {"print", 0},
    {0, -1}
};
#endif
