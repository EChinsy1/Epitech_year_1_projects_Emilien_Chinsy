/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** scripting
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "arguments.h"
#include "scripting.h"
#include "my.h"

int exec(char *buffer, args_t *args)
{
    size_t s = 0;

    args->buffer = buffer;
    if (check_alias(&(args->buffer), args->alias, &s) == ERROR)
        return (0);
    exexcution(args);
    return (0);
}

int not_impelemented(char *buffer, args_t *args, FILE *file)
{
    printf("pas fait\n");
    return (1);
}

static int is_not_script(char *buffer, FILE *file, args_t *args)
{
    for (int i = 0; keywords[i].keyword; ++i) {
        if (strncmp(buffer, keywords[i].keyword,
                strlen(keywords[i].keyword)) == 0)
            return (keywords[i].fptr(buffer, args, file));
    }
    return (0);
}

static char *remove_backslash_r(char *buffer)
{
    if (buffer[strlen(buffer) - 2] == '\r')
        buffer[strlen(buffer) - 2] = '\0';
    if (buffer[strlen(buffer) - 2] == '\n')
        buffer[strlen(buffer) - 2] = '\0';
    if (buffer[strlen(buffer) - 1] == '\n')
        buffer[strlen(buffer) - 1] = '\0';
    return (buffer);
}

int do_each_line(FILE *file, args_t *args)
{
    char *buffer = NULL;
    size_t size = 0;
    size_t s = 0;

    while (getline(&buffer, &size, file) > 0) {
        buffer = remove_backslash_r(buffer);
        if (buffer[0] == '\n' || buffer[0] == '#' || strcmp(buffer, "end") == 0)
            continue;
        if (is_not_script(buffer, file, args) != 1)
            exec(buffer, args);
    }
    fclose(file);
    free(buffer);
    return (args->last_command_return);
}

int scripting(char *file_name, int argc, char **argv, char **env)
{
    args_t args = create_args(argc, argv, env);
    FILE *file = fopen(file_name, "r");
    int return_value = 0;

    if (file == NULL) {
        dprintf(2, "%s: No such file or directory.\n", file_name);
        return (84);
    }
    return_value = do_each_line(file, &args);
    free(args.old_dir);
    free_list(args.history);
    free_word_array(args.env);
    free_word_array(args.local);
    free(args.home_dir);
    return (return_value);
}
