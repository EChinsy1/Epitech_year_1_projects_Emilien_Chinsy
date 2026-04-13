/*
** EPITECH PROJECT, 2025
** my.h
** File description:
** include file for my printf
*/

#ifndef MY_H_
    #define MY_H_

    #include <stdio.h>
    #include <stdarg.h>
    #include <unistd.h>
    #include <stdlib.h>
    #include <stdint.h>
    #include <stddef.h>
char *my_addchar(char c, char **temp_buffer);
char *my_add_nbr(intmax_t nb, char **temp_buffer);
char *my_add_nbr_base_x(uintmax_t nb, char **temp_buffer);
char *my_add_float(long double nb, char **other_args);
int my_strlen(char const *str);
char *my_addstr(char const *str, char **temp_buffer);
char *my_pivot_add_nbr(va_list args, char **temp_buffer);
char *my_pivot_add_nbr_u(va_list args, char **temp_buffer);
char *my_pivot_add_nbr_o(va_list args, char **temp_buffer);
char *my_pivot_add_nbr_x(va_list args, char **temp_buffer);
char *my_pivot_add_nbr_x_maj(va_list args, char **temp_buffer);
char *my_pivot_addstr(va_list args, char **temp_buffer);
char *my_pivot_addchar(va_list args, char **temp_buffer);
char *my_add_percent(va_list args, char **temp_buffer);
char *my_pivot_add_float(va_list args, char **temp_buffer);
char *my_pivot_add_scientific(va_list args, char **temp_buffer);
char *my_pivot_add_scientific_maj(va_list args, char **temp_buffer);
char *my_pivot_wrong_format(va_list args, char **other_args);
char *my_pivot_add_ptr_address(va_list args, char **other_args);
char *my_pivot_add_g(va_list args, char **other_args);
char *my_pivot_add_g_maj(va_list args, char **other_args);
char *my_pivot_add_nbr_a(va_list args, char **other_args);
char *concat_params(int argc, char **argv);
int my_compute_power_rec(int nb, int p);
long double my_compute_power(int base, int result);
int my_compute_square_root(int nb);
int my_find_prime_sup(int nb);
int my_getnbr(char const *str);
int my_put_nbr(int nb);
int my_is_prime(int nb);
int my_isneg(int n);
int my_char_isnum(char const chaaar);
char *my_revstr(char *str);
int my_show_word_array(char *const *tab);
int my_showmem(char const *str, int size);
int my_showstr(char const *str);
int my_sort_int_array(int *array, int size);
int my_str_isalpha(char const *str);
int my_str_islower(char const *str);
int my_str_isnum(char const *str);
int my_str_isfloat(char const *str);
int my_str_is_num_or_float(char const *str);
int my_str_isprintable(char *str);
int my_str_isupper(char const *str);
char *my_strcapitalize(char *str);
char *my_strcat(char *dest, char const *src);
int my_strcmp(char const *s1, char const *s2);
char *my_strcpy(char *dst, char const *src);
char *my_strdup(char const *src);
int my_strlen(char const *str);
char *my_strlowcase(char *str);
char *my_strncat(char *dest, char const *src, int nb);
char *change_buffer_with_width(char *buffer, char **other_args);
char *change_buffer_with_precision_int(char *buffer, char **other_args);
char *change_buffer_with_precision_str(char *buffer, char **other_args);
int my_strncmp(char const *s1, char const *s2, int n);
char *my_strncpy(char *dest, char const *src, int n);
char *my_strstr(char *str, char const *to_find);
char *my_strupcase(char *str);
void my_swap(int *a, int *b);
char **my_str_to_word_array(char const *str);
int my_char_is_flag(char to_check);
int my_char_is_specifier(char to_check);
int my_char_is_length(const char to_check);
void add_char(char *s, char c);
char **format_specifier_separator(va_list args,
    const char *to_check,
    int *i,
    char **other_args);
char flag_is_zero(char **other_args, char *buffer);
char flag_is_space(char **other_args, char *buffer);
char flag_is_minus(char **other_args, char *buffer);
char flag_is_plus(char **other_args, char *buffer);
char flag_is_hash(char **other_args);
int size_of_num(int nb);
int my_printf(const char *format, ...);
int get_precision(char **other_args);
char **empty_other_args(char **other_args);
intmax_t length_for_int(va_list args, char **other_args);
uintmax_t length_for_ui(va_list args, char **other_args);
long double length_for_double(va_list args, char **other_ars);
void *length_for_n(va_list args, char **other_args);
char *my_add_nbr_ndigits(int nb, int precision);
char *my_add_scientific_nota(double percentage, char **other_args);
int my_char_is_specifier(char to_check);
int is_length(const char *to_check);
double my_round(double nb, int precision);

#endif
