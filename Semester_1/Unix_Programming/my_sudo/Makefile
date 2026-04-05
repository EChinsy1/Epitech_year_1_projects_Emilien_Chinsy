##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## makefile for the my_sudo project
##

SRC	=	src/sudo/my_exec.c			\
		src/parsing/my_getnameuid.c		\
		src/parsing/get_groups.c		\
		src/parsing/password_handling.c		\
		src/flags/flag_handling.c		\
		src/helper_functions/helper_functions.c	\
		src/parsing/check_groups.c

NAME	=	my_sudo

FLAGS	=	-lcrypt -I./src/includes

all:	$(NAME)

$(NAME):
	epiclang $(FLAGS) $(SRC) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
