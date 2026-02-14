/*
** EPITECH PROJECT, 2025
** help
** File description:
** a function that prints help messages
*/

#include <stdio.h>
#include <string.h>
#include "my.h"
#include "types.h"
#include "list.h"
#include "help.h"

void print_help_save(void)
{
    printf("The save command:\n");
    printf("syntax:\n\tsave\n");
    printf("The save command ");
    printf("will save your current linked list");
    printf(" as a file called savefile.\n");
    printf("The save command will automatically be called");
    printf(" if you wrote an invalid command that made the ");
    printf("program exit.\n any call to save will replace the");
    printf(" previous savefile with the new data.\n");
    printf("save will exit the program if there are any args.\n");
}
