/*
** EPITECH PROJECT, 2026
** tree
** File description:
** tree
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include "lib.h"
#include "my.h"
#include "struct.h"

static int print_format(char **value_array, int depth, int i)
{
    if (value_array[i][0] == '.')
        return (0);
    write(1, "|", 1);
    if (value_array[i + 1] == NULL) {
        for (int i = 0; i < depth - 1; ++i) {
            my_putstr("  |");
        }
        if (depth > 0)
            my_putstr("  `");
    } else {
        for (int i = 0; i < depth - 1; ++i) {
            my_putstr("  |");
        }
        if (depth > 0)
            my_putstr("  |");
    }
    my_putstr("-- ");
    my_putstr(value_array[i]);
    my_putstr("\n");
    return (0);
}

static char *create_new_name(char *name, char *current_name)
{
    char *new_name = my_fake_calloc(sizeof(char),
        (my_strlen(current_name) + my_strlen(name) + 2));

    if (!new_name)
        return (NULL);
    new_name = my_strcat(name, new_name);
    new_name = my_strcat("/", new_name);
    new_name = my_strcat(current_name, new_name);
    return (new_name);
}

static char *free_new_name(char *new_name)
{
    free(new_name);
    return (NULL);
}

static int check_if_dir(char *name, char *orig_name,
    struct stat *sb, nb_t *num_of_values)
{
    if ((sb->st_mode & S_IFMT) == S_IFDIR
        && orig_name[0] != '.') {
        num_of_values->num_of_dir += 1;
        return (1);
    }
    if (orig_name[0] != '.')
        num_of_values->num_of_files += 1;
    return (0);
}

int tree(char *name, int depth, char **arg_array, nb_t *num_of_values)
{
    struct stat sb;
    char *new_name = NULL;
    char **value_array = get_all_values(name, depth);
    int i = 0;

    if (value_array == NULL)
        return (84);
    while (value_array[i]) {
        new_name = create_new_name(name, value_array[i]);
        stat(new_name, &sb);
        print_format(value_array, depth, i);
        if (check_if_dir(new_name, value_array[i], &sb, num_of_values))
            tree(new_name, depth + 1, arg_array, num_of_values);
        new_name = free_new_name(new_name);
        ++i;
    }
    free_value_array(value_array);
    return (0);
}

static void my_putchar(char c)
{
    write(1, &c, 1);
}

static void my_putnbr(int nbr)
{
    int temp_num = 0;

    if (nbr > 0) {
        temp_num = nbr % 10;
        my_putnbr(nbr / 10);
        my_putchar(temp_num + 48);
    }
}

static void end_write(nb_t *num_of_values)
{
    if (num_of_values->num_of_dir == 0)
        write(1, "0", 1);
    my_putnbr(num_of_values->num_of_dir);
    my_putstr(" directories, ");
    if (num_of_values->num_of_files == 0)
        write(1, "0", 1);
    my_putnbr(num_of_values->num_of_files);
    my_putstr(" files\n");
}

int pre_tree(char **arg_array, char **dest_array)
{
    int result = 0;
    nb_t num_of_values;

    num_of_values.num_of_dir = 0;
    num_of_values.num_of_files = 0;
    for (int i = 0; dest_array[i] != NULL; ++i) {
        num_of_values.num_of_dir++;
        result = tree(dest_array[i], 0, arg_array, &num_of_values);
        if (result == 84) {
            num_of_values.num_of_dir--;
            my_putstr(dest_array[i]);
            my_putstr("  [error opening dir]\n");
        }
        my_putchar('\n');
    }
    end_write(&num_of_values);
    free_value_array(arg_array);
    free_value_array(dest_array);
    return (0);
}
