/*
 * Copyright (с) 2022 Student of School 21:
 * Yonn Argelia
 *
 * yonnarge@student.21-school.ru
 */

#include <stdio.h>
#include <stdbool.h>
// #include "../common/s21_bool.h"

int print_file(FILE *file);

typedef struct {
  int opt_b;
  int opt_e;
  int opt_n;
  int opt_s;
  int opt_t;
} Options;

int main(int argc, char **argv) {
    int result = 0;
    int count = 1;
    Options Flag;
    Flag.opt_b = Flag.opt_e = Flag.opt_n = Flag.opt_s = Flag.opt_t = 0;


    while (count < argc) {
        FILE *file;
        file = fopen(argv[count], "r");
        result = print_file(file);
        count++;
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
            error = 2;  // Раскоментировать в конце для корректной работы
        puts("No such file");
    }
    return error;
}
