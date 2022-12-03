/**
 * Copyright (с) 2022 Student of School 21:
 * Yonn Argelia
 * yonnarge@student.21-school.ru
 *
 * The programm "s21_cat" implement the bash util 'cat'
 */

#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
  char b;
  char e;
  char n;
  char s;
  char t;
  char v;
} Options;

enum error_codes {
  OK = 0,
  ERROR = 1,
  STOP = 2,
};

enum option_codes{
  CLEAR = 0,
  SET = 1,
  HELP = 2,
};

enum position_codes {
  IS_BEGIN = 0,
  IS_MID = 1
};

void print_file(char *file_name, Options *Opt);
int file_exist(FILE *file);
int parser(int argc, char **argv, int errcode, Options *Opt);
void b_handler(FILE *file, int *c, Options *Opt, unsigned int *num_str, char *position);
void n_handler(FILE *file, int *c, Options *Opt, unsigned int *num_str);
void s_handler(FILE *file, int *c, Options *Opt, unsigned int *num_str, char *position);
void s_opt_handler(FILE *file, int *fut_c, int *c, Options *Opt, unsigned int *num_str, char *position);

#endif  // SRC_CAT_S21_CAT_H_



