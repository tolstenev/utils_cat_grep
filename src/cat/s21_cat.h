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
#include <stdbool.h>

typedef struct {
  int b;
  int e;
  int n;
  int s;
  int t;
} Options;

enum {
  OK = 0,
  ERROR = 1,
  NO_SUCH_FILE = 2,
};

int s21_print_file(FILE *file, Options *Opt);
int s21_file_is_exist(FILE *file);

#endif  // SRC_CAT_S21_CAT_H_


