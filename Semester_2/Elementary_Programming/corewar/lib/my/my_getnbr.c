/*
** EPITECH PROJECT, 2026
** getnbr
** File description:
** robot factory getnbr
*/

int my_getnbr(char const *str)
{
    long num = 0;
    int i = 0;

    for (int val = i; str[val] != '\0'; val++) {
        if ((((num * 10) + 8) > 2147483647)) {
            num = 0;
            break;
        }
        if (str[val] <= 57 && str[val] >= 48){
            num = num * 10 + (str[val] - 48);
        } else {
            break;
        }
    }
    return (num);
}
