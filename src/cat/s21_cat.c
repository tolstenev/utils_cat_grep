/*
 * Copyright (с) 2022 Student of School 21:
 * Yonn Argelia
 *
 * yonnarge@student.21-school.ru
 */

#include "s21_cat.h"

int main(int argc, char **argv) {
    int errcode = OK;
//    unsigned int counter = 1, number_of_arg = argc;
//    Options Opt = {0};  // TODO(me): мб стоит так инициализировать?
    Options Opt;
    Opt.b = Opt.e = Opt.n = Opt.s = Opt.t = Opt.v = 0;

    for (int i = 0; i < argc; ++i) {
        if (argv[i][0] == '-') {
            size_t arg_len = strlen(argv[i]);
            char *flag = argv[i] + 2;
            for (size_t j = 1; (j < arg_len) && errcode == OK; ++j) {
                switch (argv[i][j]) {
                    case '-':
                              if (strcmp(flag, "help") == 0) {
                                  s21_print_file("dir/USAGE.txt", &Opt);
                                  errcode = STOP;
                              }
                         else if (strcmp(flag, "number") == 0)           Opt.n = 1;
                         else if (strcmp(flag, "number-nonblank") == 0)  Opt.b = 1;
                         else if (strcmp(flag, "squezze-blank") == 0)    Opt.s = 1;
                         else if (strcmp(flag, "show-nonprinting") == 0) Opt.v = 1;
                         else if (strcmp(flag, "show-ends") == 0)        Opt.e = 1;
                         else if (strcmp(flag, "show-tabs") == 0)        Opt.t = 1;
                         else if (strcmp(flag, "show-all") == 0)
                             Opt.v = Opt.t = Opt.e = 1;
                         break;
                    case 'n': Opt.n = 1;                 break;
                    case 'b': Opt.b = 1;                 break;
                    case 's': Opt.s = 1;                 break;
                    case 'v': Opt.v = 1;                 break;
                    case 'E': Opt.e = 1;                 break;
                    case 'T': Opt.t = 1;                 break;
                    case 'e': Opt.v = Opt.e = 1;         break;
                    case 't': Opt.v = Opt.t = 1;         break;
                    case 'A': Opt.v = Opt.t = Opt.e = 1; break;
                    default:
                        printf("s21_cat: invalid option -- %c\n", argv[i][j]);
                        puts("Try 's21_cat --help' for more information.");
                        errcode = ERROR;
                }
            }
        }
    }

    for (int i = 1; (i < argc) && errcode == OK; ++i)
        if (argv[i][0] != '-')
            errcode = s21_print_file(argv[i], &Opt);

    return (errcode);
}

/**
 * @brief Проверяет указатель file на конец файла или наличие ошибок
 * @param file
 * @return 0 - Конец файла или ошибка;
 *         Ненулевое значение - ОК.
 */
int s21_file_is_exist(FILE *file) {
    return !(feof(file) || ferror(file));
}

int s21_print_file(char *file_name, Options *Opt) {
    int errcode = OK;  // TODO(me): подумать, а нужен ли вообще мне код ошибки?
    FILE *file = fopen(file_name, "r");

    if (NULL == file) {
//        errcode = NO_SUCH_FILE;
        printf("s21_cat: No such file or directory'%s'\n", file_name);
    } else {
        // Инициализация переменной, которая будет хранить код текущего символа
        int c = fgetc(file);
        unsigned int num_str = 0;

        if (Opt->n == 1 && Opt->b == 1)
            Opt->n = 0;

        if (Opt->n == 1 || (Opt->b == 1 && c != '\n'))
            printf("%6u\t", ++num_str);

        while (s21_file_is_exist(file) && errcode == OK) {
            // Если сразу встретили перенос каретки и установлен флаг '-s', то
            // заменяем набор пустых строк одной пустой строкой
            if (c == '\n') {
                if (Opt->s == 1) {
                    // Инициализация переменной, которая будет хранить код
                    // следующего символа
                    int next_char = fgetc(file);
                    // Если следующий символ тоже '\n', то проверяем все последующие символы,
                    // пока не встретим другой символ, каждый раз переопределяя текущий символ
                    if (next_char == '\n') {
                        while (next_char == '\n') {
                            c = next_char;  // TODO(me): мб убрать эту строку?
                            next_char = fgetc(file);
                        }
                        // Когда набор пустых строк закончился, то выводим одну пустую строку
                        if (Opt->e == 1) putchar('$');
                        putchar('\n');
                        if (Opt->n == 1) printf("%6u\t", ++num_str);
                    }
                    // Если следующий символ окажется обычным символом и файл существует,
                    // то возвращаем указатель file на одну позицию назад (на текущий символ)
                    if (s21_file_is_exist(file))
                        fseek(file, -1, SEEK_CUR);
                }
                if (Opt->e == 1) putchar('$');
            }
            if (Opt->t == 1 && c == '\t') {
                putchar('^');
                c += 64;
            }
            if (Opt->v == 1) {
                if ((0 <= c && c <= 8) || (11 <= c && c <= 30)) {
                    putchar('^');
                    c += 64;
                }
                if (c == 127) {
                    putchar('^');
                    c -= 64;
                }
            }

            // Выводим текущий символ и считываем следующий
            putchar(c);
            if ((Opt->n == 1) && (c == '\n')) {
                fgetc(file);
                if (s21_file_is_exist(file))
                    printf("%6u\t", ++num_str);
                else
                    errcode = STOP;
                fseek(file, -1, SEEK_CUR);
            }
            c = fgetc(file);
        }
    }
    fclose(file);
    return (errcode);
}







