/*
 * Copyright (с) 2022 Student of School 21:
 * Yonn Argelia
 *
 * yonnarge@student.21-school.ru
 */

#include <stdio.h>
#include <stdbool.h>

int print_file(FILE *file);

typedef struct {
  int b;
  int e;
  int n;
  int s;
  int t;
} Options;

int main(int argc, char **argv) {
    int result = 0;
    unsigned int counter = 1, number_of_arg = argc;
    Options Opt;
    Opt.b = Opt.e = Opt.n = Opt.s = Opt.t = 0;

    while (counter < number_of_arg) {
        FILE *file;
        file = fopen(argv[counter], "r");
        result = print_file(file);
        counter++;
        fclose(file);
    }
    return (result);
}

int print_file(FILE *file) {
    int error = 0;
    if (file != NULL) {
        int c;
        while (true) {
            c = fgetc(file);
            if (feof(file) || ferror(file)) break;
            putchar(c);
        }
    } else {
//            error = 2;  // Раскоментировать в конце для корректной работы
        puts("No such file");
    }
    return error;
}
