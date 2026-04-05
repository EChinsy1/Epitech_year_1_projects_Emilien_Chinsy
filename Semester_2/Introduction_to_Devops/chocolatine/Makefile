##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## Makefile
##

SRC_FILE 	=		lib.c

SRC		=		$(addprefix src/, $(SRC_FILE))		\
				src/main.c

SRC_T		=		$(addprefix src/, $(SRC_FILE))

OBJ		=		$(SRC:.c=.o)

NAME		=		Matchsticks

CFLAGS		=		-Wall -Wextra

CPPFLAGS 	=		-iquote ./include

CC		=		epiclang

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) -o $(NAME) $(OBJ) $(CPPFLAGS)

clean:
		$(RM) $(OBJ)
		$(RM) ./src/*~

fclean:	clean
		$(RM) ./$(NAME)

re:		fclean all

unit_tests: fclean $(NAME)
	epiclang -o unit tests/*.c $(CFLAGS) $(SRC_T) $(CPPLAGS) -I./include --coverage -lcriterion

tests_run: unit_tests
	./unit

cov: clean_test tests_run
	gcovr --gcov-executable "llvm-cov-20 gcov" --exclude tests/

clean_test:
	$(RM) *.gc* unit *.html *.css

.PHONY:	re clean fclean all
