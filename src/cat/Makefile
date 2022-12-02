#
# Copyright (с) 2022 Student of School 21:
# Yonn Argelia
#
# yonnarge@student.21-school.ru
#

NAME		:= s21_cat
HEADER		:= $(NAME).h
UTILITY		:= $(NAME)
TEST_FILE	:= e_cat.sh

CC			:= gcc
CFLAGS		:= -std=c11 -pedantic -Wall -Werror -Wextra
SRCS		:= $(NAME).c
OBJS		:= $(SRCS:.c=.o)

TEST_FILE	:= ../../datasets/test_file1.txt

.PHONY: all s21_cat test check clean fclean re

all: s21_cat

s21_cat: $(OBJS)
		$(CC) $(CFLAGS) $(NAME).c -o $(UTILITY)

%.o: %.c $(HEADER)
		$(CC) $(CFLAGS) -c $< -o $@

test: $(NAME)
		./TEST_FILE
		@#./$(NAME) ../../datasets/bytes.txt
#		@./$(NAME) ../../datasets/abcdef.txt
#		@./$(NAME) -n ../../datasets/abcdef.txt
#		@./$(NAME) ../../datasets/first.txt ../../datasets/second.txt
#		@./$(NAME) ../../datasets/no_file.txt

check: $(NAME)
		@clear
		@echo ---------------------CPPCHECK---------------------
		cppcheck --enable=all --suppress=missingIncludeSystem . $(HEADER) $(SRCS)
		@echo ---------------------CPPLINT----------------------
		cp ../../materials/linters/CPPLINT.cfg CPPLINT.cfg
		python3 ../../materials/linters/cpplint.py --extension=c $(SRCS) $(HEADER)
		rm CPPLINT.cfg

clean:
		rm -rf $(OBJS) *.txt

fclean: clean
		rm -rf $(NAME)

re:
		$(MAKE) fclean
		$(MAKE) all


