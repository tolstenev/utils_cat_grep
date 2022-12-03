#
# Copyright (с) 2022 Student of School 21:
# Yonn Argelia
#
# yonnarge@student.21-school.ru
#

NAME		:= s21_cat
UTILITY		:= $(NAME)
HEADER		:= $(NAME).h
TEST_FILE	:= e_cat.sh

CC			:= gcc
CFLAGS		:= -std=c11 -pedantic -Wall -Werror -Wextra
SRC			:= $(NAME).c
OBJ			:= $(SRC:.c=.o)

.PHONY: all s21_cat test check clean fclean re

all: s21_cat

s21_cat: $(OBJ)
		$(CC) $(CFLAGS) $(NAME).c -o $(UTILITY)

%.o: %.c $(HEADER)
		$(CC) $(CFLAGS) -c $< -o $@

test: $(NAME)
		./$(TEST_FILE)

lint: $(NAME)
		@echo ---------------------CPPCHECK---------------------
		cppcheck --enable=all --suppress=missingIncludeSystem . $(HEADER) $(SRC)
		@echo -------------------CLANG-FORMAT-------------------
		clang-format -i $(SRC) $(HEADER)
clean:
		rm -rf $(OBJ) *.txt

fclean: clean
		rm -rf $(NAME)

re:
		$(MAKE) fclean
		$(MAKE) all
