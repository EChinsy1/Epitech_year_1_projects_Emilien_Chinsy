## EPITECH PROJECT, 2026
## G2 - Discovery of Data Analysis - Cuddle - Alexis & Emilien
## File description:
## makefile for the cuddle project
##

CC		=	epiclang

SRC		=	src/bool_detection_tools.c						\
			src/destroy_functions.c							\
			src/tools_functions.c							\
			src/basic_operations/basics_operations.c		\
			src/basic_operations/df_head.c					\
			src/basic_operations/df_tail.c					\
			src/advanced_operations/filter.c				\
			src/advanced_operations/sort.c					\
			src/advanced_operations/aggregation.c			\
			src/advanced_operations/apply.c					\
			src/advanced_operations/convert_tools.c			\
			src/advanced_operations/convertion.c			\
			src/utilities/df_get_value.c					\
			src/utilities/df_get_values.c					\
			src/utilities/df_get_unique_values.c			\
			src/read_csv.c									\
			src/write_csv.c

TSRC	=	tests/tests_read_write.c						\
			tests/tests_basics_operations.c					\
			tests/tests_advanced_operations.c				\
			tests/tests_error_handling_basics.c				\
			tests/tests_error_handling_adv.c				\
			tests/tests_utilities.c

NAME    =	'libcuddle.a'

MAIN	=	tests/main.c

OBJ		=    $(SRC:.c=.o)

TOBJ	=	$(TSRC:.c=.o)

LNAME	=	'cuddle'

MNAME	=	'cuddle'

CFLAGS	=	-iquote ./include/

CPPFLAGS=	-lm

all: $(NAME)

$(NAME):    $(OBJ)
	ar rc $(NAME) $(OBJ)

re: fclean all

clean:
	$(RM) -f $(OBJ) $(TOBJ)

fclean: clean
	$(RM) -f $(NAME)

build_main: $(MOBJ) all
		$(CC) $(MAIN) -o $(MNAME) -L ./ -l $(LNAME) $(CFLAGS) $(CPPFLAGS)

runmain: build_main
		$(RM) data_*.csv
		./$(MNAME)

unit_tests: CC = gcc
unit_tests: all $(TOBJ)
	$(CC) -o unit_tests $(SRC) $(TOBJ) $(CFLAGS) $(CPPFLAGS) --coverage -lcriterion

tests_run: unit_tests
	./unit_tests

tests_clean: fclean
	$(RM) -f unit_tests*

coverage: unit_tests
	echo "----code coverage----\n"
	gcovr --exclude tests/
	echo ""
	echo "----branches coverage----"
	gcovr --exclude tests/ --branches

debug: CPPFLAGS += -g
debug: fclean build_main
	gdb ./$(MNAME)

vdebug: CFLAGS += -g3
vdebug: fclean build_main
	valgrind --leak-check=full --track-origins=yes ./$(MNAME)

.PHONY: all $(NAME) re clean fclean build_main runmain unit_tests		\
		tests_run coverage tests_clean debug vdebug
