##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## a makefile that has to:
## copy the built library into lib/,
## copy the my.h into include/,
## and implement the clean rule
##

CC	=	epiclang

SRC	=	my_putchar.c		\
		my_getnbr.c             \
                my_put_nbr.c            \
                my_revstr.c             \
                my_strcat.c             \
                my_strcmp.c             \
                my_strcpy.c             \
		my_strdup.c		\
                my_strlen.c             \
                my_strncat.c            \
                my_strncmp.c            \
                my_strncpy.c            \
		my_calloc.c		\

OBJ	:=	$(SRC:.c=.o)

NAME	:=	libmy.a

CFLAGS	=	-g3 -Wall -Wextra

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
