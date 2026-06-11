##
## EPITECH PROJECT, 2025
## 103cipher
## File description:
## makefile for 103cipher
##

NAME = 110borwein

all: $(NAME)

$(NAME):
	cargo build
	mv target/debug/$(NAME) ./

clean:
	cargo clean

fclean: clean
	rm -f $(NAME)

tests_run:
	cargo test

re: fclean all

.PHONY:	$(NAME)
	clean
	fclean
	tests_run
