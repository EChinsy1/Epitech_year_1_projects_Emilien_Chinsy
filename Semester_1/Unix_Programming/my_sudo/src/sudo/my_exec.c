/*
** EPITECH PROJECT, 2025
** my_exec
** File description:
** help
** printf("%d\n", get_group_id("tutu"));
** printf("%d\n", get_user_id("tutu"));
*/

#include <errno.h>
#include <grp.h>
#include "my.h"
#include "macros.h"

void free_list(list_t *list)
{
    list_t *current = list;
    list_t *next = NULL;

    if (current == NULL)
        return;
    while (current) {
        next = current->next;
        free(current->item);
        free(current->gid);
        free(current->item_space);
        free(current->gid_space);
        free(current);
        current = next;
    }
}

static int size_of_fnf_t(fnf_t **list)
{
    int size = 0;

    if (list == NULL)
        return (-1);
    while (list[size]) {
        ++size;
    }
    return (size);
}

int print_help(int argc)
{
    printf("usage: ./my_sudo -h\n");
    printf("usage: ./my_sudo [-ug] [command [args ...]]\n");
    if (argc != 2)
        return (EXIT_ERROR);
    else
        return (SUCCESS);
}

void free_flags(fnf_t **flags)
{
    int i = 0;

    if (flags == NULL)
        return;
    while (i < 2) {
        free(flags[i]);
        ++i;
    }
    free(flags);
}

int my_exec(char *arg0, char **args, user_t *user)
{
    int exec_result = 0;

    free(user->name);
    free(user->uid);
    free_list(user->groups);
    if (args[0] == NULL) {
        exit(print_help(84));
    }
    exec_result = execvp(arg0, args);
    if (exec_result == -1)
        fprintf(stderr, "my_sudo: %s: command not found\n", arg0);
    return (exec_result);
}

static int print_error_message(int is_in_sudoers,
    int passwd_check, int exec_result)
{
    if (passwd_check != SUCCESS)
        fprintf(stderr, "my_sudo: 3 incorrect password attempts\n");
    if (exec_result == INVALID_ARGS) {
        fprintf(stderr, "invalid args\n");
        return (print_help(EXIT_ERROR));
    }
    return (EXIT_ERROR);
}

static void check_validity(user_t *user, int *in_sudoers, int *passwd_check)
{
    if (strcmp(user->name, "root") != 0) {
        user->groups = get_all_groups(user->name);
        *in_sudoers = check_groups(user, user->name);
        *passwd_check = check_password(user->name, 1, user);
    } else {
        *in_sudoers = 1;
        user->groups = get_all_groups(user->name);
    }
    if (*in_sudoers < 1 && *passwd_check == SUCCESS)
        fprintf(stderr, "%s is not in the sudoers file.\n", user->name);
}

static void set_to_root(void)
{
    setregid(0, 0);
    setreuid(0, 0);
    setgroups(0, NULL);
}

static int apply_from_flags(int argc, char **argv, fnf_t **flags, user_t *user)
{
    int i = 0;
    int j = 1;
    int size = size_of_fnf_t(flags);
    int to_check = 0;

    if (flags == NULL) {
        set_to_root();
    } else {
        while (flags[i]) {
            to_check = flags[i]->fptr(flags[i]->arg, size);
            j = j + 2;
            ++i;
        }
        if (to_check == ERROR)
            return (to_check);
        setreuid(getuid(), getuid());
    }
    free_flags(flags);
    return (my_exec(argv[j], &argv[j], user));
}

int main(int argc, char **argv)
{
    user_t user;
    int in_sudoers = 0;
    int return_value = 0;
    int passwd_check = 0;
    int exec_result = 0;
    fnf_t **flags = NULL;

    if (argc < 2 || (argc == 2 && strcmp(argv[1], "-h") == 0))
        return (print_help(argc));
    flags = parse(argc, argv);
    user.name = get_id(&user);
    if (user.name == NULL)
        return (EXIT_ERROR);
    check_validity(&user, &in_sudoers, &passwd_check);
    if (passwd_check == SUCCESS && in_sudoers > 0)
        exec_result = apply_from_flags(argc, argv, flags, &user);
    return (print_error_message(in_sudoers, passwd_check, exec_result));
}
