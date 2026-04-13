/*
** EPITECH PROJECT, 2025
** robot factory
** File description:
** my_h_
*/

#ifndef MY_H_
    #define MY_H_

    #include <sys/types.h>
    #include <stdio.h>
    #include "struct.h"

char *my_strncat(char *dest, char const *src, int nb);
char *my_strcat(char *dest, char const *src);
void my_putstr(char *str);
char **my_str_to_word_array(char *str, char *delim);
int my_strcmp(char const *s1, char const *s2);
int my_getnbr(char const *str);
int my_strlen(const char *str);
char *my_strdup(char const *src);
void *my_calloc(size_t length, size_t size);
int my_strncmp(char const *s1, char const *s2, int n);
ins_t *parsing(char *file_name);
int is_all_digits(char *str);
int write_in_file(FILE *file, char *text, size_t size);
int write_cmd_cod_byte(char **array, FILE *file);
int write_reg(FILE *file, char *value);
int write_dir(FILE *file, char *value, char *cmd);
int write_ind(FILE *file, char *value);
int write_index(FILE *file, char *value, ins_t *instructions, int current);
int has_coding_byte(char *cmd);
void swap_endian(void *data, size_t size);
int find_pos_of_index(char *str);
char **get_word_array(char *buffer);
int is_index_func(char *cmd);
args_type_t which_type(char *str, int *size, int index, int stop);
char **remove_extra_spaces(char **word_array);
char **new_word_array(ins_t *instructions, char **word_array,
    int *pos_of_index, FILE *file);

//free funcs
void free_word_array(char **word_array);
ins_t *free_instructions(ins_t *instructions, FILE *file);
ins_t *free_and_return(ins_t *instructions, char *buffer, FILE *file);

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
