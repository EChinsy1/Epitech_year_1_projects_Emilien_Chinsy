/*
** EPITECH PROJECT, 2025
** my_exec
** File description:
** help
*/

#include "my.h"
#include <errno.h>

static void my_putstr(char *str)
{
    int i = 0;

    i = 0;
    while (str[i] != '\0') {
        write(1, &str[i], 1);
        i++;
    }
}

static char *get_only_good_part(char *name)
{
    int i = 3;
    int j = 0;
    char *buffer = NULL;

    while (name[j] != ':')
        ++j;
    ++j;
    while (name[i + j] != ':'){
        ++i;
    }
    buffer = calloc(sizeof(char), (i + 2));
    if (buffer == NULL)
        return (NULL);
    strncat(buffer, &name[j], i);
    return (buffer);
}

char *get_real_password(char *name)
{
    FILE *stream = NULL;
    char *line = NULL;
    char *return_string = NULL;
    size_t len = 0;
    ssize_t nread = 0;

    stream = fopen("/etc/shadow", "r");
    if (stream == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    nread = getline(&line, &len, stream);
    while (nread != -1 && return_string == NULL) {
        if (strncmp(line, name, strlen(name)) == 0)
            return_string = get_only_good_part(line);
        nread = getline(&line, &len, stream);
    }
    free(line);
    fclose(stream);
    return (return_string);
}

int get_password(char *user_name, char **buffer)
{
    size_t size = 0;
    struct termios old;
    struct termios new;

    my_putstr("[my_sudo] password for ");
    my_putstr(user_name);
    my_putstr(": ");
    if (tcgetattr(STDIN_FILENO, &old) == 0) {
        new = old;
        new.c_lflag &= ~ECHO;
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &new);
        getline(buffer, &size, stdin);
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &old);
    } else {
        getline(buffer, &size, stdin);
    }
    my_putstr("\n");
    return (0);
}

int check_password(char *user_name, int counter, user_t *user)
{
    char *real_password = NULL;
    char *entered_passwd = calloc(sizeof(char), 100);
    char *ent_passwd = NULL;
    int return_value = -1;

    real_password = get_real_password(user->name);
    get_password(user_name, &entered_passwd);
    ent_passwd = calloc(sizeof(char), strlen(entered_passwd) + 1);
    if (ent_passwd == NULL)
        return (84);
    strncat(ent_passwd, entered_passwd, strlen(entered_passwd) - 1);
    return_value = strcmp(crypt(ent_passwd, real_password), real_password);
    free(entered_passwd);
    free(real_password);
    free(ent_passwd);
    if (return_value != 0 && counter < 3) {
        my_putstr("Sorry, try again.\n");
        return (check_password(user_name, counter + 1, user));
    }
    return (return_value);
}
