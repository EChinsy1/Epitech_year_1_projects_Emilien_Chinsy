#
## EPITECH PROJECT, 2025
## Makefile
## File description:
## makefile for the my_ls project
##

SRC	=	src/make_map/make_map.c\
		src/make_map/load_map.c\
		src/main.c\
		src/events/click_n_hover.c\
		src/events/events.c\
		src/cam.c\
		src/game_struct.c\
		src/get_user_input/get_user_input.c\
		src/elements/buttons.c\
		src/elements/text.c\
		src/transformation.c\
		src/make_map/painter_algo.c

OBJ	=	$(SRC:.c=.o)

NAME	=	my_world

CFLAGS = -iquote ./includes

all:	$(NAME)

$(NAME):	$(OBJ)
	epiclang -o $(NAME) $(OBJ) $(FLAGS) -lcsfml-graphics -lcsfml-system -lcsfml-audio -lcsfml-window -lm

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
