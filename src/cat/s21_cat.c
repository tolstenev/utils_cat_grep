/*
 * Copyright (с) 2022 Student of School 21:
 * Yonn Argelia
 *
 * yonnarge@student.21-school.ru
 */

#include "s21_cat.h"

int main(int argc, char **argv) {
    int result = 0;
    unsigned int counter = 1, number_of_arg = argc;
    Options Opt;
    Opt.b = Opt.e = Opt.n = Opt.s = Opt.t = 0;

    if (argv[counter][0] == '-') {
        while (argc) {
            if (argv[counter][1] == 's') {
                Opt.s = 1;
            }
            argc--;
        }
    }

    counter = 1;
    argc = number_of_arg;

    while (counter < number_of_arg) {
        FILE *file;
        file = fopen(argv[counter], "r");
        result = s21_print_file(file, &Opt);
        counter++;
        fclose(file);
    }
    return (result);
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
    int errcode = 0;

    if (NULL == file) {
        errcode = NO_SUCH_FILE;
    } else {
        // Инициализация переменной, которая будет хранить код текущего символа
        int c = fgetc(file);
        // Пока файл существует, проводим анализ флагов и соответствующий вывод
        while (s21_file_is_exist(file)) {

            // Получили код символа
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







