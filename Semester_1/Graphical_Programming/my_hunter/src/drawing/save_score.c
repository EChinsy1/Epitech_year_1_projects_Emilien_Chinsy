/*
** EPITECH PROJECT, 2025
** save score
** File description:
** store the highscore in a text file
*/

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include "my.h"
#include "struct_elements.h"

int get_size_of_score(int score)
{
    int i = 0;

    while (score > 0) {
        score = score / 10;
        ++i;
    }
    return (i);
}

int get_high_score(int *len)
{
    int fd = open("highscore.txt", (O_RDONLY | O_CREAT), 00664);
    char *score_txt = NULL;
    struct stat sb;
    int score = 0;

    if (fd < 0)
        return (84);
    stat("highscore.txt", &sb);
    score_txt = my_calloc(sizeof(char), sb.st_size + 1);
    read(fd, score_txt, sb.st_size);
    score = my_getnbr(score_txt);
    *len = my_strlen(score_txt);
    free(score_txt);
    close(fd);
    return (score);
}

void store_high_score(int score, int type)
{
    int len_score = 0;
    int high_score = get_high_score(&len_score);
    int fd = 0;
    char *score_text;
    int i = 0;

    len_score = get_size_of_score(score);
    if (high_score < score){
        score_text = my_calloc(len_score + 1, sizeof(char));
        fd = open("highscore.txt", (O_RDWR | O_CREAT | O_TRUNC), 00664);
        while (score > 0) {
            score_text[i] = score % 10 + '0';
            score = score / 10;
            ++i;
        }
        my_revstr(score_text);
        write(fd, score_text, len_score);
        close(fd);
        free(score_text);
    }
}
