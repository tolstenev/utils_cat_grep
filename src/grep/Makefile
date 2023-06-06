#
# Copyright 2023 Gleb Tolstenev
# yonnarge@student.21-school.ru
#
# Makefile for s21_grep utility
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

NAME		:= s21_grep
CC			:= gcc
CFLAGS		:= -std=c11 -pedantic -Wall -Werror -Wextra
SRC			:= $(NAME).c
HEADER		:= $(NAME).h
TEST_FILE	:= functional_test_s21_grep.sh

all: s21_grep

info:
		@echo "Available make targets:"
		@echo "  s21_grep: create the executable file s21_grep"
		@echo "  test:     run the functional test of the programm"
		@echo "  lint:     converts the code to the required style"
		@echo "  clean:    remove all generated files"
		@echo "  re:       remove all generated files and recompile the programm"

s21_grep: $(SRC) $(HEADER)
		$(CC) $(CFLAGS) $(SRC) -o $(NAME)
test: $(NAME)
		bash $(TEST_FILE)
clean:
		rm -rf $(NAME) *.log pattern.file empty.file lyrics.txt lyrics2.txt logs/
re:
		$(MAKE) clean
		$(MAKE) all
