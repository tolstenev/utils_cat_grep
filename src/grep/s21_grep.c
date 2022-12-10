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

  char pattern[BUFF_SIZE] = {0};

  if (argc > 2) {
    int opt_symbol = 0;
    char *optstring = "violnce:f:sh?";

    while (-1 != (opt_symbol = getopt_long(argc, argv, optstring, 0, NULL)))
      errcode = init_struct(&Opt, opt_symbol, pattern);

    if ((Opt.e || Opt.f) & (argc < 4)) errcode = ERROR;
    if ((!Opt.e & !Opt.f) & (argc < 3)) errcode = ERROR;

    if (errcode == OK) executor((const char **)argv, pattern, &Opt);
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
int executor(const char **argv, const char *pattern, Options *Opt) {
  int errcode = OK;
  int num_files = 0;
  int flag_no_pattern_opt = CLEAR;

  if (Opt->e | Opt->f) {
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
 * @param buff_str
 * @param Opt
 */
void opt_handler(const char **argv, int ind_file_arg, int num_files,
                 int num_str, char *buff_str, Options *Opt) {
  if (Opt->c == 0) {
    if (num_files > 1) printf("%s:", argv[ind_file_arg]);

    n_handler(num_str, Opt);
    fputs(buff_str, stdout);

    int n = strlen(buff_str);
    if (buff_str[n] == '\0' && buff_str[n - 1] != '\n') putchar('\n');
  }
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
                 int flag_no_pattern_opt, Options *Opt) {
  int errcode = OK;

  for (int index_loop = 0; index_loop < num_files; ++index_loop) {
    FILE *file_pointer;
    int ind_file_arg = optind + index_loop + flag_no_pattern_opt;
    const char *file_name = argv[ind_file_arg];
    unsigned int num_matching_strings = 0;

    if (NULL == (file_pointer = fopen(file_name, "r"))) {
      fprintf(stderr, "s21_grep: %s: %s\n", file_name, strerror(errno));
      errcode = STOP;
    } else {
      char buff_str[BUFF_SIZE] = {0};
      int num_str = 1;
      char opt_l_handling_is = CLEAR;
      regex_t reg;

      regcomp(&reg, pattern, REG_EXTENDED);

      while (NULL != fgets(buff_str, BUFF_SIZE, file_pointer)) {
        if (OK == regexec(&reg, buff_str, 0, NULL, 0)) {
          if (Opt->c)
            Opt->l ? num_matching_strings = 1 : ++num_matching_strings;
          if (!Opt->l) {
            opt_handler(argv, ind_file_arg, num_files, num_str, buff_str, Opt);
          } else {
            opt_l_handling_is = SET;
          }
        }
        ++num_str;
      }

      if (Opt->c) c_handler(Opt, num_files, file_name, num_matching_strings);
      if (opt_l_handling_is == SET) printf("%s\n", file_name);

      regfree(&reg);
    }
    fclose(file_pointer);
  }
  return (errcode);
}

/**
 * @brief Обрабатывает поведение программы при опции '-n'
 * @param num_str
 * @param Opt
 */
void n_handler(int num_str, Options *Opt) {
  if (Opt->n) printf("%d:", num_str);
}

void c_handler(Options *Opt, int num_files, const char *file_name,
               unsigned int num_matching_strings) {
  if ((num_files > 1) & !Opt->h)
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
    char buff_str_pattern[BUFF_SIZE] = {0};

    while (NULL != fgets(buff_str_pattern, BUFF_SIZE, file_pattern_pointer)) {
      if ('\n' == *buff_str_pattern) {
        strcpy(pattern, ".*\0");  // Если есть пустая строка, то вывод всего
                                  // содержимого. Для этого - "шаблон всего"
                                  // (любой символ любое количество раз)
      } else {
        buff_str_pattern[strlen(buff_str_pattern) - 1] =
            '\0';  // Затирание добавленного '\n' от функции fgets
        init_pattern(pattern, buff_str_pattern);
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
      f_handler(pattern);
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
