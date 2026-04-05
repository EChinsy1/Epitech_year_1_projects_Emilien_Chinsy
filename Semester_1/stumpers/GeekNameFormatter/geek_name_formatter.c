/*
** EPITECH PROJECT, 2026
** stumper
** File description:
** stumper
*/

#include <unistd.h>

int my_putchar(char c)
{
    return (write(1, &c, 1));
}

int number_printer(char curr)
{
    if (curr == 'o' || curr == 'O')
        return (my_putchar('0'));
    if (curr == 'i' || curr == 'I')
        return (my_putchar('1'));
    if (curr == 'u' || curr == 'U')
        return (my_putchar('2'));
    if (curr == 'e' || curr == 'E')
        return (my_putchar('3'));
    if (curr == 'a' || curr == 'A')
        return (my_putchar('4'));
    if (curr == 'y' || curr == 'Y')
        return (my_putchar('5'));
    return (0);
}

int normal_letter_printer(char letter, int prev)
{
    if (prev % 2 == 0) {
        if (letter <= 'z' && letter >= 'a') {
            my_putchar(letter - 32);
        } else {
            my_putchar(letter);
        }
    } else {
        if (letter <= 'Z' && letter >= 'A') {
            my_putchar(letter + 32);
        } else {
            my_putchar(letter);
        }
    }
    return (0);
}

int pretty_printer(char *string)
{
    int i = 0;

    while (string[i] != '\0') {
        if (number_printer(string[i]) == 0) {
            normal_letter_printer(string[i], i);
        }
        ++i;
    }
    write(1, "\n", 1);
    return (0);
}

int geek_name_formatter(int argc, char **argv)
{
    if (argc != 2 || !argv[1]) {
        write(2, "Usage: geekNameFormatter string\n", 32);
        return (84);
    }
    return (pretty_printer(argv[1]));
}
