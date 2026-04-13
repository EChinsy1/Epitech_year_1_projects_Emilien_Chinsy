/*
** EPITECH PROJECT, 2025
** stumper
** File description:
** emacs
*/

#include <unistd.h>
#include "lib/my/my.h"
#include "stumper.h"

int main(void)
{
    char buff[30000];
    int offset = 0;
    int len = read(0, buff + offset, 30000 - offset);

    while (len > 0) {
        offset += len;
        len = read(0, buff + offset, 30000 - offset);
    }
    buff[offset] = '\0';
    if (len < 0) {
        return 84;
    }
    return (rush3(buff, length(buff), height(buff)));
}
