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

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_SIZE 1024

extern int errno;

typedef struct {
  char v;
  char i;
  char o;
  char l;
  char n;
  char c;
  char e;
  char f;
  char s;
  char h;
} Options;

enum error_codes {
  STOP = -1,
  OK = 0,
  NO_MATCHES_FOUND = 1,
  ERROR = 2,
};

enum option_codes {
  CLEAR = 0,
  SET = 1,
  HELP = 2,
};

int init_struct(Options *Opt, int symbol, char *pattern);
void init_pattern(char *pattern, const char *src);

int executor(const char **argv, const char *pattern, Options *Opt);
int file_handler(const char **argv, const char *pattern, int num_files,
                 int flag_no_pattern_opt, Options *Opt);
int file_counter(const char **argv, int flag_no_pattern_opt);
void opt_handler(const char **argv, int index_file_arg, int num_files,
                 int num_str, char *buff_str, Options *Opt);

void n_handler(int num_str, Options *Opt);
int f_handler(char *pattern);

#endif  // SRC_GREP_S21_GREP_H_
