##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## a makefile that has to:
## copy the built library into lib/,
## copy the my.h into include/,
## and implement the clean rule
##

SRC	=	my_putchar.c            \
		my_putstr.c             \
                my_compute_power_rec.c  \
                my_compute_square_root.c\
                my_find_prime_sup.c     \
		my_char_isnum.c		\
                my_getnbr.c             \
                my_is_prime.c           \
                my_isneg.c              \
                my_put_nbr.c            \
                my_revstr.c             \
                my_show_word_array.c    \
                my_showmem.c            \
                my_showstr.c            \
                my_sort_int_array.c     \
                my_str_isalpha.c	\
                my_str_islower.c        \
                my_str_isnum.c          \
		my_str_is_num_or_float.c\
		my_str_to_word_array.c	\
                my_str_isprintable.c    \
                my_str_isupper.c        \
                my_strcapitalize.c      \
                my_strcat.c             \
                my_strcmp.c             \
		my_strdup.c		\
                my_strcpy.c             \
                my_strlen.c             \
                my_strlowcase.c         \
                my_strncat.c            \
                my_strncmp.c            \
                my_strncpy.c            \
                my_strstr.c             \
                my_strupcase.c          \
                my_swap.c		\
		my_calloc.c		\
		my_printf/specifiers/helper/add_char.c					\
		my_printf/specifiers/d_or_i/my_add_nbr.c				\
                my_printf/specifiers/floating_points/my_add_float.c			\
                my_printf/specifiers/u_o_x_xmaj/my_add_nbr_base_o.c			\
                my_printf/specifiers/u_o_x_xmaj/my_add_nbr_base_x.c			\
                my_printf/specifiers/u_o_x_xmaj/my_add_nbr_base_x_maj.c			\
                my_printf/format_handling/precision/change_buffer_with_precision.c	\
                my_printf/format_handling/flags_and_width/change_buffer_with_width.c	\
                my_printf/specifiers/u_o_x_xmaj/my_add_nbr_u.c				\
		my_printf/format_handling/flags_and_width/flag_finder.c			\
                my_printf/specifiers/percent/my_add_percent.c				\
                my_printf/format_handling/formatting/format_specifier_separator.c	\
                my_printf/specifiers/floating_points/my_add_scientific_nota.c		\
		my_printf/specifiers/floating_points/my_add_scientific_nota_maj.c	\
                my_printf/specifiers/c_and_s/my_addstr.c				\
                my_printf/format_handling/flags_and_width/my_char_is_flag.c		\
                my_printf/specifiers/c_and_s/my_addchar.c				\
                my_printf/my_printf.c							\
		my_printf/format_handling/length/my_str_is_length.c			\
                my_printf/format_handling/length/length_handler.c			\
		my_printf/format_handling/formatting/in_case_of_wrong_format.c		\
		my_printf/specifiers/p/my_add_ptr_address.c				\
		my_printf/specifiers/floating_points/my_add_specifier_g.c		\
		my_printf/specifiers/floating_points/my_add_nbr_base_a.c		\
		my_printf/specifiers/floating_points/my_add_nbr_base_a_maj.c            \

OBJ	:=	$(SRC:.c=.o)

NAME	:=	libmy.a

all: $(NAME)

$(NAME):	$(OBJ)
	ar rc $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)
	rm -f *.o

fclean: clean
	rm -f $(NAME)
	rm -f ../$(NAME)

re: fclean all
