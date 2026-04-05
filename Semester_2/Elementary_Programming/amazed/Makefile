##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## task 01 of cpool Day10
##

MAIN =	src/main.c

SRC =	src/amazed.c\
	src/display_input_results.c\
	src/free_int_array.c\
	src/my_string/my_strlen.c\
	src/my_string/my_str_to_wordarr.c\
	src/my_string/my_putwordarr.c\
	src/my_string/my_strdup.c\
	src/my_string/my_strcmp.c\
	src/my_string/my_calloc.c\
	src/my_string/my_wordarr_dup.c\
	src/my_string/my_strncmp.c\
	src/my_string/my_strcat.c\
	src/my_string/my_strndup.c\
	src/my_string/my_len_deli.c\
	src/my_string/my_getnbr.c\
	src/my_string/my_len_nbr.c\
	src/my_string/mini_printf.c\
	src/my_string/is_number.c\
	src/prints/my_putstr.c\
	src/prints/my_putnbr.c\
	src/intake/getinputs.c\
	src/intake/get_input_util.c\
	src/intake/getliaison.c\
	src/intake/matrix.c\
	src/intake/graph_room.c\
	src/algorithm/bfs.c

TEST_SRC =	tests/tests_utilities.c \
		tests/tests_amazed.c

OBJ = $(SRC:.c=.o) $(MAIN:.c=.o)

NAME = amazed

CPPFLAGS = -I include/

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
