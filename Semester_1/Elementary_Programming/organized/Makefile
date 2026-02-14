##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## makefile for the my_ls project
##

CC	=	epiclang

SRC	=	src/helper_functions/free_funcs.c	\
		src/shell_funcs/add.c			\
		src/shell_funcs/sort.c			\
		src/shell_funcs/del.c			\
		src/shell_funcs/disp.c			\
		src/shell_funcs/sort_funcs.c            \
		src/shell_funcs/rev_sort_funcs.c	\
		src/helper_functions/get_len_of_args.c	\

MAIN    =	src/main.c				\
		$(SRC)

OBJ	=	$(MAIN:.c=.o)

NAME	=	organized

LDFLAGS	=	-L./lib/my/

LDLIBS	=	-lmy -lshell

CFLAGS	=	-I./includes/

all:	$(NAME)

$(NAME):	$(OBJ)
	cd ./lib/my/ && make re
	epiclang -o $(NAME) $(OBJ) $(LDFLAGS) $(LDLIBS)

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
