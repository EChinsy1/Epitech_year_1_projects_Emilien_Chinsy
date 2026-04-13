##
## EPITECH PROJECT, 2025
## makefile
## File description:
## emacs
##

SRC 	=	if_length_and_height_bigger_than_one.c	\
		check_for_1_height.c			\
		check_for_1_length.c			\
		length_height.c				\
		rush3.c					\
		show_buff.c				\
		stumper.c				\
		width_and_length_are_one.c

OBJ	:=	$(SRC:.c=.o)

NAME	:=	rush3

all: $(NAME)

$(NAME):	$(OBJ)
	cd lib/my/ && make re
	epiclang -o $(NAME) $(OBJ) -Ilib/my/ -Llib/my/ -lmy

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
