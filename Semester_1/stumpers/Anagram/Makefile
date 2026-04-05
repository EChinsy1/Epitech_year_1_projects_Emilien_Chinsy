##
## EPITECH PROJECT, 2026
## Makefile
## File description:
## stumper 1
##

SRC	=	main.c	\
		anagram.c

SRC_T	=	anagram.c

OBJ	=	$(SRC:.c=.o)

NAME	=	anagram

all:	$(NAME)

$(NAME):	$(OBJ)
	epiclang -o $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

unit_tests: all
	cc -o unit_tests				\
		$(SRC_T) tests/tests_anagram.c		\
	--coverage -lcriterion				\

tests_run: unit_tests
	./unit_tests

clean_tests:
	$(RM) unit_tests
	rm *.gcda && rm *.gcno


re: fclean all
