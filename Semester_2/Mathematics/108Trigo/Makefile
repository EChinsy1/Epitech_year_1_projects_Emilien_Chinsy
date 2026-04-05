##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## 108trigo
##

MAIN =	src/main.c

SRC =	src/lib_matrix.c \
		src/exponential.c \
		src/sin.c \
		src/cos.c \
		src/sinh.c \
		src/cosh.c \

TEST_SRC =	tests/tests_utilities.c \
		tests/tests_amazed.c

OBJ = $(MAIN:.c=.o) $(SRC:.c=.o)

NAME = 108trigo

CPPFLAGS = -iquote ./include -lm

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(CPPFLAGS)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

unit_tests: fclean
	epiclang -o unit_tests $(TEST_SRC) $(SRC) $(CPPFLAGS) --coverage -lcriterion

tests_run: unit_tests
	./unit_tests

.PHONY: all $(NAME) clean fclean re
