##
## EPITECH PROJECT, 2026
## Makefile
## File description:
## stumper 1
##

CC	=	epiclang

SRC	=	main.c	\
		fozzbazz.c

SRC_T	=	fozzbazz.c

OBJ	=	$(SRC:.c=.o)

NAME	=	fozzbazz

all:	$(NAME)

$(NAME):	$(OBJ)
	epiclang -o $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

unit_tests: all
	epiclang -o unit_tests				\
		$(SRC_T) tests/tests_fozzbazz.c		\
	--coverage -lcriterion				\

tests_run: unit_tests
	./unit_tests

clean_tests:
	$(RM) unit_tests
	rm *.gcda && rm *.gcno


re: fclean all
