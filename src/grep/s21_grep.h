/**
 * Copyright (с) 2022 Student of School 21:
 * Yonn Argelia
 *
 * yonnarge@student.21-school.ru
 *
 * The programm "s21_grep" implement the bash util 'grep'
 */

#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#include <stdio.h>

enum error_codes {
  OK = 0,
  ERROR = 1,
  STOP = 2,
};

enum option_codes {
  CLEAR = 0,
  SET = 1,
  HELP = 2,
};


#endif  // SRC_GREP_S21_GREP_H_
