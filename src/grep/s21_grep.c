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

int file_handler(const char **argv, char *pattern, int num_files);
int file_counter(const char **argv);

// void flag_handler();

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

      if (errcode == OK) {
				int num_files = 0;

				num_files = file_counter((const char **)argv);
        file_handler((const char **)argv, pattern, num_files);
      }
    }
  }

  if (NULL != pattern) free(pattern);

  return (errcode);
}

// void flag_handler() {}

int file_counter(const char **argv) {
	int num_files = 0;

	for (int i = optind; NULL != argv[i]; ++i) {
		if (argv[i][0] != '-') {
			num_files += 1;
		}
	}

	return (num_files);
}

int file_handler(const char **argv, char *pattern, int num_files) {
  int errcode = OK;

	for (int index_loop = 0; index_loop < num_files; ++index_loop) {
		FILE *file;
		int index_file_arg = optind + index_loop;
		const char *file_name = argv[index_file_arg];

		if (NULL == (file = fopen(file_name, "r"))) {
			printf("s21_grep: %s: No such file or directory\n", file_name);
			errcode = STOP;
		} else {
			regex_t reg;

			regcomp(&reg, pattern, REG_EXTENDED);


			char buff_string[BUFF_SIZE] = {0};

			while (NULL != fgets(buff_string, BUFF_SIZE, file)) {
				if (0 == regexec(&reg, buff_string, 0, NULL, 0)) {
					if (num_files > 1)
						printf("%s:", argv[index_file_arg]);
					fputs(buff_string, stdout);
				}
			}

			regfree(&reg);
		}
	}

  return (errcode);
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
