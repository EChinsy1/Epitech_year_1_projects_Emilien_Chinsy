##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## makefile for the my_ls project
##

SRC	=	algorithms.c		\
		file_systems.c		\
		file_validaition.c	\
		setting_up.c		\
		main.c			\

SRC_T	=	algorithms.c            \
                file_systems.c          \
                file_validaition.c      \
		setting_up.c		\
		tests/simple_tests.c

OBJ	=	$(SRC:.c=.o)

NAME	=	setting_up

all:	$(NAME)

$(NAME):	$(OBJ)
	cd lib/my/ && make re
	epiclang -o $(NAME) $(OBJ) -L./lib/my/ -lmy

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

unit_tests: all
	epiclang -o unit_tests				\
		$(SRC_T)				\
	--coverage -lcriterion -L./lib/my/ -lmy		\

tests_run: unit_tests
	./unit_tests

re: fclean all
