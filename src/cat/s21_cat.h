/*
 * Copyright 2023 Gleb Tolstenev
 * yonnarge@student.21-school.ru
 *
 * s21_cat.h is the header file for s21_cat utility
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

#include <stdio.h>
#include <string.h>

typedef struct {
  char b;
  char e;
  char n;
  char s;
  char t;
  char v;
} Options;

enum error_codes {
  OK = 0, /* Корректное завершение работы */
  ERROR = 1, /* Выявлены ошибки или недоступные файлы */
  STOP = 2, /* Работа программы была остановлена для вывода информации по
               использованию */
};

enum option_codes {
  CLEAR = 0,
  SET = 1,
  HELP = 2,
};

enum position_codes { IS_BEGIN = 0, IS_MID = 1 };

int file_exist(FILE *file);
int parser(int argc, char **argv, Options *Opt);
int file_handler(char *file_name, Options *Opt);
void b_handler(FILE *file, const int *c, Options *Opt, unsigned int *num_str,
               const char *position);
void n_handler(FILE *file, const int *c, Options *Opt, unsigned int *num_str);
void s_handler(FILE *file, int *c, Options *Opt, unsigned int *num_str,
               char *position);
void s_opt_handler(FILE *file, int *fut_c, int *c, Options *Opt,
                   unsigned int *num_str, const char *position);
void v_handler(int *c, Options *Opt);
void t_handler(int *c, Options *Opt);
void e_handler(int *c, Options *Opt);

#endif  // SRC_CAT_S21_CAT_H_
