##
## EPITECH PROJECT, 2026
## Makefile
## File description:
## stumper 1
##

SRC	=	main.c	\
		sort_word_array.c

OBJ	=	$(SRC:.c=.o)

NAME	=	sort_words

all:	$(NAME)

$(NAME):	$(OBJ)
	epiclang -o $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
