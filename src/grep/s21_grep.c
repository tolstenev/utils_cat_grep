/**
 * Copyright (с) 2022 Student of School 21:
 * Yonn Argelia
 *
 * yonnarge@student.21-school.ru
 */

#include "s21_grep.h"

// Debug functions
// void print_options(Options *Opt);

int init_struct(Options *Opt, int symbol, char *pattern);
void init_e_pattern(char *pattern);

int executor(const char **argv, const char *pattern, Options *Opt);
int file_handler(const char **argv, const char *pattern, int num_files,
                 int flag_no_pattern_opt, Options *Opt);
int file_counter(const char **argv, int flag_no_pattern_opt);
void flag_handler(const char **argv, int index_file_arg, int num_files,
                  int num_str, char *buff_str, Options *Opt);

void n_handler(int num_str, Options *Opt);

int main(int argc, char **argv) {
  int errcode = OK;
  Options Opt = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  char *pattern = calloc(BUFF_SIZE, sizeof(char));

  if (NULL == pattern) errcode = STOP;

  if ((errcode == OK) && (argc > 2)) {
    int opt_symbol = 0;
    char *optstring = "violnce:f:sh?";

    while (-1 != (opt_symbol = getopt_long(argc, argv, optstring, 0, NULL))) {
      errcode = init_struct(&Opt, opt_symbol, pattern);

      if ((Opt.e || Opt.f) && (argc < 4)) errcode = ERROR;
    }
    if (errcode == OK) {
      executor((const char **)argv, pattern, &Opt);
    }
  }

  if (NULL != pattern) free((void *)pattern);

  return (errcode);
}

int executor(const char **argv, const char *pattern, Options *Opt) {
  int errcode = OK;
  int num_files = 0;
  int flag_no_pattern_opt = CLEAR;

  if (!Opt->e) {
    flag_no_pattern_opt = SET;
    pattern = argv[optind];
    num_files = file_counter(argv, flag_no_pattern_opt);
  } else {
    num_files = file_counter(argv, flag_no_pattern_opt);
  }
  errcode = file_handler(argv, pattern, num_files, flag_no_pattern_opt, Opt);
  return (errcode);
}

void flag_handler(const char **argv, int index_file_arg, int num_files,
                  int num_str, char *buff_str, Options *Opt) {
  if (num_files > 1) printf("%s:", argv[index_file_arg]);

  n_handler(num_str, Opt);
  fputs(buff_str, stdout);

  int n = strlen(buff_str);
  if (buff_str[n] == '\0' && buff_str[n - 1] != '\n') putchar('\n');
}

int file_counter(const char **argv, int flag_no_pattern_opt) {
  int num_files = 0;
  int ind = optind;

  if (flag_no_pattern_opt) ind += 1;

  for (int i = ind; NULL != argv[i]; ++i) {
    if (argv[i][0] != '-') {
      num_files += 1;
    }
  }

  return (num_files);
}

int file_handler(const char **argv, const char *pattern, int num_files,
                 int flag_no_pattern_opt, Options *Opt) {
  int errcode = OK;

  for (int index_loop = 0; index_loop < num_files; ++index_loop) {
    FILE *file;
    int index_file_arg = optind + index_loop + flag_no_pattern_opt;
    const char *file_name = argv[index_file_arg];

    if (NULL == (file = fopen(file_name, "r"))) {
      printf("s21_grep: %s: No such file or directory\n", file_name);
      errcode = STOP;
    } else {
      regex_t reg;

      regcomp(&reg, pattern, REG_EXTENDED);

      char *buff_str = calloc(BUFF_SIZE, sizeof(char));
      int num_str = 1;

      if (NULL == buff_str) errcode = STOP;

      if (errcode == OK) {
        while (NULL != fgets(buff_str, BUFF_SIZE, file)) {
          if (0 == regexec(&reg, buff_str, 0, NULL, 0)) {
            flag_handler(argv, index_file_arg, num_files, num_str, buff_str,
                         Opt);
          }
          ++num_str;
        }
      }

      if (NULL != buff_str) free(buff_str);

      regfree(&reg);
    }
  }

  return (errcode);
}

void n_handler(int num_str, Options *Opt) {
  if (Opt->n) printf("%d:", num_str);
}

void init_e_pattern(char *pattern) { strcpy(pattern, optarg); }

int init_struct(Options *Opt, int symbol, char *pattern) {
  int errcode = OK;

  switch (symbol) {
    case 'v':
      Opt->v = SET;
      break;
    case 'i':
      Opt->i = SET;
      break;
    case 'o':
      Opt->o = SET;
      break;
    case 'l':
      Opt->l = SET;
      break;
    case 'n':
      Opt->n = SET;
      break;
    case 'c':
      Opt->c = SET;
      break;
    case 'e':
      Opt->e = SET;
      init_e_pattern(pattern);
      break;
    case 'f':
      Opt->f = SET;
      break;
    case 's':
      Opt->s = SET;
      break;
    case 'h':
      Opt->h = SET;
      break;
    case '?':
      // Закомментил default, потому что пока не корректно работает без
      // обработки флага -е
      //		default:
      //			puts("s21_grep: unrecognized option");
      errcode = ERROR;
  }
  return (errcode);
}

// Отладочный вывод структуры с флагами
/*void print_options(Options *Opt) {
        printf("Opt.v = %u\n", Opt->v);
        printf("Opt.i = %u\n", Opt->i);
        printf("Opt.o = %u\n", Opt->o);
        printf("Opt.l = %u\n", Opt->l);
        printf("Opt.n = %u\n", Opt->n);
        printf("Opt.c = %u\n", Opt->c);
        printf("Opt.e = %u\n", Opt->e);
        printf("Opt.f = %u\n", Opt->f);
        printf("Opt.s = %u\n", Opt->s);
        printf("Opt.h = %u\n", Opt->h);
}*/

// Отладочный вывод переменных в main
/*
if (!errcode) {
                printf("optind = %d\n", optind);
                printf("file_name = %s\n", argv[optind]);
                printf("optarg = %s\n", optarg);
                printf("pattern = %s\n", pattern);
}*/
