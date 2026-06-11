/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** my.h
*/

#ifndef MACROS_H_
    #define MACROS_H_

    #define SUCCESS 0
    #define ERROR -1

    #define BLUE(string) "\e[1;34m" string "\x1b[0m"
    #define CYAN(string) "\e[1;36m" string "\x1b[0m"
    #define SUCCESS 0
    #define EPITECH_FAILURE 84
    #define PIPE 2
    #define REDIRECTION 1
    #define COMMAND 0
    #define INVALID -1
    #define BROKEN_PIPE 13
    #define PATH_LEN 5
    #define REDIR_LEN 2
    #define UNUSED __attribute_maybe_unused__

    #define HAS_GLOB(c) (c == '*' || c == '?' || c == ']' || c == ']')

    #define HISTORY_FILE "/tmp/history.txt"
    #define BACKTICK_FILE "/tmp/backticks_temp.txt"
    #define WHICH_FILE "/tmp/which.txt"

#endif
