/**
 * Copyright (с) 2022 Student of School 21:
 * Yonn Argelia
 *
 * yonnarge@student.21-school.ru
 *
 * The programm "s21_grep" implement the bash util 'grep'
 */

#include "s21_grep.h"

/**
 * @brief Инициализация возвращаемого кода ошибки, структуры опций, первичная
 * проверка входящих параметров
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char **argv) {
  int errcode = OK;
  Options Opt = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  char pattern[SIZE] = {0};

  if (argc > 2) {
    int opt_symbol = 0;
    char *optstring = "violnce:f:sh?";

    while (-1 != (opt_symbol = getopt_long(argc, argv, optstring, 0, NULL)))
      errcode = init_struct(&Opt, opt_symbol, pattern);

    if ((Opt.e || Opt.f) & (argc < 4)) errcode = ERROR;
    if ((!Opt.e && !Opt.f) & (argc < 3)) errcode = ERROR;

    if (OK == errcode) executor((const char **)argv, pattern, &Opt);
  }
  return (errcode);
}

/**
 * @brief Запускает выполнение всей работы программы
 * @param argv
 * @param pattern
 * @param Opt
 * @return
 */
int executor(const char **argv, const char *pattern, Options const *Opt) {
  int errcode = OK;
  int num_files = 0;
  int flag_no_pattern_opt = CLEAR;

  if (Opt->e || Opt->f) {
    num_files = file_counter(argv, flag_no_pattern_opt);
  } else {
    flag_no_pattern_opt = SET;
    pattern = argv[optind];
    num_files = file_counter(argv, flag_no_pattern_opt);
  }

  errcode = file_handler(argv, pattern, num_files, flag_no_pattern_opt, Opt);

  return (errcode);
}

/**
 * @brief Анализирует опции, с которыми была запущена программа
 * @param argv
 * @param ind_file_arg
 * @param num_files
 * @param num_str
 * @param buf_str
 * @param Opt
 */
int opt_handler(const char *file_name, int num_files,
                 int num_str, /*unsigned int num_matching_strings, */char *buf_str, const char *pattern, Options const *Opt) {
	int errcode = OK;

	if (!Opt->c) {
//		c_h_handler(Opt, num_files, file_name, num_matching_strings);
		if (num_files > 1 && !Opt->h) printf("%s:", file_name);
		n_handler(Opt, num_str);

		if (Opt->o && Opt->v == 0)
			errcode = o_handler(Opt, buf_str, pattern);
		else
			fputs(buf_str, stdout);

    int n = strlen(buf_str);
    if (buf_str[n] == '\0' && buf_str[n - 1] != '\n') putchar('\n');
  }
	return (errcode);
}

/**
 * @brief Обрабатывает поведение программы при опции '-o'
 * @param Opt
 * @param buf_str
 * @param pattern
 * @return
 */
int o_handler(Options const *Opt, char *buf_str, const char *pattern) {
	int errcode = OK;
	regex_t preg;
	regmatch_t pmatch[SIZE];
	int rc = 1;
	char reg_errbuf[128] = {0};
	char *s = buf_str;

	if (OK != (rc = Opt->i ? regcomp(&preg, pattern, REG_EXTENDED | REG_ICASE)
													: regcomp(&preg, pattern, REG_EXTENDED))) {
		regerror(rc, &preg, reg_errbuf, 128);
		fprintf(stderr, "Compilation failed: '%s'\n", reg_errbuf);
		errcode = ERROR;
		regfree(&preg);
	} else if (OK == rc && !Opt->v) {
		for (int i = 0; buf_str[i] != '\0'; ++i) {
			if (0 != regexec(&preg, s, 1, pmatch, 0)) {
				break;
			}
			if (Opt->f) pmatch[0].rm_eo += 1;
			printf("%.*s\n", (int)(pmatch[0].rm_eo - pmatch[0].rm_so),
						 s + pmatch[0].rm_so);
			s += pmatch[0].rm_eo;
		}
	}
	regfree(&preg);
	return (errcode);
}

/**
 * @brief Считает количество файлов, в которых будет проходить поиск.
 * @param argv
 * @param flag_no_pattern_opt
 * @return
 */
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

/**
 * @brief Обрабатывает файлы, в которых должен выполняться поиск
 * @param argv
 * @param pattern
 * @param num_files
 * @param flag_no_pattern_opt
 * @param Opt
 * @return
 */
