##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## makefile for the my_ls project
##

SRC	=	main.c			\
		pong.c			\
		validity_checks.c	

SRC_T	=	pong.c			\
		validity_checks.c	\

OBJ	=	$(SRC:.c=.o)

NAME	=	101pong

all:	$(NAME)

$(NAME):	$(OBJ)
	epiclang -o $(NAME) $(OBJ) -L./lib/my/ -lm

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

unit_tests: all
	epiclang -o unit_tests			\
		$(SRC_T) tests/test_pong.c	\
	-lm --coverage -lcriterion		\

tests_run: unit_tests
	./unit_tests

clean_tests:
	$(RM) unit_tests
	rm *.gcda && rm *.gcno

re: fclean all
