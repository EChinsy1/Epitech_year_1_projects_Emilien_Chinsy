/*
** EPITECH PROJECT, 2025
** my_revstr
** File description:
** we have to write to write a copy of the revstr function
** from the c standard library
*/

#include "my.h"

static int my_swap_str(char *stra, char *strb)
{
    char temp;

    temp = *stra;
    *stra = *strb;
    *strb = temp;
    return (0);
}

int my_strlen(char const *str)
{
    int i = 0;

    while (str[i] != '\0'){
        i++;
    }
    return (i);
}

char *my_revstr(char *str)
{
    int len = my_strlen(str) - 1;
    int i = 0;

    if (len <= 0){
        return (str);
    }
    if (len % 2 == 1){
        while (1 < (len + 1 - i)){
            my_swap_str(&str[len], &str[i]);
            len--;
            i++;
        }
    } else {
        while ((len - i) != 0){
            my_swap_str(&str[len], &str[i]);
            len--;
            i++;
        }
    }
    return (str);
}
