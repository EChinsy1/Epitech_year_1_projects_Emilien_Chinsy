## EPITECH PROJECT, 2025
## Makefile
## File description:
## makefile for the my_ls project
##

SRC_TEST    =    bombyx.c    \

SRC    =    main.c	\
	    bombyx.c

OBJ    =    $(SRC:.c=.o)

OBJ_TEST =    $(SRC_TEST:.c=.o)

NAME    =    106bombyx

NAME_TEST    =    unit_tests

CFLAGS = -iquote./includes/

CFLAGS = -iquote ./includes/

LDFLAGS    =    -L./lib/my/

LDLIBS    =    -lmy

all:    $(NAME)

$(NAME):    $(OBJ)
	epiclang -o $(NAME) $(OBJ)

unit_tests: re
	epiclang -o unit_tests $(SRC_TEST) \
	tests/tests_bombyx.c $(CFLAGS) \
	--coverage -lcriterion	\

tests_run: unit_tests
	./unit_tests

clean_tests:
	$(RM) unit_tests
	rm *.gcda && rm *.gcno


clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
