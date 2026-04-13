##
## EPITECH PROJECT, 2026
## Makefile
## File description:
## Makefile for robot factory
##

NAME		=	robot-factory

SRC			=	src/op.c	\
				src/parsing.c	\
				src/main.c		\
				src/write_functions/write_in_file.c \
				src/write_functions/write_cmd_cod_byte.c \
				src/write_functions/write_types.c \
				src/free_funcs/free_funcs.c \
				lib/my_putstr.c \
				lib/my_strlen.c	\
				lib/my_strncat.c \
				lib/my_strcat.c \
				lib/my_strcmp.c \
				lib/my_strncmp.c \
				lib/my_calloc.c \
				lib/my_getnbr.c \
				lib/my_str_to_word_array.c \
				lib/my_strdup.c \

OBJ			=	$(SRC:.c=.o)

DEBUG_F 	= -g3 -Wall -Wextra

CPPFLAGS 	=  -iquote ./include

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

debug:	CPPFLAGS += $(DEBUG_F)
debug:	fclean all

.PHONY:	all	clean	fclean	re	debug
