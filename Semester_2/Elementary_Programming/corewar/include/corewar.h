/*
** EPITECH PROJECT, 2026
** corewar
** File description:
** Main header file for corewar
*/

#ifndef COREWAR_H
    #define COREWAR_H

    #define FAILURE 84
    #define SUCCESS 0
    #define TRUE 1
    #define FALSE 0
    #define FAIL -1
    #define FLAG_FAIL -2
    #define REG_BYTE 1
    #define DIR_BYTE 2
    #define IND_BYTE 3
    #define ELS_BYTE 0
    #define UNUSED __attribute__((unused))
    #define EROPEN "%s: Couldn't open.\n"

    #include "op.h"
    #include <stdio.h>

// Command line parsing
typedef struct files_s {
    int prog_nb;
    int load_address;
    char *prog_name;
} files_t;

typedef struct args_s {
    int nb_flags;
    int nb_files;
    int nbr_cycle;
    files_t *files;
    char *virt_machine;
} args_t;

typedef struct flags_s {
    char *flag;
    void (*fct)(char **, args_t *, int);
} flags_t;

// Champions
typedef struct champions {
    char *name;
    char *comment;
    unsigned int prog_size;
    int player_id;
    int registers[REG_NUMBER];
    unsigned int PC;
    int carry;
    int alive;
    int wait;
} champs_t;

static const char *const no_coding_byte[] = {
    "live",
    "zjmp",
    "fork",
    "lfork",
    NULL,
};

typedef struct no_coding_byte_size {
    char *name;
    int index;
    int size;
} no_coding_byte_size_t;

static const no_coding_byte_size_t coding_byte_size[] = {
    {"live", 1, 128},
    {"zjmp", 9, 192},
    {"fork", 12, 192},
    {"lfork", 15, 192},
    {NULL, 0, 0}
};

typedef struct command_fptr {
    int command_num;
    int (*fptr)(champs_t ***, int, char *, char *, char *virt_machine);
} cmd_fptr_t;

// Functions
args_t arguments(char **av);
champs_t **get_champions(args_t *args, unsigned char **virt_machine);
int corewar(int ac, char **av);
void my_put_nbr_base_x(int nb);
void get_instr_args(int *idx[2], int command,
    unsigned char **vm, champs_t ***champs);

// Corewar Instructions
int ld_func(champs_t ***champ, int index,
    int **arg_and_types, unsigned char **virt_machine);
int ldi_func(champs_t ***champ, int champ_index,
    int **arg_and_types, unsigned char **virt_machine);
int live_func(champs_t ***champ, int champ_index,
    int **arg_and_types, unsigned char **virt_machine);
int st_func(champs_t ***champ, int champ_index,
    int **arg_and_types, unsigned char **virt_machine);
int add_func(champs_t ***champ, int champ_index,
    int **arg_and_types, unsigned char **virt_machine);
int sub_func(champs_t ***champ, int champ_index,
    int **arg_and_types, unsigned char **virt_machine);
int and_func(champs_t ***champ, int champ_index,
    int **arg_and_types, unsigned char **virt_machine);
int or_func(champs_t ***champ, int champ_index,
    int **arg_and_types, unsigned char **virt_machine);
int xor_func(champs_t ***champ, int champ_index,
    int **arg_and_types, unsigned char **virt_machine);
int zjmp_func(champs_t ***champ, int champ_index,
    int **arg_and_types, unsigned char **virt_machine);
int fork_func(champs_t ***champ, int champ_index,
    int **arg_and_types, unsigned char **virt_machine);
int sti_func(champs_t ***champ, int champ_index,
    int **arg_and_types, unsigned char **virt_machine);
int lld_func(champs_t ***champ, int champ_index,
    int **arg_and_types, unsigned char **virt_machine);
int lldi_func(champs_t ***champ, int champ_index,
    int **arg_and_types, unsigned char **virt_machine);
int print_func(champs_t ***champ, int champ_index,
    int **arg_and_types, unsigned char **virt_machine);
int lfork_func(champs_t ***champ, int champ_index,
    int **arg_and_types, unsigned char **virt_machine);

typedef struct command_n_func {
    char *name;
    int (*fptr)(champs_t ***, int, int **, unsigned char **);
} cmd_n_func_t;

static const cmd_n_func_t cmd_fct[] = {
    {"none", NULL},
    {"live", &live_func},
    {"ld", &ld_func},
    {"st", &st_func},
    {"add", &add_func},
    {"sub", &sub_func},
    {"and", &and_func},
    {"or", &or_func},
    {"xor", &xor_func},
    {"zjmp", &zjmp_func},
    {"ldi", &ldi_func},
    {"sti", &sti_func},
    {"fork", &fork_func},
    {"lld", &lld_func},
    {"lldi", &lldi_func},
    {"lfork", &lfork_func},
    {"print", &print_func},
    {0, NULL}
};
#endif