int file_handler(const char **argv, const char *pattern, int num_files,
                 int flag_no_pattern_opt, Options const *Opt) {
  int errcode = OK;

  for (int index_loop = 0; index_loop < num_files; ++index_loop) {
    FILE *file_ptr;
    int ind_file_arg = optind + index_loop + flag_no_pattern_opt;
    const char *file_name = argv[ind_file_arg];
    unsigned int num_matching_strings = 0;

    if (NULL == (file_ptr = fopen(file_name, "r"))) {
			if (!Opt->s)
      	fprintf(stderr, "s21_grep: %s: %s\n", file_name, strerror(errno));
      errcode = STOP;
    } else {
      char buf_str[SIZE] = {0};
      char opt_l_handling_is = CLEAR;
      regex_t preg;
			int rc = 0;
			char reg_errbuf[128] = {0};

      if (OK != (rc = (Opt->i ? regcomp(&preg, pattern, REG_EXTENDED | REG_ICASE)
                             : regcomp(&preg, pattern, REG_EXTENDED)))) {
				regerror(rc, &preg, reg_errbuf, 128);
				fprintf(stderr, "Compilation failed: '%s'\n", reg_errbuf);
				errcode = ERROR;
				regfree(&preg);
			}

			if (OK == errcode) {
				for (int num_str = 1; NULL != fgets(buf_str, SIZE, file_ptr);
						 ++num_str) {
					if ((!Opt->v && (regexec(&preg, buf_str, 0, NULL, 0) == OK)) ||
						(Opt->v && (regexec(&preg, buf_str, 0, NULL, 0) != OK))) {
						if (Opt->c)
							Opt->l ? num_matching_strings = 1 : ++num_matching_strings;
						if (Opt->l) {
							opt_l_handling_is = SET;
						} else {
							errcode = opt_handler(file_name, num_files, num_str, /*num_matching_strings,*/ buf_str, pattern, Opt);
						}
					}
				}
			}

      if (Opt->c) c_handler(Opt, num_files, file_name, num_matching_strings);
//			c_h_handler(Opt, num_files, file_name, num_matching_strings);
      if (opt_l_handling_is == SET) printf("%s\n", file_name);

      regfree(&preg);
    }
    fclose(file_ptr);
  }
  return (errcode);
}

/**
 * @brief Обрабатывает поведение программы при опции '-n'
 * @param num_str
 * @param Opt
 */
void n_handler(Options const *Opt, int num_str) {
	if (Opt->n) printf("%d:", num_str);
}

void c_h_handler(Options const *Opt, int num_files, const char *file_name,
								 unsigned int num_matching_strings) {
//  if (Opt->c && (num_files > 1) && !Opt->h)
//    printf("%s:%d\n", file_name, num_matching_strings);
//  else if (!Opt->c && (num_files > 1))
//		printf("%s:", file_name);
//	else
//    printf("%d\n", num_matching_strings);



	if ((num_files > 1) && !Opt->h)
		printf("%s:%d\n", file_name, num_matching_strings);
	else if (Opt->c && !Opt->h)
		printf("%d\n", num_matching_strings);

}

void c_handler(Options const *Opt, int num_files, const char *file_name,
               unsigned int num_matching_strings) {
  if ((num_files > 1) && !Opt->h)
    printf("%s:%d\n", file_name, num_matching_strings);
  else
    printf("%d\n", num_matching_strings);
}

/**
 * @brief Обрабатывает файлы, содержащие паттерны при запуске программы с опцией
 * '-f'
 * @param pattern
 * @return
 */
int f_handler(char *pattern) {
  int errcode = OK;

  FILE *file_pattern_pointer;
  const char *file_name_pattern = optarg;

  if ((file_pattern_pointer = fopen(file_name_pattern, "r")) == NULL) {
		fprintf(stderr, "s21_grep: %s: %s\n", file_name_pattern, strerror(errno));
    errcode = STOP;
  } else {
    char buf_str_pattern[SIZE] = {0};

    while (NULL != fgets(buf_str_pattern, SIZE, file_pattern_pointer)) {
      if ('\n' == *buf_str_pattern) {
        strcpy(pattern, ".*\0");  // Если есть пустая строка, то вывод всего
                                  // содержимого. Для этого - "шаблон всего"
                                  // (любой символ любое количество раз)
      } else {
        buf_str_pattern[strlen(buf_str_pattern) - 1] =
            '\0';  // Затирание добавленного '\n' от функции fgets
        init_pattern(pattern, buf_str_pattern);
      }
    }
  }
  fclose(file_pattern_pointer);
  return (errcode);
}

/**
 * @brief Заполняет шаблон паттерна, который будет использоваться для поиска в
 * регулярном выражении
 * @param pattern
 * @param src
 */
void init_pattern(char *pattern, const char *src) {
  // Если src не задан (пустой шаблон, то программа выведет
  // анализируемый текст полностью (".*" - любой символ любое
  // количество раз (шаблон всего))
  if (0 == *src) strcpy(pattern, ".*\0");

  // Если паттерн пустой (первый символ - ноль,
  // инвертированный для захождения в условие), то просто
  // записываем в него src
  if (!pattern[0]) {
    strcpy(pattern, src);

    // Иначе если в паттерне "шаблон всего", то шаблон не должен
    // измениться, а если нет (т.е. паттерн другой), то дописываем новый src
    // через оператор регулярного выражения "или"
  } else if (strcmp(pattern, ".*") != 0) {
    strcat(pattern, "|");
    strcat(pattern, src);
  }
}

/**
 * @brief Инициализация структуры опций программы
 * @param Opt
 * @param symbol
 * @param pattern
 * @return errcode - код ошибки
 */
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
      init_pattern(pattern, optarg);
      break;
    case 'f':
      Opt->f = SET;
      errcode = f_handler(pattern);
      break;
    case 's':
      Opt->s = SET;
      break;
    case 'h':
      Opt->h = SET;
      break;
    case '?':
      errcode = ERROR;
  }
  return (errcode);
}
