##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## 107transfer
##

MAIN =	main.c

SRC =	main.c

TEST_SRC =	tests/tests_utilities.c \
		tests/tests_amazed.c

OBJ = $(MAIN:.c=.o)

NAME = 107transfer

CPPFLAGS = -lm

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
