/*
** EPITECH PROJECT, 2025
** star*
** File description:
** this project makes us display a star
** whose size depends on a value we assign to it.
*/

#include <unistd.h>

static void printer(char c, int start_of_for, int end_of_for, int sign)
{
    if (sign <= 0){
        for (int i = start_of_for; i >= end_of_for; i--){
            my_putchar(c);
        }
    } else {
        for (int i = start_of_for; i <= end_of_for; i++){
            my_putchar(c);
        }
    }
}

static void print_top_tip(int n)
{
    printer(' ', 1, (3 * n - 1), 1);
    my_putchar('*');
    my_putchar('\n');
    for (int i = 1; i <= n - 1; i++) {
        printer(' ', 1, (3 * n - 1 - i), 1);
        my_putchar('*');
        printer(' ', 1, (1 + 2 * (i - 1)), 1);
        my_putchar('*');
        my_putchar('\n');
    }
}

static void print_bottom_tip(int n)
{
    for (int i = n - 1; i >= 1; i--) {
        printer(' ', (3 * n - i - 1), 1, -1);
        my_putchar('*');
        printer(' ', (1 + 2 * (i - 1)), 1, -1);
        my_putchar('*');
        my_putchar('\n');
    }
    printer(' ', 1, (3 * n - 1), 1);
    my_putchar('*');
    my_putchar('\n');
}

static void print_star_line(int n)
{
    printer('*', 1, ((2 * n) + 1), 1);
    if (n == 1){
        my_putchar(' ');
    } else {
        printer(' ', 1, (1 + (2 * (n - 2))), 1);
    }
    printer('*', 1, ((2 * n) + 1), 1);
    my_putchar('\n');
}

static void print_middle_top(int n)
{
    for (int i = 1; i <= n; i++){
        printer(' ', 1, i, 1);
        my_putchar('*');
        printer(' ', 1, (4 * n + 1 + 2 * (n - 2) - (2 * i)), 1);
        my_putchar('*');
        my_putchar('\n');
    }
}

void print_middle_bottom(int n)
{
    for (int i = n; i >= 2; i--){
        printer(' ', i - 1, 1, -1);
        my_putchar('*');
        printer(' ', (4 * n + 3 + 2 * (n - 2) - (2 * i)), 1, -1);
        my_putchar('*');
        my_putchar('\n');
    }
}

void print_star_if_n_is_one(void)
{
    printer(' ', 1, 3, 1);
    my_putchar('*');
    my_putchar('\n');
    print_star_line(1);
    my_putchar(' ');
    my_putchar('*');
    printer(' ', 1, 3, 1);
    my_putchar('*');
    my_putchar('\n');
    print_star_line(1);
    printer(' ', 1, 3, 1);
    my_putchar('*');
    my_putchar('\n');
}

void star(unsigned int size)
{
    if (size == 1){
        print_star_if_n_is_one();
    } else if (size != 0) {
        print_top_tip(size);
        print_star_line(size);
        print_middle_top(size);
        print_middle_bottom(size);
        print_star_line(size);
        print_bottom_tip(size);
    }
}
