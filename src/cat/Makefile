#
# Copyright (с) 2022 Student of School 21:
# Yonn Argelia
#
# yonnarge@student.21-school.ru
#

#------------------------------------------------------------------
NAME		:= s21_cat
#------------------------------------------------------------------
UTILITY		:= $(NAME)
#------------------------------------------------------------------
HEADER		:= $(NAME).h
#------------------------------------------------------------------
TEST_FILE	:= test_s21_cat.sh
#------------------------------------------------------------------
CC			:= gcc
#------------------------------------------------------------------
CFLAGS		:= -std=c11 -pedantic -Wall -Werror -Wextra
#------------------------------------------------------------------
SRC			:= $(NAME).c
#------------------------------------------------------------------
OBJ			:= $(SRC:.c=.o)
#------------------------------------------------------------------

.PHONY: all s21_cat test lint clean fclean re

all: s21_cat

#------------------------------------------------------------------
info:
		@echo "Available make targets:"
		@echo "  s21_cat: create the executable file s21_cat"
		@echo "  test:    run the functional test of the programm"
		@echo "  lint:    converts the code to the required style"
		@echo "  clean:   remove generated files without the executable file s21_cat"
		@echo "  fclean:  remove all generated files"
		@echo "  re:      remove all generated files and recompile the programm"
#------------------------------------------------------------------
s21_cat: $(OBJ)
		$(CC) $(CFLAGS) $(NAME).c -o $(UTILITY)
#------------------------------------------------------------------
%.o: %.c $(HEADER)
		$(CC) $(CFLAGS) -c $< -o $@
#------------------------------------------------------------------
test: $(NAME)
		bash ./$(TEST_FILE)
#------------------------------------------------------------------
lint: $(NAME)
		clang-format -i $(SRC) $(HEADER)
#------------------------------------------------------------------
clean:
		rm -rf $(OBJ) log.txt
#------------------------------------------------------------------
fclean: clean
		rm -rf $(NAME)
#------------------------------------------------------------------
re:
		$(MAKE) fclean
		$(MAKE) all
#------------------------------------------------------------------
