##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## makefile for the my_ls project
##

SRC	=	src/get_map.c	\
		src/parsing.c	\
		src/get_array.c	\
		src/print_map.c	\
		src/pathfinding.c

MAIN    =	src/main.c				\
		$(SRC)

OBJ	=	$(MAIN:.c=.o)

NAME	=	my_ginger

CFLAGS	=	-I./include/

all:	$(NAME)

$(NAME):	$(OBJ)
	epiclang -g3 -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

unit_tests: all
	cc -o unit_tests				\
		$(SRC) tests/test_organized.c		\
	$(CFLAGS) $(LDFLAGS) $(LDLIBS)			\
	--coverage -lcriterion				\

tests_run: unit_tests
	./unit_tests

clean_tests:
	$(RM) unit_tests
	rm *.gcda && rm *.gcno

re: fclean all
