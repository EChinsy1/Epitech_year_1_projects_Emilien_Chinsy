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
                my_getnbr.c             \
                my_put_nbr.c            \
		my_str_to_word_array.c	\
                my_strcat.c             \
                my_strcmp.c             \
                my_strcpy.c             \
		my_strdup.c		\
                my_strlen.c             \
                my_strncat.c            \
                my_strncmp.c            \
                my_strncpy.c            \
                my_strstr.c             \
                my_strupcase.c          \
                my_itoa.c               \
		my_calloc.c		\
                my_str_isprintable.c       \

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
