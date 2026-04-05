/*
** EPITECH PROJECT, 2026
** amazed
** File description:
** my_getnbr
*/

static int get_sign(char const *str, int *i)
{
    int sign = 1;

    while ((str[*i] == 45) || (str[*i] == 43)){
        if (str[*i] == 45){
            sign = -sign;
        }
        (*i)++;
    }
    return (sign);
}

int my_getnbr(char const *str)
{
    long num = 0;
    int i = 0;
    int val = 0;
    int sign = get_sign(str, &i);

    while (str[val] <= 57 && str[val] >= 48) {
        if ((((num * 10) + 8) > 2147483647)) {
            num = 0;
            break;
        } else {
            num = num * 10 + (str[val] - 48);
        }
        val++;
    }
    return (num * sign);
}
