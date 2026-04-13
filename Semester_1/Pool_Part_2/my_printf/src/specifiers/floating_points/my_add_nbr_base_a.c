/*
** EPITECH PROJECT, 2025
** my_add_nbr_base_a.c
** File description:
** handles the %a specifier
*/

#include "../../includes/my.h"

static int get_power(double number)
{
    int power = 0;

    if (number < 0)
        number = number * -1;
    if (number == 0)
        return (power);
    while ((int)number < 1){
        number = number * 2;
        power--;
    }
    while ((int)number > 1){
        number = number / 2;
        power++;
    }
    return (power);
}

static int get_actual_precision(char *buffer)
{
    int i = 0;

    while (buffer[i]){
        i++;
    }
    if (buffer[0] == '-')
        i--;
    if (i > 3)
        i--;
    return (i - 3);
}

static char *round_with_zeros(char *buffer, int number)
{
    char *string = NULL;
    int dot = 0;

    string = my_calloc((my_strlen(buffer) + number), sizeof(int));
    for (int j = 0; buffer[j]; j++){
        string[j] = buffer[j];
        if (buffer[j] == '.')
            dot = 1;
    }
    if (dot == 0)
        add_char(string, '.');
    for (int i = 0; i < number; i++){
        add_char(string, '0');
    }
    add_char(string, '\0');
    free(buffer);
    return (string);
}

static void round_up(char *buffer, char *string, int i, int sign)
{
    if (i == sign + 3 && buffer[i + 1] > '7')
        string[i - 1]++;
    while ((buffer[i] > '7' && i > sign + 3)){
        string[i - 1] = string[i - 1] + 1;
        buffer[i] = '0';
        if (string[i - 1] == 'g'){
            string[i - 1] = '0';
            i--;
        }
        if (string[i - 1] == '/'){
            string[i - 2]++;
            string[i - 1] = '.';
        }
    }
}

static char *round_short(char *buffer, int preci, char **other_args, int sign)
{
    int i = 0;
    char *string = my_calloc(100, sizeof(char));
    int precision = preci;

    if (preci > 0)
        preci++;
    while (i < preci + 3 + sign){
        string[i] = buffer[i];
        i++;
    }
    add_char(string, '\0');
    round_up(buffer, string, i, sign);
    if (flag_is_hash(other_args) == 1 && precision == 0){
        add_char(string, '.');
    }
    free(buffer);
    return (string);
}

char *round_hex(char *buffer, char **other_args, int sign)
{
    int i = 0;
    int j = 0;
    int precision = get_precision(other_args);
    int actual_precision = get_actual_precision(buffer);

    if (sign == 1)
        sign = 0;
    if (sign == -1)
        sign = 1;
    if (my_strlen(other_args[2]) == 0 || precision == actual_precision){
        return (buffer);
    } else if (precision > actual_precision){
        return (round_with_zeros(buffer, precision - actual_precision));
    } else {
        return (round_short(buffer, precision, other_args, sign));
    }
}

char *add_mantissa(double number, char *buffer)
{
    char *temp_buffer = NULL;
    int int_part = 0;
    char *hex_base = "0123456789abcdef";

    temp_buffer = my_calloc(100, sizeof(char));
    my_strcat(temp_buffer, ".");
    while (number > 0){
        number = number * 16;
        int_part = number;
        add_char(temp_buffer, hex_base[int_part]);
        number = number - int_part;
    }
    my_strcat(buffer, temp_buffer);
    free(temp_buffer);
    return (buffer);
}

void add_nbr_a(double number, int power, char **other_args, char *real_buffer)
{
    char *buffer = my_calloc(100, sizeof(char));
    int int_part = 0;
    int sign = 1;
    char *new_other_args[6];

    if (number < 0)
        sign = -1;
    number = number * sign;
    if (sign != 1)
        my_strcat(buffer, "-");
    my_strcat(buffer, "0x1");
    if (number > 0)
        add_mantissa(number, buffer);
    buffer = round_hex(buffer, other_args, sign);
    my_strcat(buffer, "p");
    if (power >= 0)
        my_strcat(buffer, "+");
    my_fake_pivot_add_nbr(power, empty_other_args(new_other_args), buffer);
    my_strcat(real_buffer, buffer);
    free(buffer);
}

char *my_add_nbr_base_a(double number, char **other_args)
{
    int power = get_power(number);
    int sign = 1;
    char *buffer = my_calloc(100, sizeof(char));
    char *string;

    if (number == 0){
        string = round_hex(my_strcat(buffer, "0x0"), other_args, sign);
        return (my_strcat(string, "p+0"));
    }
    if (number < 0)
        sign = -1;
    number = number * sign;
    while ((int)number < 1)
        number = number * 2;
    while ((int)number > 1)
        number = number / 2;
    number = number - 1;
    add_nbr_a(number * sign, power, other_args, buffer);
    return (change_buffer_with_width(buffer, other_args));
}

char *my_pivot_add_nbr_a(va_list args, char **other_args, char *buffer)
{
    char *temp_buffer = my_add_nbr_base_a(
        length_for_double(args, other_args),
        other_args);

    my_strcat(buffer, temp_buffer);
    free(temp_buffer);
    return (buffer);
}
