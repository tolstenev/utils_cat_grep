/*
 * Copyright (с) 2022 Student of School 21:
 * Yonn Argelia
 *
 * yonnarge@student.21-school.ru
 */

#include "s21_cat.h"

int main(int argc, char **argv) {
    int errcode = OK;
    unsigned int counter = 1, number_of_arg = argc;
    Options Opt;
    Opt.b = Opt.e = Opt.n = Opt.s = Opt.t = 0;
//    char *usagefile = "USAGE.txt";

    for (int i = 0; i < argc; ++i) {
        if (argv[i][0] == '-') {
            size_t arg_len = strlen(argv[i]);
            char *flag = argv[i] + 2;
            for (size_t j = 1; (j < arg_len) && errcode == OK; ++j) {
                switch (argv[i][j]) {
                    case '-':
                              if (strcmp(flag, "help") == 0) puts("HELP YOURSELF");
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
                        // TODO(me): добавить обработку ошибки, если флаги некорректные
                        // TODO(me): не работает вывод справки по флагу  help
                        // TODO(me): в целом флаги как будто не читаются
                    default:
                        printf("s21_cat: invalid option -- %c\n", argv[i][j]);
                        puts("Try 's21_cat --help' for more information.");
                        errcode = ERROR;
                }
            }
        }
    }

    // TODO(me): переписать основную часть, чтобы в цикле перебирались файлнэймы,
    // а сами фалы открывались уже внутри функции.
    // TODO(me): соответственно изменить сигнатуру функций
    // TODO(me): сделать это всё для того, чтобы одной функций в начале вызвать функцию и открыть файл со справкой

    if (errcode == OK) {
        counter = 1;
        argc = number_of_arg;
        while (counter < number_of_arg) {
            FILE *file;
            file = fopen(argv[counter], "r");
            errcode = s21_print_file(file, &Opt);
            fclose(file);
            counter++;
        }
    }
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

int s21_print_file(FILE *file, Options *Opt) {
    int errcode = OK;

    if (NULL == file) {
        errcode = NO_SUCH_FILE;
    } else {
        // Инициализация переменной, которая будет хранить код текущего символа
        int c = fgetc(file);
        // Пока файл существует, проводим анализ флагов и соответствующий вывод
        while (s21_file_is_exist(file)) {
            // Если сразу встретили перенос каретки и установлен флаг '-s', то
            // заменяем набор пустых строк одной пустой строкой
            if (Opt->s == 1 && c == '\n') {
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
                    putchar('\n');
                }
                // Если следующий символ окажется обычным символом и файл существует,
                // то возвращаем указатель file на одну позицию назад (на текущий символ)
                if (s21_file_is_exist(file))
                    fseek(file, -1, SEEK_CUR);
            }
            // Выводим текущий символ и считываем следующий
            putchar(c);
            c = fgetc(file);
        }
    }

    return (errcode);
}







