##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## makefile to compile a liby.a with my_printf
##

SRC	=	src/specifiers/helper/add_char.c				\
		src/specifiers/d_or_i/my_add_nbr.c				\
                src/specifiers/floating_points/my_add_float.c			\
                src/specifiers/u_o_x_xmaj/my_add_nbr_base_o.c			\
                src/specifiers/u_o_x_xmaj/my_add_nbr_base_x.c			\
                src/specifiers/u_o_x_xmaj/my_add_nbr_base_x_maj.c		\
                src/format_handling/precision/change_buffer_with_precision.c	\
                src/format_handling/flags_and_width/change_buffer_with_width.c	\
                src/specifiers/u_o_x_xmaj/my_add_nbr_u.c			\
		src/format_handling/flags_and_width/flag_finder.c		\
                src/specifiers/percent/my_add_percent.c				\
                src/format_handling/formatting/format_specifier_separator.c	\
                src/specifiers/floating_points/my_add_scientific_nota.c		\
		src/specifiers/floating_points/my_add_scientific_nota_maj.c	\
                src/specifiers/c_and_s/my_addstr.c				\
                src/format_handling/flags_and_width/my_char_is_flag.c		\
                src/specifiers/c_and_s/my_addchar.c				\
                src/my_printf.c							\
		src/format_handling/length/my_str_is_length.c			\
                src/format_handling/length/length_handler.c			\
		src/format_handling/formatting/in_case_of_wrong_format.c	\
		src/specifiers/p/my_add_ptr_address.c				\
		src/specifiers/floating_points/my_add_specifier_g.c		\
		src/specifiers/floating_points/my_add_nbr_base_a.c		\
		src/specifiers/floating_points/my_add_nbr_base_a_maj.c          \
                lib/my/my_compute_power_rec.c  		\
                lib/my/my_compute_square_root.c		\
                lib/my/my_char_isnum.c			\
                lib/my/my_getnbr.c			\
                lib/my/my_isneg.c			\
                lib/my/my_revstr.c			\
                lib/my/my_showstr.c			\
                lib/my/my_str_isalpha.c			\
                lib/my/my_str_is_num_or_float.c		\
		lib/my/my_str_isnum.c			\
                lib/my/my_strcat.c			\
                lib/my/my_strcmp.c			\
                lib/my/my_strcpy.c			\
                lib/my/my_strlen.c			\
                lib/my/my_strncat.c			\
                lib/my/my_strncmp.c			\
                lib/my/my_strncpy.c			\
                lib/my/my_swap.c			\
		lib/my/my_calloc.c

SRC_T   =       src/specifiers/helper/add_char.c                                \
                src/specifiers/d_or_i/my_add_nbr.c                              \
                src/specifiers/floating_points/my_add_float.c                   \
                src/specifiers/u_o_x_xmaj/my_add_nbr_base_o.c                   \
                src/specifiers/u_o_x_xmaj/my_add_nbr_base_x.c                   \
                src/specifiers/u_o_x_xmaj/my_add_nbr_base_x_maj.c               \
                src/format_handling/precision/change_buffer_with_precision.c    \
                src/format_handling/flags_and_width/change_buffer_with_width.c  \
                src/specifiers/u_o_x_xmaj/my_add_nbr_u.c                        \
                src/format_handling/flags_and_width/flag_finder.c               \
                src/specifiers/percent/my_add_percent.c                         \
                src/format_handling/formatting/format_specifier_separator.c     \
                src/specifiers/floating_points/my_add_scientific_nota.c         \
                src/specifiers/floating_points/my_add_scientific_nota_maj.c     \
                src/specifiers/c_and_s/my_addstr.c                              \
                src/format_handling/flags_and_width/my_char_is_flag.c           \
                src/specifiers/c_and_s/my_addchar.c                             \
                src/my_printf.c                                                 \
                src/format_handling/length/my_str_is_length.c                   \
                src/format_handling/length/length_handler.c                     \
                src/format_handling/formatting/in_case_of_wrong_format.c        \
                src/specifiers/p/my_add_ptr_address.c                           \
                src/specifiers/floating_points/my_add_specifier_g.c             \
                src/specifiers/floating_points/my_add_nbr_base_a.c

OBJ	=	$(SRC:.c=.o)

NAME	=	libmy.a

all:	$(NAME)

$(NAME):	$(OBJ)
	ar rc $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)
	rm -f *.o

fclean: clean
	find -type f -name "*~" -delete -o -type f -name "#*#" -delete

clean_tests:
	rm -f *.gcda
	rm -f *.gcno

unit_tests: all
	epiclang -o unit_tests          \
        $(SRC_T) tests/test_my_printf.c \
	-L.                             \
	-lmy                            \
        --coverage                      \
        -lcriterion                     \

tests_run:	unit_tests
	./unit_tests			\

re: fclean all

