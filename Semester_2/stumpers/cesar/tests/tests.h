/*
** EPITECH PROJECT, 2026
** tests.h
** File description:
** tests.h
*/

#ifndef TESTS_H
    #define TESTS_H

char *open_file(const char *filename);
char *decrypt(char *string, int n);
int crypt_in_file(char *message);
int cesar(int argc, char **argv);
char *get_buffer(char **argv);

#endif
