/**
 * Copyright (с) 2022 Student of School 21:
 * Yonn Argelia
 *
 * yonnarge@student.21-school.ru
 */

#include "s21_cat.h"

/**
 * @brief Запускает выполнение всей работы программы
 * @param argc - количество аргументов в командной строке
 * @param argv - указатель на аргументы командной строки
 * @param pattern - регулярное выражение по которому будет осуществляться поиск
 * @return	0 -	Корректное завершение работы.
 * 					1	- Выявлены ошибки или
 * недоступные файлы. 2	- Работа программы была остановлена для вывода
 * информации по использованию.
 */
int main(int argc, char **argv) {
  int errcode = OK;
  Options Opt = {0, 0, 0, 0, 0, 0};

  errcode = parser(argc, argv, &Opt);

  for (int i = 1; (i < argc) && (errcode == OK); ++i)
    if (argv[i][0] != '-') errcode = file_handler(argv[i], &Opt);

  return (errcode);
}

/**
 * @brief Проводит синтаксический анализ аргументов командной строки и
 * инициализацирует структуру опций, с которыми была запущена программа
 * @param argc - количество аргументов в командной строке
 * @param argv - указатель на аргументы командной строки
 * @param Opt - структура данных, хранящая информацию об опциях, с которыми была
 * запущена программа
 * @return	0 -	Корректное завершение работы.
 * 					1	- Выявлены ошибки или
 * недоступные файлы. 2	- Работа программы была остановлена для вывода
 * информации по использованию.
 */
int parser(int argc, char **argv, Options *Opt) {
  int errcode = OK;
  int opt_long = CLEAR;

  for (int i = 1; i < argc; ++i) {
    if (argv[i][0] == '-') {
      size_t arg_len = strlen(argv[i]);
      char *opt_phrase = argv[i] + 2;

      for (size_t j = 1; (j < arg_len) && opt_long == CLEAR && errcode == OK;
           ++j) {
        switch (argv[i][j]) {
          case '-':
            if (strcmp(opt_phrase, "help") == 0) {
              file_handler("USAGE_s21_cat.txt", Opt);
              errcode = STOP;
            } else if (strcmp(opt_phrase, "number") == 0) {
              Opt->n = opt_long = SET;
            } else if (strcmp(opt_phrase, "number-nonblank") == 0) {
              Opt->b = opt_long = SET;
            } else if (strcmp(opt_phrase, "squeeze-blank") == 0) {
              Opt->s = opt_long = SET;
            } else if (strcmp(opt_phrase, "show-nonprinting") == 0) {
              Opt->v = opt_long = SET;
            } else if (strcmp(opt_phrase, "show-ends") == 0) {
              Opt->e = opt_long = SET;
            } else if (strcmp(opt_phrase, "show-tabs") == 0) {
              Opt->t = opt_long = SET;
            } else if (strcmp(opt_phrase, "show-all") == 0) {
              Opt->v = Opt->t = Opt->e = opt_long = SET;
            } else {
              fprintf(stderr, "s21_cat: unrecognized option --%s\n",
                      opt_phrase);
              puts("Try './s21_cat --help' for more information.");
              errcode = ERROR;
            }
            break;
          case 'b':
            Opt->b = SET;
            break;
          case 'n':
            Opt->n = SET;
            break;
          case 's':
            Opt->s = SET;
            break;
          case 'v':
            Opt->v = SET;
            break;
          case 'T':
            Opt->t = SET;
            break;
          case 'E':
            Opt->e = SET;
            break;
          case 'e':
            Opt->v = Opt->e = SET;
            break;
          case 't':
            Opt->v = Opt->t = SET;
            break;
          case 'A':
            Opt->v = Opt->t = Opt->e = SET;
            break;
          default:
            fprintf(stderr, "s21_cat: invalid option -- '%c'\n", argv[i][j]);
            puts("Try 's21_cat --help' for more information.");
            errcode = ERROR;
        }
      }
    }
  }
  return (errcode);
}

/**
 * @brief Основная функция, которая обрабатывает файлы в соответствии с
 * указанными опциями
 * @param file_name - имя обрабатываемого в текущий момент файла
 * @param Opt - структура данных, хранящая информацию об опциях, с которыми была
 * запущена программа
 * @return	0 -	Корректное завершение работы.
 * 					1	- Выявлены ошибки или
 * недоступные файлы. 2	- Работа программы была остановлена для вывода
 * информации по использованию.
 */
int file_handler(char *file_name, Options *Opt) {
  FILE *file_ptr;
  int errcode = OK;

  if (NULL == (file_ptr = fopen(file_name, "r"))) {
    fprintf(stderr, "s21_cat: %s: %s\n", file_name, strerror(2));
    errcode = ERROR;
  } else {
    int c = fgetc(file_ptr);
    unsigned int num_str = 0;
    char flag_position = IS_BEGIN;

    b_handler(file_ptr, &c, Opt, &num_str, &flag_position);
    n_handler(file_ptr, &c, Opt, &num_str);
    s_handler(file_ptr, &c, Opt, &num_str, &flag_position);

    flag_position = IS_MID;
    do {
      v_handler(&c, Opt);
      t_handler(&c, Opt);
      s_handler(file_ptr, &c, Opt, &num_str, &flag_position);
      e_handler(&c, Opt);

      putchar(c);

      b_handler(file_ptr, &c, Opt, &num_str, &flag_position);
      n_handler(file_ptr, &c, Opt, &num_str);
      c = fgetc(file_ptr);
    } while (file_exist(file_ptr));

    fclose(file_ptr);
  }
  return (errcode);
}

