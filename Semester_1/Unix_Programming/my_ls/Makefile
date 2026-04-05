##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## makefile for the my_ls project
##

SRC	=	src/main.c					\
		src/flag_handling/flag_and_path_separator.c	\
		src/flag_handling/flag_r_handling.c		\
		src/flag_handling/flag_l_printing.c		\
                src/flag_handling/sort_with_t.c	                \
		src/ls/my_ls.c

NAME	=	my_ls

FLAGS	=	-L./lib/my/ -lmy -I./src/includes/

all:	$(NAME)

$(NAME):
	cd lib/my/ && make re
	epiclang $(SRC) -o $(NAME) $(FLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
