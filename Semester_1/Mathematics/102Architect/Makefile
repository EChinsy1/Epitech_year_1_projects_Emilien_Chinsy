##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## Makefile
##

SRC =	src/main.c			\
	src/math_part_one.c		\
	src/math_part_two.c		\
	src/checks_and_start.c

SRC_T	=	src/math_part_one.c		\
		src/math_part_two.c		\
		src/checks_and_start.c

OBJ :=	$(SRC:.c=.o)

NAME = 102architect

CFLAGS = -lm -I./src/includes

all: $(NAME)

$(NAME):	$(OBJ)
	epiclang -o $(NAME) $(OBJ) $(CFLAGS)

clean:
	$(RM) $(OBJ)

unit_tests: all
	epiclang -o unit_tests					\
		$(SRC_T) $(CFLAGS) tests/test_architect.c	\
	-lm --coverage -lcriterion				\

tests_run: unit_tests
	./unit_tests

clean_tests:
	$(RM) unit_tests
	rm *.gcda && rm *.gcno

fclean: clean
	$(RM) $(NAME)

re: fclean all
