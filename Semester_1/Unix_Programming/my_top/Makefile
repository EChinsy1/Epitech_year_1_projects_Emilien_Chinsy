##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## task 01 of cpool Day10
##

MAIN =	src/main.c

SRC =	src/top.c \
	src/get_all_users.c \
	src/get_from_proc/get_load_average.c \
	src/files.c \
	src/tui/display_procs.c \
	src/tui/display_sys.c \
	src/tui/tui_init.c \
	src/tui/tui_loop.c \
	src/get_from_proc/get_uptime.c \
	src/get_from_proc/get_num_users.c \
	src/get_from_proc/get_cpu_stats.c \
	src/get_from_proc/get_in_pid_folders.c \
	src/get_from_proc/get_from_mem_info.c \
	src/get_from_proc/get_systime.c \
	src/window_functions/scroll.c \
	src/window_functions/kill.c \
	src/window_functions/cycle_units.c \
	src/tui/sort.c

OBJ = $(SRC:.c=.o) $(MAIN:.c=.o)

NAME = my_top

CPPFLAGS = -I include/

all:	$(NAME)

$(NAME):	$(OBJ)
	epiclang -o $(NAME) $(OBJ) $(CPPFLAGS) -lncurses -lm

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
