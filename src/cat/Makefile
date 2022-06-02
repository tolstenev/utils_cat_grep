#
# Copyright (с) 2022 Student of School 21:
# Yonn Argelia
#
# yonnarge@student.21-school.ru
#

NAME		:= s21_cat
UTILITY		:= $(NAME)
CC			:= gcc
CFLAGS		:= -std=c11 -Wall -Werror -Wextra
TEST_FILE	:= ../../datasets/test_file1.txt

SRCS		:= s21_cat.c	\

OBJS		:= $(SRCS:.c=.o)

.PHONY: all s21_cat test check clean fclean re

all: s21_cat

s21_cat:
	@$(CC) $(CFLAGS) $(NAME).c -o $(UTILITY)


test: $(NAME)
#	@./$(NAME) ../../datasets/abcdef.txt
	@./$(NAME) ../../datasets/first.txt ../../datasets/second.txt
	@./$(NAME) ../../datasets/no_file.txt

check: $(NAME)
	@echo ---------------------CPPCHECK---------------------
	@cppcheck *.c
	@echo ---------------------CPPLINT----------------------
	@cp ../../materials/linters/CPPLINT.cfg CPPLINT.cfg
	@python3 ../../materials/linters/cpplint.py --extension=c *.c
	@rm CPPLINT.cfg

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all


