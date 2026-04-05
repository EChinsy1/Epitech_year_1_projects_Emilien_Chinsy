##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## makefile for the my_ls project
##

SRC_T     =     cipher.c                \
                make_matrix.c           \
                multiply_matrixes.c     \
                decrypt.c               \
		my_find_prime_sup.c

SRC	=	main.c			\
		cipher.c		\
		make_matrix.c		\
		multiply_matrixes.c	\
		decrypt.c		\
		my_find_prime_sup.c

OBJ	=	$(SRC:.c=.o)

NAME	=	103cipher

all:	$(NAME)

$(NAME):	$(OBJ)
	epiclang -o $(NAME) $(OBJ) -lm

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

unit_tests: all
	epiclang -o unit_tests					\
		$(SRC_T) $(CFLAGS) tests/test_cipher.c		\
        -lm --coverage -lcriterion

tests_run: unit_tests
	./unit_tests

clean_tests:
	$(RM) unit_tests
	rm *.gcda && rm *.gcno

re: fclean all
