/*
** EPITECH PROJECT, 2025
** if length and height are bigger than one
** File description:
** a function that checks what rush the square is from
** if the length and width are bigger than one
*/

#include <unistd.h>
#include "lib/my/my.h"
#include "stumper.h"
#include "struct.h"
#include <stdio.h>

static int top_line(char to_check, int square, int len, int i)
{
    if (i == 0 && to_check == COMPONENTS[square].top_left){
        return (1);
    }
    if (i == len - 1 && to_check == COMPONENTS[square].top_right){
        return (1);
    }
    if ((i != 0 && i != len - 1) && to_check == COMPONENTS[square].line_char){
        return (1);
    }
    return (0);
}

static int bot_line(char to_check, int square, int len, int i)
{
    if (i == 0 && to_check == COMPONENTS[square].bot_left){
        return (1);
    }
    if (i == len - 1 && to_check == COMPONENTS[square].bot_right){
        return (1);
    }
    if ((i != 0 && i != len - 1) && to_check == COMPONENTS[square].line_char){
        return (1);
    }
    return (0);
}

static int middle(char to_check, int square, int len, int i)
{
    if (i == 0 && to_check == COMPONENTS[square].col_char){
        return (1);
    }
    if (i == len - 1 && to_check == COMPONENTS[square].col_char){
        return (1);
    }
    if ((i != 0 && i != len - 1) && to_check == ' '){
        return (1);
    }
    return (0);
}

static int go_through_square(char *buff, int len, int height, int square)
{
    int ligne = 0;
    int valid = 0;

    for (int i = 0; i < ((len + 1) * height); i++){
        valid = (buff[i] == '\n');
        ligne = ligne + (buff[i] == '\n');;
        if (ligne == 0 && valid != 1){
            valid = top_line(buff[i], square, len, (i - ((len + 1) * ligne)));
        }
        if (ligne == (height - 1) && valid != 1){
            valid = bot_line(buff[i], square, len, (i - ((len + 1) * ligne)));
        }
        if ((ligne != 0 && ligne != (height - 1)) && valid != 1){
            valid = middle(buff[i], square, len, (i - ((len + 1) * ligne)));
        }
        if (valid != 1){
            return (0);
        }
    }
    return (square + 1);
}

static int print_pipes(int shown)
{
    if (shown > 0){
        my_putstr(" || ");
    }
    return (0);
}

int bigger_than_one(char *buff, int length, int height)
{
    int i = 0;
    int shown = 0;

    while (COMPONENTS[i].exists == 1) {
        if (go_through_square(buff, length, height, i) == i + 1){
            print_pipes(shown);
            show_rush((i + 1), length, height);
            shown++;
        }
        i++;
    }
    if (shown == 0){
        my_putstr("none");
    }
    my_putchar('\n');
    return (0);
}
