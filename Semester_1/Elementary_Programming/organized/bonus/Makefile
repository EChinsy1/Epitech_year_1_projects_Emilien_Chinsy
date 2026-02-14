##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## makefile for the my_ls project
##

CC	=	epiclang

SRC_T   =       src/organized.c                         \
		src/colors/print_types.c		\
                src/shell_funcs/add.c                   \
                src/shell_funcs/sort.c                  \
                src/shell_funcs/del.c                   \
                src/shell_funcs/sort_funcs.c            \
                src/shell_funcs/rev_sort_funcs.c        \
                src/helper_functions/get_len_of_args.c  \

SRC	=	src/organized.c				\
		src/colors/print_types.c		\
		src/main.c				\
		src/workshop_shell/workshop_shell.c	\
		src/shell_funcs/add.c			\
		src/shell_funcs/sort.c			\
                src/shell_funcs/stats.c                 \
		src/shell_funcs/del.c			\
		src/shell_funcs/parse.c			\
                src/shell_funcs/empty.c			\
                src/shell_funcs/help.c                  \
                src/shell_funcs/help2.c                 \
		src/shell_funcs/help3.c			\
		src/shell_funcs/sort_funcs.c            \
		src/shell_funcs/rev_sort_funcs.c	\
		src/helper_functions/get_len_of_args.c	\
		src/shell_funcs/save.c			\

NAME	=	organized

FLAGS	=	-L./lib/my/ -lmy -I./src/includes/

all:	$(NAME)

$(NAME):
	cd ./lib/my/ && make re
	epiclang -o $(NAME) $(SRC) $(FLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

unit_tests: all
	epiclang -o unit_tests				\
		$(SRC_T) tests/test_organized.c		\
	-L./lib/my/ -lmy -lshell -I./src/includes	\
	--coverage -lcriterion				\

tests_run: unit_tests
	./unit_tests

clean_tests:
	$(RM) unit_tests
	rm *.gcda && rm *.gcno

re: fclean all
