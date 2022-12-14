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

#define SIZE 1024

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

int executor(const char **argv, const char *pattern, Options const *Opt);
int file_handler(const char **argv, const char *pattern, int num_files,
                 int flag_no_pattern_opt, Options const *Opt);
int file_counter(const char **argv, int flag_no_pattern_opt);
int opt_handler(const char *file_name, int num_files,
								 int num_str,  char *buf_str, const char *pattern, Options const *Opt);

void n_handler(Options const *Opt, int num_str);
int f_handler(char *pattern);
void c_handler(Options const *Opt, int num_files, const char *file_name,
               unsigned int num_matching_strings);

int o_handler(Options const *Opt, char *buffer, const char *pattern);


#endif  // SRC_GREP_S21_GREP_H_
