##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## Makefile for 102architect
##

SRC	=	src/104neutrinos.c	\
		src/result.c		\
		src/calculate.c		\
		src/main.c

SRC_T     =     src/104neutrinos.c  \
                src/result.c        \
                src/calculate.c

OBJ	=	$(SRC:.c=.o)

CC	=	epiclang

CFLAGS	=	-I./include

LDFLAGS	=	-lm

NAME	=	104neutrinos

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LDFLAGS)

clean:
	$(RM) $(NAME)

unit_tests: all
	$(CC) -o unit_tests					\
		$(SRC_T) $(CFLAGS) tests/test_neutrinos.c	\
	$(LDFLAGS) --coverage -lcriterion

tests_run: unit_tests
	./unit_tests

clean_tests:
	$(RM) unit_tests
	rm *.gcda && rm *.gcno

fclean:	clean
	$(RM) $(OBJ)

re:	fclean all

.PHONY: all $(NAME) clean fclean re unit_tests tests_run clean_tests
