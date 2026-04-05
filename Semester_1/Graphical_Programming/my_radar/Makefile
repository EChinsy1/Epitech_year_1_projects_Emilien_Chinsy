#
## EPITECH PROJECT, 2025
## Makefile
## File description:
## makefile for the my_ls project
##

CC	+=	epiclang

SRC	=	src/entity_handling/parsing.c	\
		src/events/events.c		\
		src/entity_handling/drawing.c	\
		src/collisions/collisions.c	\
		src/collisions/quad_tree.c	\
		src/other/text.c		\
		src/other/my_add_nbr.c		\
		src/entity_handling/sprites.c	\
		src/entity_handling/read.c	\
		src/main_game/main.c

OBJ	=	$(SRC:.c=.o)

NAME	=	my_radar

CFLAGS = -I./includes/ 

all:	$(NAME)

$(NAME):	$(OBJ)
	cd lib/my/ && make re
	epiclang -o $(NAME) $(OBJ) $(CFLAGS) -L./lib/my/ -lmy -lcsfml-graphics -lcsfml-system -lcsfml-audio -lcsfml-window -lm

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
