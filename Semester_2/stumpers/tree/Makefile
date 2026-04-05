##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## makefile for the my_ls project
##

SRC	=	lib/my_strcmp.c	\
		lib/my_strlen.c	\
		lib/my_strcat.c \
		lib/my_putstr.c	\
		lib/my_strdup.c	\
		lib/my_strchardup.c \
		lib/my_calloc.c \
		src/tree.c	\
		src/value_array.c

MAIN    =	src/main.c				\
		$(SRC)

OBJ	=	$(MAIN:.c=.o)

NAME	=	tree

CFLAGS	=	-I./include/

all:	$(NAME)

$(NAME):	$(OBJ)
	epiclang -o $(NAME) $(OBJ)

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
