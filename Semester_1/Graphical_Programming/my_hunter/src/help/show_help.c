/*
** EPITECH PROJECT, 2025
** show help*
** File description:
** -h
*/

#include <unistd.h>

int show_help(void)
{
    write(1, "Hello and welcome to my_hunter!\n\n", 33);
    write(1, "Its duck migrating season, ", 28);
    write(1, "and they are coming for you grain!.\n", 37);
    write(1, "protect it by shooting them. They ", 34);
    write(1, "will always come from the west as they are migrating.\n", 55);
    write(1, "Beware though farmer, ", 22);
    write(1, "the birds have mutated due to pollution, ", 42);
    write(1, "Some of them are a lot stronger ", 32);
    write(1, "and others are a lot faster. Beware.\n", 38);
    write(1, "Nevertheless, there are two game modes, ", 41);
    write(1, "long which is an endless mode, ", 32);
    write(1, "and a mode with predetermined levels.\n", 38);
    write(1, "Good luck and have fun farmer!", 30);
    return (0);
}
