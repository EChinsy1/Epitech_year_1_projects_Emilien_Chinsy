## EPITECH PROJECT, 2025
## Makefile
## File description:
## makefile for the my_ls project
##

CC    =    epiclang -g

SRC    =    src/builtins/env.c	\
			src/builtins/exit.c	\
			src/builtins/cd.c	\
			src/builtins/setenv.c	\
			src/builtins/unsetenv.c	\
			src/history/history.c	\
			src/exec/exec_tree.c	\
			src/exec/pipe.c			\
			src/exec/redirections.c \
			src/exec/handle_signals.c	\
			src/get_directory_to_exec/get_directory_to_exec.c	\
			src/my_sh_parsing_tree.c	\
			src/tree/tree_funcs.c		\
			src/main.c			\

OBJ    =    $(SRC:.c=.o)


NAME    =    mysh

NAME_TEST    =    secured

CFLAGS = -iquote./includes/

LDFLAGS	=	-L./lib/my/

LDLIBS	=	-lmy

all:    $(NAME)

$(NAME):    $(OBJ)
	cd lib/my/ && make re
	epiclang -o $(NAME) $(OBJ) $(CFLAGS) -L./lib/my/ -lmy

make_to_test:    $(OBJ)
	cd lib/my/ && make re
	epiclang -o $(NAME_TEST) $(OBJ) $(CFLAGS) -L./lib/my/ -lmy

unit_tests: re
	epiclang -o unit_tests $(SRC) \
	tests/test_secured.c $(CFLAGS) \
	$(LDFLAGS) $(LDLIBS) \
	--coverage -lcriterion	\

tests_run: unit_tests
	./unit_tests

clean_tests:
	$(RM) unit_tests
	rm .gcda && rm.gcno


clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
