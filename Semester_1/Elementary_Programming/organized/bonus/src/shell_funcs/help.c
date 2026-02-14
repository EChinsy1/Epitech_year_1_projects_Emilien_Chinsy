/*
** EPITECH PROJECT, 2025
** help
** File description:
** a function that prints help messages
*/

#include <stdio.h>
#include <string.h>
#include "my.h"
#include "macros.h"
#include "types.h"
#include "list.h"
#include "help.h"

void print_help_add(void)
{
    printf("The add command:\n");
    printf("syntax:\n\tadd\t[TYPE, name]\n");
    printf("The add command will add any number of items to your list.\n");
    printf("It takes as argument any number of types, each followed ");
    printf("by a name.\n");
    printf("The valid types are:\n");
    printf("\tWIRE\n\tACTUATOR\n\tSENSOR\n\tDEVICE\n\tPROCESSOR\n");
    printf("It will end the program if you input any invalid type or an ");
    printf("invalid number of arguments.\n");
}

void print_help_sort(void)
{
    printf("The sort command:\n");
    printf("syntax:\n\tsort\t[TAG, \"-flag\"]\n");
    printf("The sort command will sort your arguments according to ");
    printf("three possible tags:\n");
    printf("\tNAME\n\tID\n\tTYPE\n");
    printf("Each of these tags can take a \"-r\" flag to sort in reverse.\n");
    printf("You can combine these sorting tags, ");
    printf("doing so will sort the list first ");
    printf("by using the first tag, and if it finds ");
    printf("that two items are identical ");
    printf("according to that tag, it will sort by the next tag. ");
    printf("And so on, and so forth.\n");
    printf("It will end the program if any of the sorting tags are invalid, ");
    printf("if there are no args, ");
    printf("if there is a flag that does not exist of if ");
    printf("there are sorting tags without accompanying tags.\n");
}

void print_help_disp(void)
{
    printf("The disp command:\n");
    printf("syntax:\n\tdisp\t\"-flag\"\n");
    printf("The disp command will display all the items in your list\n");
    printf("The disp command can take a \"-c\" flag ");
    printf("to print the types with ");
    printf("\x1b[01;32mc\x1b[0m\x1b[01;34mo\x1b[0m\x1b[01;35ml\x1b[0m");
    printf("\x1b[01;36mo\x1b[0m\x1b[01;31mr\x1b[0m.\n");
    printf("The disp function will end the program if it is ");
    printf("given args other than \"-c\"\n");
}

void print_help_del(void)
{
    printf("The del command:\n");
    printf("syntax:\n\tdel\t\[id]\n");
    printf("The del command will delete all items that correspond ");
    printf("to the ids you input as an argument.\n");
    printf("The del command will end the program if it is ");
    printf("given text as an argument, no arguments, or");
    printf("inexistant ids.\n");
}

static void print_help_no_args(void)
{
    int i = 0;

    printf("Hello and Welcome to Organized, ");
    printf("your own tool to help you organize your stuff!\n");
    printf("Here is list of different commands or ");
    printf("argument you can use or give me:\n");
    for (int i = 0; FUNC_AND_HELP[i].name != NULL; ++i) {
        printf("\t%s\n", FUNC_AND_HELP[i].name);
    }
}

static void find_func_and_print(char *arg)
{
    int printed = 0;

    for (int i = 0; FUNC_AND_HELP[i].name != NULL; ++i) {
        if (strcmp(FUNC_AND_HELP[i].name, arg) == 0) {
            FUNC_AND_HELP[i].fptr();
            printed = 1;
        }
    }
    if (printed == 0) {
        printf("%s doesn't exist, here is a list of functions:\n", arg);
        for (int i = 0; FUNC_AND_HELP[i].name != NULL; ++i) {
            printf("\t%s\n", FUNC_AND_HELP[i].name);
        }
    }
}

int help(void *data, char **args)
{
    int num_of_args = get_len_of_args(args);

    if (num_of_args == 0) {
        print_help_no_args();
        return (SUCCESS);
    }
    for (int i = 0; i < num_of_args; ++i) {
        find_func_and_print(args[i]);
    }
    return (SUCCESS);
}
