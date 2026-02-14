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

void print_help_all(void)
{
    int i = 0;

    printf("Hello and Welcome to Organized, your own tool to help you ");
    printf("organize your stuff!\n");
    printf("Here is list of different commands you can use ");
    printf("and their arguments:\n");
    printf("\tcommand_name\targ_1\t[arg_group]\t\"optional_arg\"\n\n\n");
    for (int i = 0; FUNC_AND_HELP[i].name != NULL
        && strcmp(FUNC_AND_HELP[i].name, "all") != 0; ++i) {
        FUNC_AND_HELP[i].fptr();
        printf("\n\n");
    }
}

void print_help_empty(void)
{
    printf("The empty command:\n");
    printf("syntax:\n\tempty\n");
    printf("The empty command will empty your linked list.\n");
    printf("The empty command will end the program if ");
    printf("given any arguments\n");
}

void print_help_parse(void)
{
    printf("The parse command:\n");
    printf("syntax:\n\tparse\tpath_to_file\n");
    printf("The parse command will parse files under a specific format");
    printf(" and fill up the linked_list with items from that file.\n");
    printf("the format is:\nTYPE\tname\n");
    printf("each line must only contain these two ");
    printf("and you cannot input the unique id\n");
    printf("the parse command will end the program ");
    printf("if you input more and less than one arg");
    printf(" or if the file is in any way invalid ");
    printf("(such as it doesn't exist or it doesn't");
    printf(" follow the format.\n");
}

void print_help_stats(void)
{
    printf("The stats command:\n");
    printf("syntax:\n\tstats\t\"-flag\"\n");
    printf("The stats command will show you stats on ");
    printf("your current list of items.\n");
    printf("It will tell you:\n\tthe next element's ");
    printf("id\n\tthe current_number_of_items");
    printf(" that the list holds.\n\tAnd the number of ");
    printf("items of each type the list holds.\n");
    printf("It can also take a \"-c\" flag to print the types with ");
    printf("\x1b[01;32mc\x1b[0m\x1b[01;34mo\x1b[0m\x1b[01;35ml\x1b[0m");
    printf("\x1b[01;36mo\x1b[0m\x1b[01;31mr\x1b[0m.\n");
    printf("The stats command will end the program if ");
    printf("it is given args other than \"-c\"\n");
}

void print_help_help(void)
{
    printf("The help command:\n");
    printf("syntax:\n\thelp\t[\"name_of_command\"]\n");
    printf("The help command ");
    printf("will print information depending on the argument:\n");
    printf("With no args, it will print a ");
    printf("small intro to the program and a list of commands\n");
    printf("With the name of a command, ");
    printf("it will print the help for that command.\n");
    printf("With all: it will print everything.\n");
    printf("The help command will never end the program.\n");
}
