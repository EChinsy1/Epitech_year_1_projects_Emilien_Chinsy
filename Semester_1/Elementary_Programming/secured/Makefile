## EPITECH PROJECT, 2025
## Makefile
## File description:
## makefile for the my_ls project
##

CC    =    epiclang

SRC_TEST    =    main.c    \
                src/hash.c    \
                src/hashtable_creation.c    \
                src/list.c    \

SRC    =    src/hash.c    \
        lib/my/my_strlen.c    \
        lib/my/my_calloc.c    \
		lib/my/my_put_nbr.c		\
		lib/my/my_putchar.c	\
		lib/my/my_strcpy.c	\
		lib/my/my_strdup.c	\
        src/hashtable_creation.c    \
        src/list.c

OBJ    =    $(SRC:.c=.o)

OBJ_TEST =    $(SRC_TEST:.c=.o)

NAME    =    libhashtable.a

NAME_TEST    =    secured

CFLAGS = -iquote./includes/

LDFLAGS	=	-L./lib/my/

LDLIBS	=	-lmy

CFLAGS = -iquote ./includes/

LDFLAGS    =    -L./lib/my/

LDLIBS    =    -lmy

all:    $(NAME)

$(NAME):    $(OBJ)
	cd lib/my/ && make re
	ar rc $(NAME) $(OBJ)

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
