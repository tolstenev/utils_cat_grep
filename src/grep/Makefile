#
# Copyright (с) 2022 Student of School 21:
# Yonn Argelia
#
# yonnarge@student.21-school.ru
#

NAME		:= s21_grep
UTILITY		:= $(NAME)
HEADER		:= $(NAME).h
TEST_FILE	:= test_$(NAME).sh

CC			:= gcc
CFLAGS		:= -std=c11 -pedantic -Wall -Werror -Wextra
SRC			:= $(NAME).c
OBJ			:= $(SRC:.c=.o)

.PHONY: all s21_grep test lint clean fclean re

all: s21_grep

s21_grep: $(OBJ)
		$(CC) $(CFLAGS) $(NAME).c -o $(UTILITY)

%.o: %.c $(HEADER)
		$(CC) $(CFLAGS) -c $< -o $@

test: $(NAME)
		bash ./$(TEST_FILE)

lint: $(NAME)
		@echo ---------------------CPPCHECK---------------------
		cppcheck --enable=all --suppress=missingIncludeSystem . $(HEADER) $(SRC)
		@echo -------------------CLANG-FORMAT-------------------
		clang-format -i $(SRC) $(HEADER)
clean:
		rm -rf $(OBJ) _traces/

fclean: clean
		rm -rf $(NAME)

re:
		$(MAKE) fclean
		$(MAKE) all
