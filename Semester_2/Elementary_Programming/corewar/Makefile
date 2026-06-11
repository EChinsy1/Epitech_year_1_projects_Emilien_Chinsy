##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## Makefile for solo_stumper1
##

SRC_DIR	=	src/

COMMAND_DIR = commands/

COMMANDS	=	add.c \
				and.c \
				fork.c \
				ld.c \
				ldi.c \
				live.c \
				lld.c \
				lldi.c \
				or.c \
				print.c \
				st.c \
				sti.c \
				sub.c \
				xor.c \
				zjmp.c \
				lfork.c \

FILES	=	corewar.c	\
		parsing.c	\
		parsing_file.c	\
		gameplay.c \
		gameplay_utils.c	\
		op.c \
		dump.c \

SRC	=	$(addprefix $(SRC_DIR), $(FILES))	\
		$(addprefix $(SRC_DIR)$(COMMAND_DIR), $(COMMANDS))	\
		$(addprefix $(SRC_DIR), main.c)

OBJ 	=	$(SRC:.c=.o)

CC 	:=	epiclang

CFLAGS 	+= 	-Wall -Wextra

CPPFLAGS +=	-iquote ./include/

LDFLAGS  +=	-L./lib/my -lmy

NAME 	= 	corewar

all:	$(NAME)

$(NAME): $(OBJ)
	$(MAKE) -j -C lib/my
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	$(MAKE) clean -C lib/my
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re:	fclean all

multi:	fclean
	$(MAKE) -j

.PHONY: all clean fclean re multi
