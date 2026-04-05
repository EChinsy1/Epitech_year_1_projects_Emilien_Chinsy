#
## EPITECH PROJECT, 2025
## Makefile
## File description:
## makefile for the my_ls project
##

CC += epiclang

SRC	=	src/main_game/display_window.c		\
		src/events/events_buttons.c		\
		src/events/events.c			\
		src/entity_handling/sprites.c		\
		src/drawing/animations.c		\
		src/entity_handling/death.c		\
		src/main_game/game_functions.c		\
		src/drawing/draw_cursor.c		\
		src/drawing/draw_birds.c		\
		src/entity_handling/entity_handling.c	\
		src/entity_handling/movements.c		\
		src/drawing/text.c			\
		src/main_game/end_game.c		\
		src/help/show_help.c			\
		src/main_game/my_add_nbr.c		\
		src/main_game/between_levels.c		\
		src/drawing/save_score.c

OBJ	=	$(SRC:.c=.o)

NAME	=	my_hunter

CFLAGS	=	-I./src/includes

all:	$(NAME)

$(NAME):	$(OBJ)
	cd lib/my/ && make re && cd ../..
	epiclang -o $(NAME) $(OBJ) $(FLAGS) -lcsfml-graphics -lcsfml-system -lcsfml-audio -lcsfml-window -L./lib/my -lmy

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
