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

//int print_file(FILE *file) {
//    int error = 0;
//    if (file != NULL) {
//        int c;
//        while (true) {
//            c = fgetc(file);
//            if (feof(file) || ferror(file)) break;
//            putchar(c);
//        }
//    } else {
////            error = 2;  // Раскоментировать в конце для корректной работы
//        puts("No such file");
//    }
//    return error;
//}
int print_file(FILE *file, Options *Opt) {
    int error = 0;
    if (NULL == file) {
//            error = 2;  // Раскоментировать в конце для корректной работы
        puts("No such file");
    } else {
        while (true) {
            if (feof(file) || ferror(file)) break;
            int c = fgetc(file);

            if (c == '\n' && fgetc(file) == '\n') {
                c = fgetc(file);
            }

            putchar(c);
        }
    }


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







