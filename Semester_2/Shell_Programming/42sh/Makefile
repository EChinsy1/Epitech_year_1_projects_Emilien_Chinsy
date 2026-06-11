## EPITECH PROJECT, 2025
## Makefile
## File description:
## makefile for the my_ls project
##

CC    :=    epiclang

BACKTICKS = backticks.c	\
			backtick_word_array.c

EXEC	=	pipe.c			\
		exec_tree.c		\
		redirections.c		\
		redirections_extra.c	\
		handle_signals.c

SCRIPTING	=	scripting.c \
			    repeat.c \
				foreach.c \
				where.c	\
				which.c	\

BUILTINS =	exit.c			\
		cd.c			\
		setenv.c		\
		set.c			\
		unsetenv.c		\
		env.c			\
		alias.c			\
		pipe.c			\
		shrek.c			\
		prompt.c 		\

JOBS	=	find_separator.c	\
		job_struct.c		\
		builtins.c		\
		percentage_handler.c	\
		handler_functions.c	\
		update_jobs.c		\

GET_DIRECTORY_TO_EXEC =		get_directory_to_exec.c

TREE	=	tree_funcs.c	\
			validate_trees.c

HISTORY	=	history.c					\
			history_exclamation_mark.c 	\

GLOBBINGS = globbings.c

INPUT	=	my_getline.c	\
		arrows.c	\
		autocompletion.c \
		control.c \
		parse_fptr.c \
		del_keys.c		\

SRC_FILES =	my_sh_parsing_tree.c							\
		minishell.c								\
		$(addprefix scripting/, $(SCRIPTING))						\
		$(addprefix exec/, $(EXEC))						\
		$(addprefix builtins/, $(BUILTINS))					\
		$(addprefix get_directory_to_exec/, $(GET_DIRECTORY_TO_EXEC))		\
		$(addprefix tree/, $(TREE))						\
		$(addprefix history/, $(HISTORY))					\
		$(addprefix globbings/, $(GLOBBINGS))					\
		$(addprefix jobs/, $(JOBS))						\
		$(addprefix backticks/, $(BACKTICKS))					\
		$(addprefix input/, $(INPUT))						\


TEST_SRC =	$(addprefix src/, $(SRC_FILES))		\

SRC    =	$(addprefix src/, $(SRC_FILES))						\
		src/main.c

TEST_OBJ =	$(TEST_SRC:.c=.o)

OBJ    =	$(SRC:.c=.o)


NAME    =    42sh

NAME_TEST    =    42sh_tests

CFLAGS = -iquote./includes/

LDFLAGS	=	-L./lib/my/

LDLIBS	=	-lmy

all:    $(NAME)

$(NAME):    $(OBJ)
	cd lib/my/ && make
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS) -L./lib/my/ -lmy $(LDLIBS)

make_to_test:    $(OBJ)
	cd lib/my/ && make re
	$(CC) -o $(NAME_TEST) $(OBJ) $(CFLAGS) -L./lib/my/ -lmy

unit_tests: fclean $(TEST_OBJ)
	cd lib/my/ && make re
	$(CC) -o unit_tests $(TEST_OBJ) $(CFLAGS) $(LDFLAGS) $(LDLIBS) --coverage -lcriterion

tests_run: unit_tests
	./unit_tests

clean_tests:
	$(RM) unit_tests
	$(RM) *.gcda && $(RM) *.gcno

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)
	cd lib/my/ && make fclean

re: fclean all
