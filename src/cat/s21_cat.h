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
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
} Options;

enum {
  OK = 0,
  ERROR = 1,
  STOP = 2,
};

enum {
  CLEAR = 0,
  SET = 1,
  HELP = 2,
};

int s21_print_file(char *file_name, Options *Opt);
int s21_file_is_exist(FILE *file);

#endif  // SRC_CAT_S21_CAT_H_



