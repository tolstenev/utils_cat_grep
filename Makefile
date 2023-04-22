#
# Copyright 2023 Gleb Tolstenev
# yonnarge@student.21-school.ru
#
# Makefile for utils_cat_grep project
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

.PHONY: all test lint clean fclean re

all: s21_cat s21_grep


#------------------------------------------------------------------
s21_cat:
		cd src/cat && make s21_cat
#------------------------------------------------------------------
s21_grep:
		cd src/grep && make s21_grep
#------------------------------------------------------------------
test:
		cd src/cat && make test
		cd src/grep && make test
#------------------------------------------------------------------
lint:
		clang-format -i ./*/*/*.c ./*/*/*.h
#------------------------------------------------------------------
clean:
		cd src/cat && make clean
		cd src/grep && make clean
#------------------------------------------------------------------
fclean: clean
		cd src/cat && make fclean
		cd src/grep && make fclean
#------------------------------------------------------------------
