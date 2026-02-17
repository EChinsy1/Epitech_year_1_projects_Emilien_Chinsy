##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## a makefile that has to:
## copy the built library into lib/,
## copy the my.h into include/,
## and implement the clean rule
##

SRC	=	my_putstr.c             \
                my_compute_power_rec.c  \
                my_compute_square_root.c\
                my_find_prime_sup.c     \
                my_getnbr.c             \
                my_is_prime.c           \
                my_isneg.c              \
                my_put_nbr.c            \
                my_putchar.c            \
                my_revstr.c             \
                my_show_word_array.c    \
                my_showmem.c            \
                my_showstr.c            \
                my_sort_int_array.c     \
                my_str_isalpha.c	\
                my_str_islower.c        \
                my_str_isnum.c          \
                my_str_isprintable.c    \
                my_str_isupper.c        \
                my_strcapitalize.c      \
                my_strcat.c             \
                my_strcmp.c             \
                my_strcpy.c             \
                my_strlen.c             \
                my_strlowcase.c         \
                my_strncat.c            \
                my_strncmp.c            \
                my_strncpy.c            \
                my_strstr.c             \
                my_strupcase.c          \
                my_swap.c

OBJ	:=	$(SRC:.c=.o)

NAME	:=	libmy.a

CC      =       epiclang
CFLAGS  =       -Wall -Wextra -Werror -I.

all: $(NAME)

$(NAME):	$(OBJ)
	ar rc $(NAME) $(OBJ)
	cp $(NAME) ../libmy.a
	cp my.h ../../include/my.h

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f ../$(NAME)
