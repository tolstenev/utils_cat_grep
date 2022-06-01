/*
 * Copyright (с) 2022 Student of School 21:
 * Yonn Argelia
 *
 * yonnarge@student.21-school.ru
 */

#include <stdio.h>
#include "../common/s21_bool.h"

int main(int argc, char **argv) {
    int result = 0;
    int count = 1;

    while (count <= argc) {
        FILE *file;
        file = fopen(argv[count], "r");

        if (file != NULL) {
            int c;
            while (s21_true) {
                c = fgetc(file);
                if (feof(file) || ferror(file)) break;
                putchar(c);
            }
        } /*else {
            result = 2;
            printf("No such file %s\n", argv[count]);
        }*/
        fclose(file);
        count++;
    }
    return (result);
}

