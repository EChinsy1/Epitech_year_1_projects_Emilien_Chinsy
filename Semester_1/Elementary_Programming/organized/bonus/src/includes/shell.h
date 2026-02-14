/*
** EPITECH PROJECT, 2025
** G-CPE-110 : Setting Up Shell
** File description:
** shell.h
*/

#ifndef SHELL_H
    #define SHELL_H

int add(void *data, char **args);
int del(void *data, char **args);
int sort(void *data, char **args);
int disp(void *data, char **args);
int parse(void *data, char **args);
int stats(void *data, char **args);
int empty(void *data, char **args);
int help(void *data, char **args);
int save(void *data, char **args);
int create_save_file(linked_list_t *list);
int workshop_shell(void *data);

#endif
