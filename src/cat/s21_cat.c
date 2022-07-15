/*
 * Copyright (с) 2022 Student of School 21:
 * Yonn Argelia
 *
 * yonnarge@student.21-school.ru
 */

#include <stdio.h>
#include <stdbool.h>

typedef struct {
  int b;
  int e;
  int n;
  int s;
  int t;
} Options;

int print_file(FILE *file, Options *Opt);
int file_is_exist(FILE *file);



// TODO: посмотереть уроки по bash-скриптам
// TODO: написать хорошие и понятные тесты на один флаг с просмотром выводимой в файл информацией
// если тест не пройден, то файлы не удаляются, а сохранятются.
// в названии, либо внутри пишется комбинация, при которой не совпало
// TODO: прогнать код Миши
// TODO: написать код этого флага у себя
// TODO:




int main(int argc, char **argv) {
    int result = 0;
    unsigned int counter = 1, number_of_arg = argc;
    Options Opt;
    Opt.b = Opt.e = Opt.n = Opt.s = Opt.t = 0;

    while (counter < number_of_arg) {
        FILE *file;
        file = fopen(argv[counter], "r");
        result = print_file(file, &Opt);
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
int file_is_exist(FILE *file) {
    return !(feof(file) || ferror(file));
}

int print_file(FILE *file, Options *Opt) {
    int error = 0;
    // Просто тестовое выставление флага. Убрать в итоге
    Opt->s = 1;

    if (NULL == file) {
//            error = 2;  // Раскоментировать в конце для корректной работы
        puts("No such file");
    } else {
        int c = 0;
        int k = 0;
        while (file_is_exist(file)) {
            c = fgetc(file);
            if (Opt->s == 1 && c == '\n') {
                int next_char = fgetc(file);
                if (next_char == '\n') {
                    while (next_char == '\n') {
                        c = next_char;
                        next_char = fgetc(file);
                    }
                    putchar('\n');
                }
                if (file_is_exist(file))
                    fseek(file, -1, SEEK_CUR);

            }
            putchar(c);
        }
    }

    /**
     * не работает этот флаг эс
     * надо взять текущий символ
     * если он перенос строки
     *          взять следующий символ
     *     если нет, то
     * если след. тоже перенос строки
     * взять следующий символ, и так проверять, пока не встретим другой символ
     *
     * если встретили другой символ, то вывели один перенос
     * проверили, если встреченный символ не конец файла, то вернули указатель на один символ назад
     */


//    if (Opt->s == 1) && ch == '\n') {
//
//        while (ch == '\n') {
//            if (flags->e == 1 && flags->s == 0)
//                printf("$");
//            if (flags->s == 0 && flags->b == 1)
//                printf("%c", ch);
//            ch = (char) fgetc(file);
//        }
//    }

    return error;
}







