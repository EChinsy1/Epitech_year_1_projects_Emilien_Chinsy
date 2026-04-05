## EPITECH PROJECT, 2025
## Makefile
## File description:
## makefile for the my_ls project
##

SRC_TEST    =    src/builtins/env.c	\
			src/builtins/exit.c	\
			src/builtins/cd.c	\
			src/builtins/setenv.c	\
			src/builtins/unsetenv.c	\
			src/exec/exec.c	\
			src/get_directory_to_exec/get_directory_to_exec.c	\
			src/main.c			\

SRC    =    src/builtins/env.c	\
			src/builtins/exit.c	\
			src/builtins/cd.c	\
			src/builtins/setenv.c	\
			src/builtins/unsetenv.c	\
			src/exec/exec.c	\
			src/get_directory_to_exec/get_directory_to_exec.c	\
			src/main.c			\

OBJ    =    $(SRC:.c=.o)

OBJ_TEST =    $(SRC_TEST:.c=.o)

NAME    =    mysh

NAME_TEST    =    secured

CFLAGS = -iquote./includes/

LDFLAGS	=	-L./lib/my/

LDLIBS	=	-lmy

all:    $(NAME)

$(NAME):    $(OBJ)
	cd lib/my/ && make re
	epiclang -o $(NAME) $(OBJ_TEST) $(CFLAGS) -L./lib/my/ -lmy

make_to_test:    $(OBJ_TEST)
	cd lib/my/ && make re
	epiclang -o $(NAME_TEST) $(OBJ_TEST) $(CFLAGS) -L./lib/my/ -lmy

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