/**
 * @brief Проверяет доступность файла для обработки (существование и отсутствие
 * ошибок)
 * @param file_ptr - указатель на обрабатываемый в текущий момент файл
 * @return	0 -	Корректное завершение работы.
 * 					1	- Выявлены ошибки или
 * недоступные файлы. 2	- Работа программы была остановлена для вывода
 * информации по использованию.
 */
int file_exist(FILE *file_ptr) { return !(feof(file_ptr) || ferror(file_ptr)); }

/**
 * @brief Обрабатывает поведение программы при опции '-b'
 * @param file_ptr - указатель на обрабатываемый в текущий момент файл
 * @param c - обрабатываемый символ
 * @param Opt - структура данных, хранящая информацию об опциях, с которыми была
 * запущена программа
 * @param num_str - номер анализируемой строки файла
 * @param flag_position - флаг для предобратки в начале файла
 */
void b_handler(FILE *file_ptr, const int *c, Options *Opt,
               unsigned int *num_str, const char *flag_position) {
  if (Opt->b) {
    Opt->n = 0;
    int fut_c = fgetc(file_ptr);
    if (file_exist(file_ptr)) {
      if ((*c == '\n' && fut_c != '\n' && *flag_position == IS_MID) ||
          (*c != '\n' && *flag_position == IS_BEGIN)) {
        printf("%6u\t", ++(*num_str));
      }
      fseek(file_ptr, -1, SEEK_CUR);
    }
  }
}

/**
 * @brief Обрабатывает поведение программы при опции '-n'
 * @param file_ptr - указатель на обрабатываемый в текущий момент файл
 * @param c - обрабатываемый символ
 * @param Opt - структура данных, хранящая информацию об опциях, с которыми была
 * запущена программа
 * @param num_str - номер анализируемой строки файла
 */
void n_handler(FILE *file_ptr, const int *c, Options *Opt,
               unsigned int *num_str) {
  if (Opt->n) {
    fgetc(file_ptr);
    if (file_exist(file_ptr)) {
      if (*c == '\n' || *num_str == 0) {
        printf("%6u\t", ++(*num_str));
      }
      fseek(file_ptr, -1, SEEK_CUR);
    }
  }
}

/**
 * @brief Обрабатывает поведение опции '-s'
 * @param file_pfile_ptr - указатель на обрабатываемый в текущий момент файлtr
 * @param fut_c - указатель на следующий за обрабатываемым символ
 * @param c - обрабатываемый символ
 * @param Opt - структура данных, хранящая информацию об опциях, с которыми была
 * запущена программа
 * @param num_str - номер анализируемой строки файла
 * @param flag_position - флаг для предобратки в начале файла
 */
void s_opt_handler(FILE *file_ptr, int *fut_c, int *c, Options *Opt,
                   unsigned int *num_str, const char *flag_position) {
  if (*fut_c == '\n') {
    if (Opt->e) printf("$");
    while (*fut_c == '\n') *fut_c = fgetc(file_ptr);
    putchar('\n');
    if (*flag_position == IS_BEGIN) *c = *fut_c;
    if (Opt->n || (Opt->b && *flag_position == IS_BEGIN)) {
      printf("%6u\t", ++(*num_str));
    }
  }
}

/**
 * @brief Обрабатывает поведение программы при опции '-s'
 * @param file_ptr - указатель на обрабатываемый в текущий момент файл
 * @param c - обрабатываемый символ
 * @param Opt - структура данных, хранящая информацию об опциях, с которыми была
 * запущена программа
 * @param num_str - номер анализируемой строки файла
 * @param flag_position - флаг для предобратки в начале файла
 */
void s_handler(FILE *file_ptr, int *c, Options *Opt, unsigned int *num_str,
               char *flag_position) {
  if (Opt->s) {
    int fut_c = fgetc(file_ptr);
    if (*flag_position == IS_BEGIN) {
      if (*c != '\n') {
        fseek(file_ptr, -1, SEEK_CUR);
      }
      s_opt_handler(file_ptr, &fut_c, c, Opt, num_str, flag_position);
    } else if (*flag_position == IS_MID) {
      if (*c == '\n') {
        s_opt_handler(file_ptr, &fut_c, c, Opt, num_str, flag_position);
      }
      if (file_exist(file_ptr)) {
        fseek(file_ptr, -1, SEEK_CUR);
      }
    }
  }
}

/**
 * @brief Обрабатывает поведение программы при опции '-v'
 * @param c - обрабатываемый символ
 * @param Opt - структура данных, хранящая информацию об опциях, с которыми была
 * запущена программа
 */
void v_handler(int *c, Options *Opt) {
  if (Opt->v) {
    if ((0 <= *c && *c <= 8) || (11 <= *c && *c <= 31)) {
      putchar('^');
      *c += 64;
    }
    if (*c == 127) {
      putchar('^');
      *c -= 64;
    }
  }
}

/**
 * @brief Обрабатывает поведение программы при опции '-t'
 * @param c - обрабатываемый символ
 * @param Opt - структура данных, хранящая информацию об опциях, с которыми была
 * запущена программа
 */
void t_handler(int *c, Options *Opt) {
  if (Opt->t && *c == '\t') {
    putchar('^');
    *c += 64;
  }
  v_handler(c, Opt);
}

/**
 * @brief Обрабатывает поведение программы при опции '-e'
 * @param c - обрабатываемый символ
 * @param Opt - структура данных, хранящая информацию об опциях, с которыми была
 * запущена программа
 */
void e_handler(int *c, Options *Opt) {
  if (Opt->e && (*c == '\n')) printf("$");
  v_handler(c, Opt);
}
