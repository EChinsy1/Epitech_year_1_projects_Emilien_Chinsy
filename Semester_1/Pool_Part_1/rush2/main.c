/*
** EPITECH PROJECT, 2025
** Step 4.
** File description:
** The program looks at a sentence given to it,
** and calculates the frequency of each letter,
** requested as an argument.
** it will then compare the numbers from wikipedia
** and show which language the sentence is most likely to be from
*/

#include "my.h"
#include "my_struct.h"
#include "my_macro_abs.h"
#include <unistd.h>

static int error_handling(char **argv, int argc)
{
    int j = 2;

    if (argc < 3){
        return (84);
    }
    if (argv[1] == ((void *)0) || argv[2] == ((void *)0)){
        return (84);
    }
    while (j <= argc - 1){
        if ((my_str_isalpha(argv[j])) == 0 || (my_strlen(argv[j]) > 1)) {
            return (84);
        }
        j++;
    }
    return (0);
}

int num_of_letters(char **argv)
{
    int result = 0;
    int i = 0;
    char curr;

    while (i < my_strlen(argv[1])){
        curr = argv[1][i];
        if ((curr <= 90 && curr >= 65) || (curr <= 122 && curr >= 97)){
            result++;
        }
        i++;
    }
    return (result);
}

void show_percentages(float percentage)
{
    int int_part;
    int float_part;

    int_part = (percentage + 0.05);
    float_part = (percentage * 100);
    float_part = (float_part % 100);
    my_putstr(" (");
    my_put_nbr(int_part);
    my_putchar('.');
    my_put_nbr(float_part);
    if (float_part == 0){
        my_putchar('0');
    }
    my_putstr("%)\n");
}

static int occurence_counter(int j, char **argv, char mini_l)
{
    int i = 0;
    float occurences = 0;
    float percentage;

    while (i < my_strlen(argv[1])){
        if (argv[1][i] == mini_l || argv[1][i] == (mini_l - 32)){
            occurences++;
        }
        i++;
    }
    percentage = occurences / num_of_letters(argv) * 100;
    my_putchar(*argv[j]);
    my_putchar(':');
    my_put_nbr(occurences);
    show_percentages(percentage);
    return (occurences);
}

static int find_alpha_num_of_letter(char mini_l)
{
    int i = 0;
    char curr_char;

    while (i < 26){
        curr_char = EACH_OCCURENCE[i].letter;
        if (curr_char == mini_l){
            return (i);
        }
        i++;
    }
    return (0);
}

static int which_language(char **argv, float occurences, char mini_l, int num_l)
{
    float percentage = occurences / num_l * 100;
    int letter = find_alpha_num_of_letter(mini_l);
    float distances[4] = {
        ABS(EACH_OCCURENCE[letter].English - percentage),
        ABS(EACH_OCCURENCE[letter].French - percentage),
        ABS(EACH_OCCURENCE[letter].German - percentage),
        ABS(EACH_OCCURENCE[letter].Spanish - percentage)};
    int result = 0;
    int i = 1;

    while (i <= 3){
        if (distances[result] < distances[i]){
            result = i;
        }
        i++;
    }
    return (result - 1);
}

static char make_it_small(char **argv, int current)
{
    if (*argv[current] <= 90){
        return (*argv[current] + 32);
    }
    return (*argv[current]);
}

int who_is_the_biggest(int *who_is_more_common)
{
    int result = 0;
    int i = 1;
    const char *name[4] = {"English", "French", "German", "Spanish"};

    while (i <= 3){
        if (who_is_more_common[i] > who_is_more_common[result]){
            result = i;
        }
        i++;
    }
    write(1, "=> ", 3);
    my_putstr(name[result]);
    return (0);
}

int main(int argc, char **argv)
{
    int j = 2;
    float occurence = 0;
    int who_is_more_common[4];
    char mini_l;
    int letters = num_of_letters(argv);

    if (error_handling(argv, argc) == 84){
        return (84);
    }
    for (int i = 0; i < 4; i++){
        who_is_more_common[i] = 0;
    }
    while (j <= argc - 1){
        mini_l = make_it_small(argv, j);
        occurence = occurence_counter(j, argv, mini_l);
        who_is_more_common[which_language(argv, occurence, mini_l, letters)]++;
        j++;
    }
    who_is_the_biggest(who_is_more_common);
    return 0;
}
