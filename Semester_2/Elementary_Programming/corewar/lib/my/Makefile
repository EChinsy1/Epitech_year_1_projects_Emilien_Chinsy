##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## a makefile that has to:
## copy the built library into lib/,
## copy the my.h into include/,
## and implement the clean rule
##

CC 	= 	epiclang

SRC	=	$(shell find ./ -name "*.c")

OBJ	:=	$(SRC:.c=.o)

NAME	:=	libmy.a

CPPFLAGS +=     -iquote ../../include

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
