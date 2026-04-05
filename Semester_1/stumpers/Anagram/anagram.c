/*
** EPITECH PROJECT, 2026
** anagram
** File description:
** main
*/

#include <unistd.h>
#include <stdio.h>

void my_putchar(char c)
{
    write(1, &c, 1);
}

int my_strlen(char *str)
{
    int i = 0;

    while (str[i] != '\0')
        ++i;
    return (i);
}

int check_if_occurs(int occurs, int indice, char str1, char *str2)
{
    char char_1 = 'a';
    char char_2 = 'a';

    if (occurs != 0 || indice == -1)
        return (occurs);
    char_1 = str1;
    if (char_1 >= 65 && char_1 <= 90)
        char_1 += 32;
    char_2 = str2[indice];
    if (char_2 >= 65 && char_2 <= 90)
        char_2 += 32;
    if (char_1 == char_2) {
        return (indice + 1);
    }
    return (0);
}

int anagram(char *str1, char *str2, int len)
{
    int indices[len];
    int occurs = 0;

    for (int i = 0; i < len; ++i)
        indices[i] = i;
    for (int i = 0; i < len; ++i) {
        occurs = 0;
        for (int j = 0; j < len; ++j) {
            occurs = check_if_occurs(occurs, indices[j], str1[i], str2);
        }
        if (occurs == 0){
            return (0);
        } else {
            indices[occurs - 1] = -1;
        }
    }
    return (1);
}

int anagram_main(int argc, char **argv)
{
    int is_anagram = 0;
    int len_1 = 0;
    int len_2 = 0;

    if (argc != 3) {
        write(2, "Error: not enough arguments.\n", 29);
        return (84);
    }
    len_1 = my_strlen(argv[1]);
    len_2 = my_strlen(argv[2]);
    if (len_1 == len_2)
        is_anagram = anagram(argv[1], argv[2], len_1);
    if (is_anagram == 1) {
        write(1, "anagram!\n", 9);
    } else {
        write(1, "no anagrams.\n", 13);
    }
    return (0);
}
